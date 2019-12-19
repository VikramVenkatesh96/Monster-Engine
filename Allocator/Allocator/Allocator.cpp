// Allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <assert.h>
#include <iostream>
#include <windows.h>

struct BlockDescriptor {
	size_t size;
	BlockDescriptor* next;
	BlockDescriptor* prev;
	bool markedForCollect;
};

//Test Data Structure to allocate memory
struct Node {
	unsigned int value;
	Node* next;
};

unsigned int counter = 0;

#define DEFAULT_ALIGNMENT 4;

#pragma region Globals
//Size of Heap
const size_t 		sizeHeap = 1024 * 1024;

/*Stores the value returned by VirtualAlloc so that
  it can be returned to VirtualFree when freeing*/
const void* startPtr;

//Keeps track of last freed block(Descriptor)
BlockDescriptor* lastFreedMem;

//Keeps track of last allocated block(Descriptor)
BlockDescriptor* lastAllocatedMem = nullptr;

//Keeps track of Fragmented Memory
size_t fragmentedMemory = 0;
#pragma endregion

#pragma region Function Declarations

void* alloc(size_t);
void* alloc(size_t, const unsigned int);
void  Free(void*);
void FreeAll();
//Performs garbage collection when called
void  Collect();
void* FindFreedMemory(size_t, unsigned int);
void* FindFirstFit(size_t, unsigned int);
//void * FindBestFit(size_t, unsigned int);
size_t GetLargestFreeBlock();

size_t GetTotalFreeMemory();

// tells us if a pointer is within this HeapManagers managed memory
bool Contains(void* i_ptr);
// tells us if this pointer is an outstanding allocation from this block
bool IsAllocated(const void* i_ptr);

// a debugging helper function to show us all the free blocks.
void ShowFreeBlocks();
// a debugging helper function to show us all the outstanding blocks.
#pragma endregion

//Test Class for New and Delete
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

private:
	Node* start;
	unsigned int length;
};

LinkedList::LinkedList()
{
	start = static_cast<Node*>(alloc(sizeof(Node)));
	length = 10;
}
LinkedList::~LinkedList()
{
	counter++;
	Free(start);
	length = 0;
}
#pragma region Operator Overloads
//operator overloads for new and delete
void* operator new(const size_t sizeInBytes)
{
	void* ptr = alloc(sizeInBytes);
	return ptr;
}

void operator delete(void* ptr)
{
	Free(ptr);
}

//Operator overloads for new[] and delete[]
void* operator new[](const size_t sizeInBytes)
{
	void* ptr = alloc(sizeInBytes);
	return ptr;
}

void operator delete[](void* ptr)
{
	Free(ptr);
}

//Operator overloads for placement new

//Dummy struct to override placement new
struct dummy {} temp;

void* operator new(const size_t sizeInBytes, const dummy t, void* ptr)
{
	return ptr;
}

//Operator overloads for aligned new and delete
void* operator new(const size_t sizeInBytes, const dummy t, const unsigned int alignment)
{
	void* ptr = alloc(sizeInBytes,alignment);
	return ptr;
}

#pragma endregion

int main()
{
#pragma region MemManager Initialization
	const unsigned int 	numDescriptors = 2048;

	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);

	assert(SysInfo.dwPageSize > 0);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	startPtr = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	//Create the first free block as the whole heap
	lastFreedMem = reinterpret_cast<BlockDescriptor*>(const_cast<void*>(startPtr));
	lastFreedMem->size = sizeHeap;
	lastFreedMem->markedForCollect = false;
	lastFreedMem->next = nullptr;
	lastFreedMem->prev = nullptr;
