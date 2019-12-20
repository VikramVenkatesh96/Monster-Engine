#include "MemorySystem.h"

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	InitHeapManager(i_pHeapMemory, i_sizeHeapMemory);
	InitFSA(sizes, counts, count);
	return true;
}

void Collect()
{
	collect();
}

void DestroyMemorySystem()
{
	DestroyFSA();
}

