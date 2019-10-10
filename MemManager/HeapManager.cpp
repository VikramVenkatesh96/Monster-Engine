#include "HeapManager.h"
#include <iostream>

#define DEADZONESIZE 4
#define DEFAULTALIGNMENT 4

HeapManager::HeapManager(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors) {
	startPtr = i_pHeapMemory;
	sizeOfHeap = i_HeapMemorySize;
	numDescriptors = i_numDescriptors;
}

HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	static HeapManager heapManager = HeapManager(i_pHeapMemory ,i_HeapMemorySize , i_numDescriptors);
	return &heapManager;
}

HeapManager * HeapManager::destroy()
{
	startPtr = nullptr;
	sizeOfHeap = 0;
	numDescriptors = 0;
	//remove all nodes from the linked lists
	return nullptr;
}

void * HeapManager::_alloc(size_t i_bytes)
{	
	//Allocate space for the block desc
	LinkedListNode * blockDescNode = (LinkedListNode *)startPtr;
	
	// Pad after block desc to make sure address starts aligned
	size_t startPadding = DEFAULTALIGNMENT - (((uintptr_t)startPtr + sizeof(blockDescNode)) % DEFAULTALIGNMENT);
	
	//Actual pointer to be returned is after the block desc so add its size to reach that location
	char * ptr = (char *)startPtr + sizeof(blockDescNode) + startPadding;
	
	//Init the block descriptor
	blockDescNode->allocatedMemPtr = ptr;
	blockDescNode->size = i_bytes;
	blockDescNode->next = NULL;
	
	//Add the node to allocatedMemList
	allocatedBlockList.insert(blockDescNode);
	
	//calculate size of padding required for alignment(default: 4 bytes aligned)
	size_t endPadding = 4 - (((uintptr_t)ptr + i_bytes) % 4);
	
	//Change the ptr for the next allocation (current head + block desc + data + alignmentPadding) 
	startPtr = (char *)startPtr + startPadding + sizeof(blockDescNode) + i_bytes + endPadding;
	
	//Return the allocated pointer
	return ptr;
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	//Allocate space for the block desc
	LinkedListNode * blockDescNode = (LinkedListNode *)startPtr;

	//Pad after blockDescriptor  to make sure address is aligned
	size_t startPadding = i_alignment - (((uintptr_t)startPtr + sizeof(blockDescNode)) % i_alignment);
	
	//Actual pointer to be returned is after the block desc so add its size to reach that location
	char * ptr = (char *)startPtr + sizeof(blockDescNode) + startPadding;

	//Init the block descriptor
	blockDescNode->allocatedMemPtr = ptr;
	blockDescNode->size = i_bytes;
	blockDescNode->next = NULL;

	//Add the node to allocatedMemList
	allocatedBlockList.insert(blockDescNode);

	//calculate size of padding required for alignment
	size_t endPadding = i_alignment - (((uintptr_t)ptr + i_bytes) % i_alignment);

	//Change the ptr for the next allocation (current head + block desc + data + alignmentPadding) 
	startPtr = (char *)startPtr + startPadding + sizeof(blockDescNode) + i_bytes + endPadding;

	//Return the allocated pointer
	return ptr;
}

bool HeapManager::_free(void * i_ptr)
{
	return false;
}

void HeapManager::collect()
{
}

size_t HeapManager::getLargestFreeBlock() const
{
	size_t largestFreeBlock = 0;
	LinkedListNode * temp = freeBlocksList.GetStart();
	for (unsigned int i = 0; i < freeBlocksList.GetLength(); ++i) {
		if (temp->size > largestFreeBlock) {
			largestFreeBlock = temp->size;
		}
		temp = temp->next;
	}
	return largestFreeBlock;
}

size_t HeapManager::getTotalFreeMemory() const
{
	size_t totalFreeMem = 0;
	LinkedListNode * temp = freeBlocksList.GetStart();
	for (unsigned int i = 0; i < freeBlocksList.GetLength(); ++i) {
		totalFreeMem = totalFreeMem + temp->size;
		temp = temp->next;
	}
}

bool HeapManager::Contains(void * i_ptr) const
{
	if (allocatedBlockList.FindElement(i_ptr) || freeBlocksList.FindElement(i_ptr))
		return true;
	else
		return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	return allocatedBlockList.FindElement(i_ptr);
}

void HeapManager::ShowFreeBlocks() const
{
	std::cout << "Free Blocks List:" << std::endl;
	freeBlocksList.PrintNodes();
}

