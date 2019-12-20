#include "BitArray.h"
#include <intrin.h>

//No magic numbers rule
#define BITS_IN_A_BYTE 8

BitArray::BitArray(size_t size)
{
    this->size = size;

    unsigned int count;
    if (size % (sizeof(size_t) * BITS_IN_A_BYTE) == 0)
    {
        count = size / (sizeof(size_t) * BITS_IN_A_BYTE);
    }
    else
    {
        count = (size / (sizeof(size_t) * BITS_IN_A_BYTE)) + 1;
    }

    bits = (size_t*)MemoryManager::alloc(sizeof(size_t) * count);

    //Initialize the bitarray with 0
    for (unsigned int i = 0; i < count; ++i)
    {
        bits[count] = 0;
    }
}

BitArray::~BitArray()
{
    this->size = 0;
    MemoryManager::Free(bits);
}

int BitArray::GetFirstSetBit()
{
    long index = -1;
    bool found = false;
    unsigned int count;
    if (size % (sizeof(size_t) * BITS_IN_A_BYTE) == 0)
    {
        count = size / (sizeof(size_t) * BITS_IN_A_BYTE);
    }
    else
    {
        count = (size / (sizeof(size_t) * BITS_IN_A_BYTE)) + 1;
    }
    //Using BitScanReverse for search from MSB to LSB
    unsigned int arrayIndex;
    for (arrayIndex = 0; arrayIndex < count; ++arrayIndex)
    {
#if _WIN64
        if (_BitScanReverse64((unsigned long*)&index, (unsigned long long)~bits[arrayIndex]))
        {
            found = true;
            break;
        }
#else
        if (_BitScanReverse((unsigned long*)&index, (unsigned long)~bits[arrayIndex]))
        {
            found = true;
            break;
        }
#endif

    }
    if (found)
    {
        index = (arrayIndex * sizeof(size_t) * BITS_IN_A_BYTE) +
            ((sizeof(size_t) * BITS_IN_A_BYTE) - index);
    }
    return index;
}

void BitArray::SetBit(const unsigned int index, const unsigned int value)
{
    unsigned int arrayIndex = index / (sizeof(size_t) * BITS_IN_A_BYTE);
    unsigned int bitIndex = (index % (sizeof(size_t) * BITS_IN_A_BYTE));
    //We are referring from MSB to LSB so shift index accordingly
    bitIndex = ((sizeof(size_t) * BITS_IN_A_BYTE) - 1) - bitIndex;
    if (value == 1)
    {
#if _WIN64
        bits[arrayIndex] |= 1ULL << bitIndex;
#else
        bits[arrayIndex] |= 1UL << bitIndex;
#endif
    }
    else
    {
#if _WIN64
        bits[arrayIndex] &= ~(1ULL << bitIndex);
#else
        bits[arrayIndex] &= ~(1UL << bitIndex);
#endif  
    }
}