#pragma once
#include "Allocators.h"

//Fixed Size Allocator initialization parameters
#pragma region FSA params
const unsigned int count = 3;
//This has to be in ascending order
const unsigned int sizes[] = {16, 32 ,96};
const unsigned int counts[] = {100, 200, 400};
#pragma endregion

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();
