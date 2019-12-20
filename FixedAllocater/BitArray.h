#pragma once
#include "MemorySystem.h"

//Forward declaration to prevent circular dependency
class BitArray
{
public:
	
	BitArray(size_t);
	~BitArray();

	int GetFirstSetBit();
	void SetBit(const unsigned int index, const unsigned int value);

	//new and delete operator overloads for 
	//the BitArray class to use HeapAllocator instead of the FSA
	void* operator new(size_t size)
	{
		return alloc(size);
	}

	void operator delete(void* ptr)
	{
		Free(ptr);
	}

private:
	size_t size;
	size_t * bits;
};
