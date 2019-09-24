#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <conio.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // _DEBUG

// This is only a simple unit test.

//Function Declarations
char* MakeSentence();
char* MakeSentence(const char*[]);
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

	char * pSentence = MakeSentence();
	//char * pSentence = MakeSentence( strings );

	printf( "The Sentence is: %s and its size is: %d ", pSentence, len(pSentence));


	free( pSentence );

	_getch();
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

//Overload for input string
char* MakeSentence() {
	
}

//default implementation
char* MakeSentence(const char* strings[]) {
	//Find the size required to allocate
	int numOfChars = 0;
	for (int i = 0; i < len(strings); ++i) {
		numOfChars += len(strings[i]);
	}
	
	//Allocate that amount of memory
	char* sentence = (char*) malloc(sizeof(char) * (numOfChars + len(strings) + 1));
	//Create the sentence
	int charCount = 0;
	int wordCount = 0;
	int writeCount = 0;
	while (wordCount < len(strings)) {
		if (charCount < len(strings[wordCount])) {
			sentence[writeCount] = strings[wordCount][charCount];
			charCount++;
		}
		else {
			wordCount++;
			charCount = 0;
			if(writeCount == numOfChars + len(strings) - 1)
				sentence[writeCount] = '.';
			else
				sentence[writeCount] = ' ';
		}
		writeCount++;
	}
	sentence[writeCount] = '\0';
	
	return sentence;
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