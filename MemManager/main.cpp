// Don't worry I did it for you
#include "UnitTests.h"
#include <conio.h>
#include <iostream>

void main(int i_argc, char ** i_argl)
{
	if (UnitTests::HeapManager_UnitTest())
	{
		std::cout << "Unit Test Succeded!" << std::endl;
	}
	_getch();
}