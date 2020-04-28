#include "MemoryManager.h"
#include "BitArray.h"
#include <assert.h>
#include <stdlib.h>

#pragma region Static Member Declarations
const unsigned int* MemoryManager::fixedSizes;
const unsigned int* MemoryManager::fixedCounts;
unsigned int MemoryManager::fixedCount;
uint8_t** MemoryManager::allocators;
BitArray** MemoryManager::bitArrays;
size_t MemoryManager::sizeHeap;
void* MemoryManager::startPtr;
BlockDescriptor* MemoryManager::lastFreedMem;
BlockDescriptor* MemoryManager::lastAllocatedMem;
#pragma endregion

MemoryManager::MemoryManager()
{

}

void* MemoryManager::AllocateMem(size_t size) {
	return malloc(size);
}

void* MemoryManager::IncreaseMem(void* ptr,size_t newSize) {
	
	return realloc(ptr, newSize);
}

void MemoryManager::FreeMem(void* ptr) {

	free(ptr);
}

void MemoryManager::Init(const void* heapStart,const size_t sizeHeap, const unsigned int* sizes, const unsigned int* counts, const unsigned int count)
{
	InitHeapManager(heapStart,sizeHeap);
	InitFSA(sizes,counts,count);
}

void MemoryManager::Destroy()
{
	DestroyFSA();
}

void* __cdecl MemoryManager::Malloc(size_t i_size)
{
	void* returnPtr = nullptr;

	if (i_size <= fixedSizes[fixedCount - 1])
	{
		//Use Fixed Size Allocator 
		returnPtr = FSalloc(i_size);
	}
	else
	{
		//Use HeapAllocator
		returnPtr = alloc(i_size);
	}
	return returnPtr;
}

void __cdecl MemoryManager::MFree(void* i_ptr)
{
	if (!FSfree(i_ptr))
	{
		Free(i_ptr);
	}
}

#pragma region FSA functions
void MemoryManager::InitFSA(const unsigned int* sizes, const unsigned int* counts, const unsigned int count)
{
	fixedSizes = sizes;
	fixedCounts = counts;
	fixedCount = count;

	allocators = static_cast<uint8_t**>(alloc(sizeof(uint8_t*) * count));
	bitArrays = static_cast<BitArray**>(alloc(sizeof(BitArray*) * count));

	for (unsigned int i = 0; i < count; ++i)
	{
		allocators[i] = static_cast<uint8_t*>(alloc(sizeof(uint8_t) * fixedCounts[i] * fixedSizes[i]));
		bitArrays[i] = new BitArray(counts[i]);
	}
}

void* MemoryManager::FSalloc(size_t sizeInBytes)
{
	unsigned int index;
	//Loop through sizes to find the correct allocator
	for (index = 0; index < fixedCount; ++index)
	{
		if (sizeInBytes <= fixedSizes[index])
		{
			break;
		}
	}

	uint8_t* returnPtr = allocators[index];
	int blockIndex = bitArrays[index]->GetFirstSetBit();

	if (blockIndex == -1)
	{
		returnPtr = nullptr;
	}
	else
	{
		returnPtr = returnPtr + (fixedSizes[index] * blockIndex);
		bitArrays[index]->SetBit(blockIndex, 1);
	}

	return returnPtr;
}

bool MemoryManager::FSfree(void* objRef)
{
	bool found = false;
	unsigned int index;
	uint8_t* ptr = static_cast<uint8_t*>(objRef);
	for (index = 0; index < fixedCount; ++index)
	{
		if (ptr >= allocators[index] && ptr <= allocators[index] + fixedSizes[index])
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		unsigned int blockIndex = (ptr - allocators[index]) / fixedSizes[index];
		bitArrays[index]->SetBit(blockIndex, 0);
	}
	return found;
}
void MemoryManager::DestroyFSA()
{
	for (unsigned int i = 0; i < fixedCount; ++i)
	{
		Free(allocators[i]);
		delete bitArrays[i];
	}

	Free(allocators);
	Free(bitArrays);
}
#pragma endregion

#pragma region HeapAllocator functions
void MemoryManager::InitHeapManager(const void* i_pHeapMemory, size_t i_sizeHeapMemory)
{
	sizeHeap = i_sizeHeapMemory;

	/*Stores the value returned by VirtualAlloc so that
	  it can be returned to VirtualFree when freeing*/
	startPtr = const_cast<void*>(i_pHeapMemory);

	//Create the first free block as the whole heap
	lastFreedMem = reinterpret_cast<BlockDescriptor*>(const_cast<void*>(startPtr));
	lastFreedMem->size = sizeHeap;
	lastFreedMem->markedForCollect = false;
	lastFreedMem->next = nullptr;
	lastFreedMem->prev = nullptr;

	//Keeps track of last allocated block(Descriptor)
	lastAllocatedMem = nullptr;

}

void* MemoryManager::alloc(size_t sizeInBytes)
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

//Returns the Block Descriptor of the obtained fit
void* MemoryManager::FindFreedMemory(size_t sizeInBytes, unsigned int alignment)
{
	return FindFirstFit(sizeInBytes, alignment);
	//retrun FindBestFit(sizeInBytes);
}

void MemoryManager::Free(void* objRef)
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

void MemoryManager::Collect()
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

void* MemoryManager::FindFirstFit(size_t sizeInBytes, unsigned int alignment) {

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

	return iteratorNode;
}

#pragma endregion

#pragma region Global Operator Overloads
//void* operator new(size_t i_size)
//{
//	void* returnPtr = MemoryManager::Malloc(i_size);
//	return returnPtr;
//}
//
//void operator delete(void* i_ptr)
//{
//	MemoryManager::MFree(i_ptr);
//}
//
//void* operator new[](size_t i_size)
//{
//	void* returnPtr = MemoryManager::Malloc(i_size);
//	return returnPtr;
//}
//
//void operator delete [](void* i_ptr)
//{
//	MemoryManager::MFree(i_ptr);
//}
#pragma endregion