#pragma endregion

	ShowFreeBlocks();

	//Test the new and delete operator
	LinkedList* list = new LinkedList();
	delete list;
	
	assert(lastAllocatedMem == nullptr);
	ShowFreeBlocks();
	Collect();

	//Test the new[] and delete[] operator
	LinkedList* lists = new LinkedList[5];
	delete[] lists;

	assert(lastAllocatedMem == nullptr);
	ShowFreeBlocks();
	Collect();

	//Test placement new and delete
	const unsigned int size = 5;
	LinkedList* placement = (LinkedList*)malloc(sizeof(LinkedList) * 5);
	for (unsigned int i = 0; i < size; ++i)
	{
		new(temp,placement + i)LinkedList();
	}

	for (unsigned int i = 0; i < size; ++i)
	{
		(placement + i)->~LinkedList();
	}
	
	assert(lastAllocatedMem == nullptr);
	ShowFreeBlocks();
	Collect();

	//Test for aligned list
	const unsigned int alignment = 64;
	LinkedList* alignedList = new(temp, alignment)LinkedList();
	//assert alignment
	assert((reinterpret_cast<uintptr_t>(alignedList)& (alignment - 1)) == 0);
	delete alignedList;

	assert(lastAllocatedMem == nullptr);
	ShowFreeBlocks();
	Collect();

	//Free the heap
	VirtualFree(const_cast<void*>(startPtr), 0, MEM_RELEASE);
}

void* alloc(size_t sizeInBytes)
{
	const unsigned int alignment = DEFAULT_ALIGNMENT;
	//Init the ptr to return
	uint8_t* returnPtr;

	if ((returnPtr = static_cast<uint8_t*>(FindFreedMemory(sizeInBytes, alignment))) != nullptr)
	{

#pragma region Freed LinkedList Deletion

		//Retrieve the BlockDescriptor
		BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(returnPtr);

		//Perform deletion on FreedList(refactor for other data structures)
		//Delete only if not first node
		if (descriptor->prev)
		{
			descriptor->prev->next = descriptor->next;

			if (descriptor->next)
			{
				descriptor->next->prev = descriptor->prev;
			}

			//Check if not last node in the LinkedList
			if (descriptor == lastFreedMem)
			{
				lastFreedMem = lastFreedMem->prev;
			}

			//Clear all node values
			descriptor->prev = nullptr;
			descriptor->next = nullptr;
		}
#pragma endregion

		//Temporary ptr to move
		uint8_t* ptr = returnPtr;

		//Move returnPtr to end of the block
		ptr += reinterpret_cast<BlockDescriptor*>(returnPtr)->size;

		//Temporarily store this location
		uint8_t* tempPtr = ptr;
		//Start moving backwards
		ptr -= sizeInBytes;

		//Align the requested memory
		ptr = ptr - (reinterpret_cast<uintptr_t>(ptr)& (alignment - 1));

		//Store size remaining in previous BlockDescriptor
		//This step has to be done at this point as this very same ptr can be overriden
		//if returnPtr = newBlockDescriptor
		reinterpret_cast<BlockDescriptor*>(returnPtr)->size -= (tempPtr)-(ptr - sizeof(BlockDescriptor));
		reinterpret_cast<BlockDescriptor*>(returnPtr)->markedForCollect = true;

		//Create a new Block Descriptor
		BlockDescriptor* newBlockDescriptor = reinterpret_cast<BlockDescriptor*>
			(ptr - sizeof(BlockDescriptor));

		//Make sure new block is within the heap
		if (newBlockDescriptor - 1 > startPtr)
		{
			newBlockDescriptor->size = tempPtr - (ptr - sizeof(BlockDescriptor));
			newBlockDescriptor->markedForCollect = false;
			newBlockDescriptor->next = nullptr;
			newBlockDescriptor->prev = nullptr;
			//Store ptr in returnPtr
			returnPtr = ptr;
		}
		else
		{
			reinterpret_cast<BlockDescriptor*>(returnPtr)->size += (tempPtr)-(ptr - sizeof(BlockDescriptor));
			reinterpret_cast<BlockDescriptor*>(returnPtr)->markedForCollect = false;
			returnPtr = nullptr;
		}
	}
	else
	{
		//Memory couldn't be allocated
		returnPtr = nullptr;
	}

	//Add the new BlockDescriptor to the allocated list;
	if (returnPtr)
	{
		//Get the BlockDescriptor
		BlockDescriptor* tempBD = reinterpret_cast<BlockDescriptor*>(returnPtr - sizeof(BlockDescriptor));

#pragma region Allocated LinkedList Addition
		//Perform Doubly LinkedList Addition(refactor for other type of data structures)
		tempBD->prev = lastAllocatedMem;
		if (lastAllocatedMem)
		{
			lastAllocatedMem->next = tempBD;
		}
		lastAllocatedMem = tempBD;
#pragma endregion
	}

	return returnPtr;
}

