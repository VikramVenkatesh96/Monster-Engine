#include "DataStructures.h"
#include <iostream>

int main()
{
	LinkedList list;
	int tempValue;
	while (true) {
		std::cout << "\nEnter value:";
		std::cin >> tempValue;
		if (tempValue == -1)
			break;
		LinkedListNode * node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
		node->value = tempValue;
		node->next = NULL;
		list.insert(node);
	}
	for (unsigned int i = 0; i < list.GetLength(); ++i) {
		std::cout << list.GetAt(i)->value << "->";
	}
	
	for (unsigned int i = 0; i < list.GetLength(); ++i) {
		list.remove();
	}
	int a;
	a = 5;
}
