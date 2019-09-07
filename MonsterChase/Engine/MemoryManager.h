#pragma once
#include <stdlib.h>
class MemoryManager
{
public:
	MemoryManager();
	
	static void* AllocateMem(size_t);
	
	static void* ModifyMem(void*,size_t);
	
	template <class T> static void* DecreaseMem(T* ptr, int n, int index) {

		for (int i = index + 1; i < n; ++i) {
			ptr[i - 1] = ptr[i];
		}
		return realloc(ptr, sizeof(T)*(n - 1));
	}
	static void FreeMem(void* ptr);

};

