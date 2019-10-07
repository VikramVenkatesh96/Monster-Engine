#include "DataStructures.h"
#include <iostream>

int main()
{
	//BinarySearchTree Unit Test
	BinarySearchTree bst;
	int tempValue;
	while (true) {
		std::cout << "Enter a value to input:";
		std::cin >> tempValue;
		if (tempValue == -1)
			break;
		BinarySearchTreeNode * node = (BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));
		node->value = tempValue;
		node->lChild = NULL;
		node->rChild = NULL;
		bst.Insert(node);
	}
	std::cout << std::endl;
	bst.PrintPreOrder();
	std::cout << std::endl;
	bst.PrintInOrder();
	
	int size = bst.GetSize();
	while (size > 0) {
		std::cout << " Enter key to delete:";
		std::cin >> tempValue;
		if (tempValue == -1)
			break;
		bst.Remove(tempValue);
		size--;
		if (size == 0) {
			std::cout << "No more elements exist in the tree";
		}
		else {
			std::cout << std::endl;
			bst.PrintPreOrder();
			std::cout << std::endl;
			bst.PrintInOrder();
		}
	}
	//List Unit Test
	/*LinkedList list;
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
	}*/
	
}