void* alloc(size_t sizeInBytes, const unsigned int alignment) {
	//Init the ptr to return
	uint8_t* returnPtr;

	if ((returnPtr = static_cast<uint8_t*>(FindFreedMemory(sizeInBytes, alignment))) != nullptr)
	{

#pragma region Freed LinkedList Deletion

		//Retrieve the BlockDescriptor
		BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>(returnPtr);

		//Perform deletion on FreedList(refactor for other data structures)
		//Delete only if not first node
		if (descriptor->prev)
		{
			descriptor->prev->next = descriptor->next;

			if (descriptor->next)
			{
				descriptor->next->prev = descriptor->prev;
			}

			//Check if not last node in the LinkedList
			if (descriptor == lastFreedMem)
			{
				lastFreedMem = lastFreedMem->prev;
			}

			//Clear all node values
			descriptor->prev = nullptr;
			descriptor->next = nullptr;
		}
#pragma endregion

		//Temporary ptr to move
		uint8_t* ptr = returnPtr;

		//Move returnPtr to end of the block
		ptr += reinterpret_cast<BlockDescriptor*>(returnPtr)->size;

		//Temporarily store this location
		uint8_t* tempPtr = ptr;
		//Start moving backwards
		ptr -= sizeInBytes;

		//Align the requested memory
		ptr = ptr - (reinterpret_cast<uintptr_t>(ptr)& (alignment - 1));

		//Store size remaining in previous BlockDescriptor
		//This step has to be done at this point as this very same ptr can be overriden
		//if returnPtr = newBlockDescriptor
		reinterpret_cast<BlockDescriptor*>(returnPtr)->size -= tempPtr - (ptr - sizeof(BlockDescriptor));
		reinterpret_cast<BlockDescriptor*>(returnPtr)->markedForCollect = true;

		//Create a new Block Descriptor
		BlockDescriptor* newBlockDescriptor = reinterpret_cast<BlockDescriptor*>
			(ptr - sizeof(BlockDescriptor));

		//Make sure new block is within the heap
		if (newBlockDescriptor /*-1*/ >= startPtr)
		{
			newBlockDescriptor->size = tempPtr - (ptr - sizeof(BlockDescriptor));
			newBlockDescriptor->markedForCollect = false;
			newBlockDescriptor->next = nullptr;
			newBlockDescriptor->prev = nullptr;
			//Store ptr in returnPtr
			returnPtr = ptr;
		}
		else
		{
			reinterpret_cast<BlockDescriptor*>(returnPtr)->size += tempPtr - (ptr - sizeof(BlockDescriptor));
			reinterpret_cast<BlockDescriptor*>(returnPtr)->markedForCollect = false;
			returnPtr = nullptr;
		}
	}
	else
	{
		//Memory couldn't be allocated
		returnPtr = nullptr;
	}

	//Add the new BlockDescriptor to the allocated list;
	if (returnPtr)
	{
		//Get the BlockDescriptor
		BlockDescriptor* tempBD = reinterpret_cast<BlockDescriptor*>(returnPtr - sizeof(BlockDescriptor));

#pragma region Allocated LinkedList Addition
		//Perform Doubly LinkedList Addition(refactor for other type of data structures)
		tempBD->prev = lastAllocatedMem;
		if (lastAllocatedMem)
		{
			lastAllocatedMem->next = tempBD;
		}
		lastAllocatedMem = tempBD;
#pragma endregion
	}

	return returnPtr;
}

