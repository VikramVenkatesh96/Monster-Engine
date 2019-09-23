#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // _DEBUG

// This is only a simple unit test.

//Function Declarations
char* MakeSentence(char*[]);

void MakeSentence(const char*[]);

template<class T>
int len(T*);

int main( int i_argc, char ** i_argl )
{
	printf("Running with args: %d , %s\n", i_argc, i_argl[0]);

	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	} ;

	//char * pSentence = MakeSentence( strings );
	MakeSentence(strings);
	//printf( "The Sentence is: %s", pSentence );

	//free( pSentence );

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

//Overload for input string
//char* MakeSentence(char* strings[]) {
//	
//}
//default implementation
void MakeSentence(const char* strings[]) {
	//Find the size required to allocate
	int size = 0;
	for (int i = 0; i < len(strings); ++i) {
		size += (len(strings[i]) + 1);
	}
	
	//Allocate that amount of memory
	char* sentence = (char*) malloc(sizeof(char) * size);

	//Create the sentence
	int count = 0;
	while (count < size) {
		sentence[count] = strings[]
	}
}

// Function to find length of any type of array or list
template <class T>
int len(T* array) {
	int counter = 0;
	while (array[counter] != NULL) {
		counter++;
	}
	return counter;
}