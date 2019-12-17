#pragma once
// this is a sample of what your HeapManager class interface should look like.

#define DEFAULT_ALIGNMENT 4

//BlockDescriptor structure
struct BlockDescriptor {
	size_t size;
	BlockDescriptor* next;
	BlockDescriptor* prev;
	bool markedForCollect;
};

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

private:
	
	static size_t sizeHeap;
	
	unsigned static int numDescriptors;
	/*Stores the value returned by VirtualAlloc so that
  it can be returned to VirtualFree when freeing*/
	const static void* startPtr;

	//Keeps track of last freed block(Descriptor)
	static BlockDescriptor* lastFreedMem;

	//Keeps track of last allocated block(Descriptor)
	static BlockDescriptor* lastAllocatedMem;

	void* FindFreedMemory(size_t, unsigned int);

	inline size_t FindSizeRequired(size_t sizeInBytes, unsigned int alignment)
	{
		size_t alignmentPadding = alignment - ((0x0 + sizeof(BlockDescriptor)) & (alignment - 1)) % alignment;
		return (sizeof(BlockDescriptor) + sizeof(BlockDescriptor) + alignmentPadding + sizeInBytes);
	}

	void* FindFirstFit(size_t, unsigned int);
	
	void DrawLine() const;

public:
	// a debugging helper function to show us all the free blocks.
	void ShowFreeBlocks() const;
	// a debugging helper function to show us all the outstanding blocks.
	void ShowOutstandingAllocations() const;
};