//Returns the Block Descriptor of the obtained fit
void* FindFreedMemory(size_t sizeInBytes, unsigned int alignment)
{
	return FindFirstFit(sizeInBytes, alignment);
	//retrun FindBestFit(sizeInBytes);
}

void Free(void* objRef)
{//Retreive the BlockDescriptor node
	BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>
		(static_cast<uint8_t*>(objRef) - sizeof(BlockDescriptor));
#pragma region Allocated LinkedList Deletion
	//Perform deletion on AllocatedList(refactor for other data structures)
	if (descriptor->prev)
	{
		descriptor->prev->next = descriptor->next;
	}

	if (descriptor->next)
	{
		descriptor->next->prev = descriptor->prev;
	}

	//Check if not last node in the LinkedList
	if (descriptor == lastAllocatedMem)
	{
		lastAllocatedMem = lastAllocatedMem->prev;
	}

	//Clear all node values
	descriptor->prev = nullptr;
	descriptor->next = nullptr;
#pragma endregion

#pragma region Freed LinkedList Addition
	//Perform addition on FreedList(refactor for other data structures)
	descriptor->prev = lastFreedMem;
	if (lastFreedMem)
	{
		lastFreedMem->next = descriptor;
	}
	lastFreedMem = descriptor;
#pragma endregion
}

void Collect()
{
	bool foundAllMarked;
	//Reach the first node by traversing the list
	BlockDescriptor* tempIterator = lastFreedMem;
	while (tempIterator->prev != nullptr)
	{
		tempIterator = tempIterator->prev;
	}

	BlockDescriptor* firstIterator = tempIterator;
	BlockDescriptor* secondIterator;

	while (firstIterator != nullptr)
	{
		secondIterator = firstIterator->next;

		while (secondIterator != nullptr)
		{
			foundAllMarked = false;

			//Consolidate all fragmented memory
			do
			{
				BlockDescriptor* tempBD = reinterpret_cast<BlockDescriptor*>
					(reinterpret_cast<uint8_t*>(firstIterator) + firstIterator->size);

				//Safety to make sure addresses are within Heap
				if (tempBD >= reinterpret_cast<BlockDescriptor*>
					(reinterpret_cast<uint8_t*>(const_cast<void*>(startPtr)) + sizeHeap))
				{
					break;
				}


				if (tempBD->markedForCollect)
				{
					firstIterator->size += tempBD->size;
				}
				else
				{
					foundAllMarked = true;
				}
			} while (!foundAllMarked);

			//Retrieve next BlockDescriptor
			BlockDescriptor* blockDescriptor = reinterpret_cast<BlockDescriptor*>
				(reinterpret_cast<uint8_t*>(firstIterator) + firstIterator->size);

			//Safety to make sure addresses are within Heap
			if (blockDescriptor >= reinterpret_cast<BlockDescriptor*>
				(reinterpret_cast<uint8_t*>(const_cast<void*>(startPtr)) + sizeHeap))
			{
				break;
			}

			//Check if allocations are contigous
			if (secondIterator == blockDescriptor) {

#pragma region Freed LinkedList Deletion
				//Perform Deletion of secondIterator from FreeList
				if (secondIterator->prev)
				{
					secondIterator->prev->next = secondIterator->next;
				}

				if (secondIterator->next)
				{
					secondIterator->next->prev = secondIterator->prev;
				}

				if (secondIterator == lastFreedMem) {
					lastFreedMem = lastFreedMem->prev;
				}

				//Clear all node values
				secondIterator->prev = nullptr;
				secondIterator->next = nullptr;
#pragma endregion

				firstIterator->size += secondIterator->size;
				//Reset secondIterator to recheck for contigous allocations
				secondIterator = firstIterator->next;
				continue;
			}

			secondIterator = secondIterator->next;
		}

		firstIterator = firstIterator->next;
	}
}

