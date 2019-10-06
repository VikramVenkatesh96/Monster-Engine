#include "DataStructures.h"
#include<assert.h>
#include<stdlib.h>			//using for free()

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