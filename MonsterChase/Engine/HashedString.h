#pragma once
#include <string.h>
class HashedString
{
public:
	constexpr HashedString() :
		hash(Hash(""))
	{
	}
	constexpr HashedString(const char* i_string) :
		hash(Hash(i_string))
	{
	}
	HashedString(const HashedString& i_other);
	HashedString & operator=(const HashedString& i_other);
	~HashedString();
	unsigned int get() const;
	bool operator ==(const HashedString & i_other) const;
private:
	static constexpr size_t Hash(const char* i_string)
	{
		return Hash(reinterpret_cast<void*>(const_cast<char*>(i_string)), strlen(i_string));
	}
	//Using FNV-1 hash function
	static constexpr size_t Hash(const void* i_bytes, size_t i_count)
	{
		const unsigned char* p = static_cast<const unsigned char*>(i_bytes);
#ifdef _WIN64
		size_t result = 0xCBF29CE484222325; //FNV offset basis
#else
		size_t result = 0x811C9DC5;
#endif
		while (--i_count)
		{
#ifdef _WIN64
			result *= 0x100000001B3; //FNV prime
#else
			result *= 0x1000193;
#endif
			result ^= *p++;
		}
		return result;
	}

private:
	size_t hash;
};