inline size_t FindSizeRequired(size_t sizeInBytes, unsigned int alignment)
{
	size_t alignmentPadding = alignment - ((0x0 + sizeof(BlockDescriptor)) & (alignment - 1)) % alignment;
	return (sizeof(BlockDescriptor) + sizeof(BlockDescriptor) + alignmentPadding + sizeInBytes);
}

void* FindFirstFit(size_t sizeInBytes, unsigned int alignment) {

	BlockDescriptor* iteratorNode = lastFreedMem;

	size_t actualSizeRequired = FindSizeRequired(sizeInBytes, alignment);

	while (iteratorNode != nullptr)
	{
		if (iteratorNode->size >= actualSizeRequired)
		{
			break;
		}

		iteratorNode = iteratorNode->prev;
	}

	if (iteratorNode)
	{
		fragmentedMemory += iteratorNode->size - actualSizeRequired;
	}

	return iteratorNode;
}

size_t GetLargestFreeBlock()
{
	size_t largestFreeBlockSize = 0;
	BlockDescriptor* iterator = lastFreedMem;
	while (iterator != nullptr) {
		if (iterator->size > largestFreeBlockSize)
		{
			largestFreeBlockSize = iterator->size;
		}
		iterator = iterator->prev;
	}
	return largestFreeBlockSize;
}

void FreeAll()
{
	while (lastAllocatedMem)
	{
		Free(lastAllocatedMem);
	}
}

size_t GetTotalFreeMemory()
{
	size_t totalFreeMemSize = 0;
	BlockDescriptor* iterator = lastFreedMem;

	while (iterator != nullptr) {
		totalFreeMemSize += iterator->size;
		iterator = iterator->prev;
	}

	return totalFreeMemSize;
}

bool Contains(void* i_ptr)
{
	bool isPresent = false;

	//Retrieve BlockDescriptor
	BlockDescriptor* blockDescriptor =
		reinterpret_cast<BlockDescriptor*>(static_cast<uint8_t*>(i_ptr) - sizeof(BlockDescriptor));

	//Search if BlockDescriptor in Free List
	BlockDescriptor* iterator = lastFreedMem;
	while (iterator != nullptr)
	{
		if (iterator == blockDescriptor)
		{
			isPresent = true;
			break;
		}
		iterator = iterator->prev;
	}

	if (isPresent)
	{
		return isPresent;
	}
	else
	{
		//Search if BlockDescriptor in Allocated List
		isPresent = IsAllocated(i_ptr);

		return isPresent;
	}
}

bool IsAllocated(const void* i_ptr)
{
	bool isPresent = false;

	BlockDescriptor* blockDescriptor = reinterpret_cast<BlockDescriptor*>
		(static_cast<uint8_t*>(const_cast<void*>(i_ptr)) - sizeof(BlockDescriptor));

	BlockDescriptor* iterator = lastAllocatedMem;

	while (iterator != nullptr)
	{
		if (iterator == blockDescriptor)
		{
			isPresent = true;
			break;
		}
		iterator = iterator->prev;
	}

	return isPresent;
}

inline void DrawLine()
{
	const char asciiCode = static_cast<char>(205);
	const unsigned int lineLength = 75;
	for (unsigned int i = 0; i < lineLength; ++i)
	{
		std::cout << asciiCode;
	}
	std::cout << std::endl;
}

void ShowFreeBlocks()
{
	if (lastFreedMem) {
		std::cout << "Index" << "\t\t\t" << "Address" << "\t\t\t\t" << "Size" << std::endl;
		DrawLine();

		unsigned int index = 1;
		BlockDescriptor* iterator = lastFreedMem;

		while (iterator != nullptr)
		{
			std::cout << index << "\t\t\t" << iterator << "\t\t\t" << iterator->size << std::endl;
			DrawLine();
			iterator = iterator->prev;
			index++;
		}

		std::cout << "Total free memory available: " << GetTotalFreeMemory() << std::endl;

	}
	else
	{
		std::cout << "No Free Memory!" << std::endl;
	}
}

