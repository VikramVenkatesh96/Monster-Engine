#pragma once
#include "DataStructures.h"
// this is a sample of what your HeapManager class interface should look like.

class HeapManager
{
public:

	HeapManager(void *, size_t, unsigned int);

	static HeapManager * create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	static HeapManager * destroy();

	// allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);
	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);

	// frees an allocation
	bool _free(void* i_ptr);

	// attempt to merge abutting blocks.
	void collect();

	// tells us the size of the largest free block
	size_t getLargestFreeBlock() const;
	// tells us how much total memory is available
	size_t getTotalFreeMemory() const;

	// tells us if a pointer is within this HeapManagers managed memory
	bool Contains(void * i_ptr) const;
	// tells us if this pointer is an outstanding allocation from this block
	bool IsAllocated(void* i_ptr) const;

	// a debugging helper function to show us all the free blocks.
	void ShowFreeBlocks() const;
	// a debugging helper function to show us all the outstanding blocks.

private:
	static void * startPtr;
	static unsigned int numDescriptors;
	static size_t sizeOfHeap;
	static LinkedList freeBlocksList;
	static LinkedList allocatedBlockList;
};
