#include "DataStructures.h"
#include<iostream>
#include<assert.h>
#include<stdlib.h>			//using for free()

//LinkedList Functions
LinkedList::LinkedList()
{
	length = 0;
	start = NULL;
}

void LinkedList::insert(LinkedListNode * node)
{
	if (start == NULL) {
		start = node;
	}
	else {
		LinkedListNode * temp = start;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
	}
	length++;
}
//Overloaded instance for inserting at an index
void LinkedList::insert(LinkedListNode * node, unsigned int index)
{
	assert(index < length);

	if (index == 0) {
		node->next = start;
		start = node;
	}
	else {
		LinkedListNode * temp = start;
		//goto previous node
		for (unsigned int i = 0; i < index - 1; ++i) {
			temp = temp->next;
		}
		//create the necessary links
		LinkedListNode * temp1 = temp->next;
		temp->next = node;
		node->next = temp1;
	}
	length++;
}


void LinkedList::remove()
{
	//Check for existence
	assert(length > 0);

	LinkedListNode * temp = start;
	if (length > 1)
		start = start->next;
	else
		start = NULL;
	free(temp);                       //Manage memory
	length--;
}

//Overloaded instance for removing from an index
void LinkedList::remove(unsigned int index)
{
	//Check for existence
	assert(length > 0);
	//Check if index in range
	assert(index < length);
	LinkedListNode * temp = start;
	if (length == 1)
		start = NULL;
	else {
		//goto previous node
		for (unsigned int i = 0; i < index - 1; ++i) {
			temp = temp->next;
		}
		LinkedListNode * temp1 = temp->next;
		temp->next = temp1->next;
		free(temp1);				//Manage Memory
	}
	length--;
}

unsigned int LinkedList::GetLength() {
	return length;
}

LinkedListNode * LinkedList::GetAt(unsigned int index) {
	LinkedListNode * returnNode = start;
	for (unsigned int i = 0; i < index; ++i) {
		returnNode = returnNode->next;
	}
	return returnNode;
}
//LinkedList Functions End

//BinarySearchTree Functions
BinarySearchTree::BinarySearchTree()
{
	size = 0;
	root = NULL;
}

void BinarySearchTree::Insert(BinarySearchTreeNode * node)
{
	if (root == NULL) {
		root = node;
	}
	else {
		BinarySearchTreeNode * temp = root;
		//navigate through the tree to find correct leaf
		while (true) {
			if (node->value <= temp->value) {
				if (temp->lChild == NULL)
					break;
				else
					temp = temp->lChild;
			}
			else {
				if (temp->rChild == NULL)
					break;
				else
					temp = temp->rChild;
			}			
		}
		//Add that node to the leaf
		if (node->value <= temp->value)
			temp->lChild = node;
		else
			temp->rChild = node;	
	}
	//Increase size		
	size++;
}

