#include "HeapManager.h"
#include <stdlib.h>
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
{	//Allocate space for the block desc
	LinkedListNode * blockDescNode = (LinkedListNode *)startPtr;
	
	//Actual pointer to be returned is after the block desc so add its size to reach that location
	char * ptr = (char *)startPtr + sizeof(blockDescNode);
	
	//Init the block descriptor
	blockDescNode->allocatedMemPtr = ptr;
	blockDescNode->size = i_bytes;
	blockDescNode->next = NULL;
	
	//Add the node to allocatedMemList
	allocatedBlockList.insert(blockDescNode);
	
	//calculate size of padding required for alignment(default: 4 bytes aligned)
	size_t padding = (((uintptr_t)ptr + i_bytes) % 4);
	
	//Change the ptr for the next allocation (current head + block desc + data + alignmentPadding) 
	startPtr = (char *)startPtr + sizeof(blockDescNode) + i_bytes + padding;
	
	//Return the allocated pointer
	return ptr;
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	return nullptr;
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
	return size_t();
}

size_t HeapManager::getTotalFreeMemory() const
{
	return size_t();
}

bool HeapManager::Contains(void * i_ptr) const
{
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	return false;
}

void HeapManager::ShowFreeBlocks() const
{
}

