#include "IO.h"
#include "MemoryManager.h"
#include <conio.h>
IO::IO()
{
}
bool IO::TakeStringInput(char* string) {
	char c;
	int index = 0;
	while ((c = (char)_getche()) != '\r') {
		index++;
		string = (char*)MemoryManager::IncreaseMem(string, sizeof(char)*(index + 1));
		string[index - 1] = c;
		string[index] = '\0';
	}
	if (index > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