//Modify this for a more specific removal
void BinarySearchTree::Remove(int value)
{
	assert(size > 0);
	bool elementFound = false;
	bool rootNodeDeletion = false;
	BinarySearchTreeNode * temp = root;
	//Check if root to be removed
	if (value == temp->value) {
		elementFound = true;
		rootNodeDeletion = true;
	}
	else {
		//Climb Tree to find node
		while (true) {
			if (temp == NULL) {
				break;
			}
			else {
				if (temp->lChild != NULL && temp->lChild->value == value) {
					elementFound = true;
					break;
				}
				else {
					if (temp->rChild != NULL && temp->rChild->value == value) {
						elementFound = true;
						break;
					}
					else {
						if (value < temp->value) {
							temp = temp->lChild;
						}
						else {
							temp = temp->rChild;
						}
					}
				}
			}
		}
	}
	//Make sure the node exists in the tree
	assert(elementFound);
	if (rootNodeDeletion) {
		if (temp->lChild == NULL && temp->rChild == NULL) {
			BinarySearchTreeNode * temp1 = temp;
			root = NULL;
			free(temp1);						//Manage Memory
		}
		else {

			BinarySearchTreeNode * successor = FindSuccessor(temp);
			if (temp->lChild == NULL || successor->value != temp->lChild->value)
				successor->lChild = temp->lChild;
			if(temp->rChild == NULL || successor->value != temp->rChild->value)
				successor->rChild = temp->rChild;
			BinarySearchTreeNode * temp1 = temp;
			root = successor;
			free(temp1);						//Manage Memory
		}
	}
	else {
		if (temp->lChild !=NULL && temp->lChild->value == value) {
			if (temp->lChild->lChild == NULL && temp->lChild->rChild == NULL) {
				BinarySearchTreeNode * temp1 = temp->lChild;
				temp->lChild = NULL;
				free(temp1);					//Manage Memory
			}
			else {
				BinarySearchTreeNode * successor = FindSuccessor(temp->lChild);
				if (size > 3) {
					if(successor->value != temp->lChild->lChild->value)
						successor->lChild = temp->lChild->lChild;
					if(successor->value != temp->lChild->rChild->value)
						successor->rChild = temp->lChild->rChild;
				}
				BinarySearchTreeNode * temp1 = temp->lChild;
				temp->lChild = successor;
				free(temp1);					//Manage Memory
			}
		}
		else {
			if (temp->rChild->lChild == NULL && temp->rChild->rChild == NULL) {
				BinarySearchTreeNode * temp1 = temp->rChild;
				temp->rChild = NULL;
				free(temp1);					//Manage Memory
			}
			else {
				BinarySearchTreeNode * successor = FindSuccessor(temp->rChild);
				if (size > 3) {
					if (successor->value != temp->rChild->lChild->value)
						successor->lChild = temp->rChild->lChild;
					if (successor->value != temp->rChild->rChild->value)
						successor->rChild = temp->rChild->rChild;
				}
				BinarySearchTreeNode * temp1 = temp->rChild;
				temp->rChild = successor;
				free(temp1);					//Manage Memory
			}
		}
	}
	size--;
}

BinarySearchTreeNode * BinarySearchTree::FindSuccessor(BinarySearchTreeNode * node) {
	BinarySearchTreeNode * parentOfSuccessor = node;
	BinarySearchTreeNode * successor;
	if (node->rChild == NULL) {
		successor = node->lChild;
		while (true)
		{
			if (successor->rChild == NULL) {
				break;
			}
			else {
				parentOfSuccessor = successor;
				successor = successor->rChild;
			}
		}
		if (parentOfSuccessor->value != root->value && parentOfSuccessor->value != node->value) {
			if (successor->lChild != NULL) {
				parentOfSuccessor->rChild = successor->lChild;
			}
			else {
				parentOfSuccessor->rChild = NULL;
			}
		}
	}
	else
	{
		successor = node->rChild;
		while (true)
		{
			if (successor->lChild == NULL) {
				break;
			}
			else {
				parentOfSuccessor = successor;
				successor = successor->lChild;
			}
		}
		if (parentOfSuccessor->value != root->value && parentOfSuccessor->value != node->value) {
			if (successor->rChild != NULL) {
				parentOfSuccessor->lChild = successor->rChild;
			}
			else {
				parentOfSuccessor->lChild = NULL;
			}
		}
	}
	return successor;
}

unsigned int BinarySearchTree::GetSize()
{
	return size;
}

void BinarySearchTree::PrintPreOrder()
{
	PrintPreOrder(root);
}
void BinarySearchTree::PrintPreOrder(BinarySearchTreeNode * node)
{
	if (node == NULL) {
		return;
	}
	else {
		std::cout << node->value << "->";
		PrintPreOrder(node->lChild);
		PrintPreOrder(node->rChild);
	}
}
void BinarySearchTree::PrintInOrder()
{
	PrintInOrder(root);
}
void BinarySearchTree::PrintInOrder(BinarySearchTreeNode * node)
{
	if (node == NULL) {
		return;
	}
	else {
		PrintInOrder(node->lChild);
		std::cout << node->value << "->";
		PrintInOrder(node->rChild);
	}
}
//BinarySearchTree Functions End