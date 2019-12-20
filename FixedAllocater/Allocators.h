#pragma once 
#include <stdint.h>
class BitArray;
#define DEFAULT_ALIGNMENT 4

struct BlockDescriptor {
	size_t size;
	BlockDescriptor* next;
	BlockDescriptor* prev;
	bool markedForCollect;
};

#pragma region FSA Globals
static const unsigned int* fixedSizes;
static const unsigned int* fixedCounts;
static unsigned int fixedCount;
static uint8_t** allocators;
static BitArray** bitArrays;
#pragma endregion


#pragma region HeapManager Globals
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

void* __cdecl Malloc(size_t);
void __cdecl MFree(void* );
void* operator new(size_t);
void operator delete(void*);
void* operator new[](size_t);
void operator delete[](void*);

#pragma region FSA function declarations
void InitFSA(const unsigned int*, const unsigned int*, const unsigned int);
void* FSalloc(size_t);
bool FSfree(void*);
void DestroyFSA();
#pragma endregion


#pragma region HeapAllocator function declarations
void InitHeapManager(void*, size_t);
void* alloc(size_t);
void  Free(void*);
void collect();
void* FindFreedMemory(size_t, unsigned int);

inline size_t FindSizeRequired(size_t sizeInBytes, unsigned int alignment)
{
	size_t alignmentPadding = alignment - ((0x0 + sizeof(BlockDescriptor)) & (alignment - 1)) % alignment;
	return (sizeof(BlockDescriptor) + sizeof(BlockDescriptor) + alignmentPadding + sizeInBytes);
}

void* FindFirstFit(size_t, unsigned int);
#pragma endregion

