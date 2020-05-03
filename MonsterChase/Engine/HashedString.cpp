#include "HashedString.h"

HashedString::HashedString(const HashedString & i_other):
	hash(i_other.hash)
{
}

HashedString & HashedString::operator=(const HashedString & i_other)
{
	hash = i_other.hash;
	return *this;
}


HashedString::~HashedString()
{
}

unsigned int HashedString::get() const
{
	return hash;
}

bool HashedString::operator==(const HashedString & i_other) const
{
	return (hash == i_other.hash);
}


