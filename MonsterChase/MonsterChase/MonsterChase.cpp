#include "IO.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#ifdef _DEBUG
#include <ctype.h>
#include <crtdbg.h>
#endif // _DEBUG

// This is only a simple unit test.
#define _CRTDBG_MAP_ALLOC
//Function Declarations
char* MakeSentence();
char* MakeSentence(const char*[]);
void CopyStrings(char*, char*, int, int);
template<class T>
int len(T*);

int main(int i_argc, char ** i_argl)
{
	//Did this to remove unsused params warning
	printf("Running with args: %d , %s\n", i_argc, i_argl[0]);
	
	char c = 'n';
	char * pSentence = nullptr;

	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	//char * pSentence = MakeSentence( strings ); //To be used for const strings like the one above
	printf("\nEnter your sentence word-by-word, pressing enter at the end of each word.\n End the sentence by giving enter as the input.\n");
	do{	
		switch (c) {
			case 'n': {
				pSentence = MakeSentence();

				if (pSentence[0] == '0') {
					printf("Nothing was Inputed\n");
				}
				else {
					printf("The Sentence is: %s and its size is: %d ", pSentence, len(pSentence));
				}
				free(pSentence);
				break;
			}
			case 'y': break;
			
			default: {
				printf("\nEnter a valid choice!\n");
			}
		}
		printf("Do you want to quit?(y/n): ");
		c = (char)getchar();
		c =(char)tolower(c);
	} while (c != 'y');

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

//Overload for input string
char* MakeSentence() {
	//Init Sentence with nullptr
	char * sentence = nullptr;
	bool isEmptyString = true;
	// Infinitely take input and keep storing in sentence untill user ends it.
	while (true) {
		char* temp = (char*)malloc(sizeof(char));
		bool isEmpty = IO::TakeStringInput(temp);
		printf("\n");
		//printf("%d", len(temp));
		if (isEmpty) {
			free(temp);
			break;
		}
		else
		{
			//No reallocs to be used so used CopyString func to copy strings and paste it to temp
			//first backup copy the strings if sentence is not empty and then copy the new word to sentence by starting from the end index
			
			//printf("%d", size);
			if (!isEmptyString) {
				int size = len(sentence);
				char* temp1 = (char*)malloc(sizeof(char) * size);
				CopyStrings(temp1,sentence,size,0);
				free(sentence);
				sentence = (char*)malloc(sizeof(char) * (size + len(temp) + 2));
				CopyStrings(sentence, temp1, size,0);
				free(temp1);
				CopyStrings(sentence, temp, len(temp), size);
				sentence[size + len(temp)] = ' ';
				sentence[size + len(temp) + 1] = '\0';
			}
			else {
				sentence = (char*)malloc(sizeof(char) * (len(temp) + 2));
				CopyStrings(sentence, temp, len(temp), 0);
				sentence[len(temp)] = ' ';
				sentence[len(temp) + 1] = '\0';
			}
			
			isEmptyString = false;
		}
		free(temp);
	}
	//Handle case when nothing is inputed
	if (isEmptyString) {
		free(sentence);
		char* empty = (char*)malloc(sizeof(char));
		*empty = '0';
		return empty;
	}
	else
	{
		int length = len(sentence);
		sentence[length-1] = '.';
		return sentence;
	}	
}

//default implementation
char* MakeSentence(const char* strings[]) {
	//Find the size required to allocate
	int numOfChars = 0;
	for (int i = 0; i < len(strings); ++i) {
		numOfChars += len(strings[i]);
	}
	
	//Allocate that amount of memory
	char* sentence = (char*) malloc(sizeof(char) * (numOfChars + len(strings) + 1));	//(total number of raw characters + number of spaces and period + end of sentence )

	//Create the sentence
	int charCount = 0;
	int wordCount = 0;
	int writeCount = 0;
	//iterate over the words and store all characters in sentence
	while (wordCount < len(strings)) {
		if (charCount < len(strings[wordCount])) {
			sentence[writeCount] = strings[wordCount][charCount];
			charCount++;
		}
		else {
			wordCount++;
			charCount = 0;
			// Logic to add spaces and period
			if (writeCount == numOfChars + len(strings) - 1)
				sentence[writeCount] = '.';
			else
				sentence[writeCount] = ' ';
		}
		writeCount++;
	}
	//End of sentence
	sentence[writeCount] = '\0';

	return sentence;
}

void CopyStrings(char* dest, char* src, int length, int startOffset) {
	for (int i = 0; i < length; ++i) {
		dest[startOffset + i] = src[i];
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
