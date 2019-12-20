#include "MemoryManager.h"
#include <stdlib.h>


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
