#include "HeapManager.h"
#include <iostream>

#pragma region Static Member Definitions
size_t HeapManager::sizeHeap = 0;
unsigned int HeapManager::numDescriptors;
const void* HeapManager :: startPtr;
BlockDescriptor* HeapManager::lastFreedMem;
BlockDescriptor* HeapManager::lastAllocatedMem;
#pragma endregion

unsigned int overflowCounter = 0;

HeapManager::HeapManager(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors) {
	startPtr = i_pHeapMemory;
	sizeHeap = i_HeapMemorySize;
	numDescriptors = i_numDescriptors;
	//Create the first free block as the whole heap
	lastFreedMem = reinterpret_cast<BlockDescriptor*>(const_cast<void*>(startPtr));
	lastFreedMem->size = sizeHeap;
	lastFreedMem->markedForCollect = false;
	lastFreedMem->next = nullptr;
	lastFreedMem->prev = nullptr;
}

HeapManager* HeapManager::create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	static HeapManager heapManager = HeapManager(i_pHeapMemory, i_HeapMemorySize, i_numDescriptors);
	return &heapManager;
}

HeapManager* HeapManager::destroy()
{
	startPtr = nullptr;
	sizeHeap = 0;
	numDescriptors = 0;
	lastAllocatedMem = nullptr;
	lastFreedMem = nullptr;
	return nullptr;
}

void* HeapManager::_alloc(size_t i_bytes)
{
	const unsigned int alignment = DEFAULT_ALIGNMENT;
	//Init the ptr to return
	uint8_t* returnPtr;

	if ((returnPtr = static_cast<uint8_t*>(FindFreedMemory(i_bytes, alignment))) != nullptr)
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
		ptr -= i_bytes;

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


void* HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	//Init the ptr to return
	uint8_t* returnPtr;

	if ((returnPtr = static_cast<uint8_t*>(FindFreedMemory(i_bytes, i_alignment))) != nullptr)
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
		ptr -= i_bytes;

		//Align the requested memory
		ptr = ptr - (reinterpret_cast<uintptr_t>(ptr)& (i_alignment - 1));

		//Store size remaining in previous BlockDescriptor
		//This step has to be done at this point as this very same ptr can be overriden
		//if returnPtr = newBlockDescriptor
		if ((tempPtr - (ptr - sizeof(BlockDescriptor))) > reinterpret_cast<BlockDescriptor*>(returnPtr)->size)
		{
			overflowCounter++;
		}
		reinterpret_cast<BlockDescriptor*>(returnPtr)->size -= tempPtr -(ptr - sizeof(BlockDescriptor));
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
			reinterpret_cast<BlockDescriptor*>(returnPtr)->size += tempPtr -(ptr - sizeof(BlockDescriptor));
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

bool HeapManager::_free(void* i_ptr)
{
	//Retreive the BlockDescriptor node
	BlockDescriptor* descriptor = reinterpret_cast<BlockDescriptor*>
		(static_cast<uint8_t*>(i_ptr) - sizeof(BlockDescriptor));
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
	return true;
}

void HeapManager::collect()
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
					if (tempBD->size >= sizeHeap) {
						overflowCounter++;
						break;
					}
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
				if (firstIterator->size >= sizeHeap) {
					int x = 0;
				}
				//Reset secondIterator to recheck for contigous allocations
				secondIterator = firstIterator->next;
				continue;
			}
			if (secondIterator->next == nullptr)
			{
				int x = 0;
			}
			secondIterator = secondIterator->next;
		}

		firstIterator = firstIterator->next;
	}
}

size_t HeapManager::getLargestFreeBlock() const
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

size_t HeapManager::getTotalFreeMemory() const
{
	size_t totalFreeMemSize = 0;
	BlockDescriptor* iterator = lastFreedMem;

	while (iterator != nullptr) {
		totalFreeMemSize += iterator->size;
		iterator = iterator->prev;
	}

	return totalFreeMemSize;
}

bool HeapManager::Contains(void* i_ptr) const
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

bool HeapManager::IsAllocated(void* i_ptr) const
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

void HeapManager::DrawLine() const
{
	const char asciiCode = static_cast<char>(205);
	const unsigned int lineLength = 75;
	for (unsigned int i = 0; i < lineLength; ++i)
	{
		std::cout << asciiCode;
	}
	std::cout << std::endl;

}

void HeapManager::ShowFreeBlocks() const
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

		std::cout << "Total free memory available: " << getTotalFreeMemory() << std::endl;

	}
	else
	{
		std::cout << "No Free Memory!" << std::endl;
	}
}

void HeapManager::ShowOutstandingAllocations() const
{
	if (lastAllocatedMem) {
		std::cout << "Index" << "\t\t\t" << "Address" << "\t\t\t\t" << "Size" << std::endl;
		DrawLine();

		unsigned int index = 1;
		BlockDescriptor* iterator = lastAllocatedMem;

		while (iterator != nullptr)
		{
			std::cout << index << "\t\t\t" << iterator << "\t\t\t" << iterator->size << std::endl;
			DrawLine();
			iterator = iterator->prev;
			index++;
		}

	}
	else
	{
		std::cout << "No Allocated Memory!" << std::endl;
	}
}

void* HeapManager::FindFreedMemory(size_t sizeInBytes, unsigned int alignment)
{
	return FindFirstFit(sizeInBytes, alignment);
}

void* HeapManager::FindFirstFit(size_t sizeInBytes, unsigned int alignment)
{

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

