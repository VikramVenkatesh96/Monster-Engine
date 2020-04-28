#pragma once
#include <stdlib.h> 
#include <stdint.h>

class BitArray;
#define DEFAULT_ALIGNMENT 4

struct BlockDescriptor {
	size_t size;
	BlockDescriptor* next;
	BlockDescriptor* prev;
	bool markedForCollect;
};

class MemoryManager
{
public:
	MemoryManager();
	
	static void* AllocateMem(size_t);
	
	static void* IncreaseMem(void*,size_t);
	
	template <class T>
	static void* DecreaseMem(T* ptr, int n, int index) {

		for (int i = index + 1; i < n; ++i) {
			ptr[i - 1] = ptr[i];
		}
		delete ptr[n-1];
		return realloc(ptr, sizeof(T)*(n - 1));
	}

	static void FreeMem(void* ptr);
	static void Init(const void * ,const size_t, const unsigned int*, const unsigned int*, const unsigned int);
	static void Destroy();
	static void* __cdecl Malloc(size_t);
	static void __cdecl MFree(void*);
	static void* alloc(size_t);
	static void  Free(void*);

private:
#pragma region FSA Params
	static const unsigned int* fixedSizes;
	static const unsigned int* fixedCounts;
	static unsigned int fixedCount;
	static uint8_t** allocators;
	static BitArray** bitArrays;
#pragma endregion

#pragma region HeapManager Params
	//Size of Heap
	static size_t sizeHeap;

	/*Stores the value returned by VirtualAlloc so that
	  it can be returned to VirtualFree when freeing*/
	static void* startPtr;

	//Keeps track of last freed block(Descriptor)
	static BlockDescriptor* lastFreedMem;

	//Keeps track of last allocated block(Descriptor)
	static BlockDescriptor* lastAllocatedMem;

#pragma endregion

#pragma region FSA function declarations
	static void InitFSA(const unsigned int*, const unsigned int*, const unsigned int);
	static void* FSalloc(size_t);
	static bool FSfree(void*);
	static void DestroyFSA();
#pragma endregion

#pragma region HeapAllocator function declarations
	static void InitHeapManager(const void*, size_t);
	static void Collect();
	static void* FindFreedMemory(size_t, unsigned int);

	static inline size_t FindSizeRequired(size_t sizeInBytes, unsigned int alignment)
	{
		size_t alignmentPadding = alignment - ((0x0 + sizeof(BlockDescriptor)) & (alignment - 1)) % alignment;
		return (sizeof(BlockDescriptor) + sizeof(BlockDescriptor) + alignmentPadding + sizeInBytes);
	}

	static void* FindFirstFit(size_t, unsigned int);
#pragma endregion
};
//
//void* operator new(size_t);
//void operator delete(void*);
//void* operator new[](size_t);
//void operator delete[](void*);