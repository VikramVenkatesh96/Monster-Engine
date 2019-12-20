#pragma once
#include "GameObject.h"
 
static bool endUpdate = false;
static List<GameObject> gameObjects;
#pragma region MemoryManager variables
//Heap start and size
static const void* heapStart;
static const size_t sizeOfHeap = 1024 * 1024;

//Fixed size allocator sizes and counts
const unsigned int count = 3;
//This has to be in ascending order
const unsigned int sizes[] = { 16, 32 ,96 };
const unsigned int counts[] = { 100, 200, 400 };

#pragma endregion

