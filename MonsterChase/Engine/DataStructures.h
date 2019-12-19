#pragma once
#include "stdlib.h"

template <class T>
struct ListNode
{
	T* value;
	ListNode* next;
};

template <class T>
class List
{

public:
	List() 
	{
		start = nullptr;
		length = 0;
	}

	void Add(T* nodeValue)
	{
		{
			ListNode<T>* node = (ListNode<T>*)malloc(sizeof(ListNode<T>));
			node->value = nodeValue;
			node->next = nullptr;

			if (length == 0)
			{
				start = node;
			}
			else
			{
				ListNode<T>* iterator = start;
				while (iterator->next != nullptr)
				{
					iterator = iterator->next;
				}

				iterator->next = node;
			}
			length++;
		}
	}
	
	bool Remove(T* nodeValue)
	{
		bool found = false;
		ListNode<T>* nodeToDelete = nullptr;
		if (start->value == nodeValue)
		{
			nodeToDelete = start;
			start = start->next;
			found = true;
		}
		else 
		{
			ListNode<T>* iterator = start;
			while (iterator->next->value != nodeValue && iterator != nullptr)
			{
				iterator = iterator->next;
			}
			if (iterator != nullptr)
			{
				nodeToDelete = iterator->next;
				iterator->next = nodeToDelete->next;
				found = true;
			}
			else
			{
				found = false;
			}
		}
		if (found)
		{
			length--;
			nodeToDelete->next = nullptr;
			T* temp = nodeToDelete->value;
			free(nodeToDelete);
		}
		return found;
	}

	bool Remove(unsigned int index)
	{
		
		unsigned int count = 0;
		if (index == 0)
		{
			ListNode<T>* temp = start;
			start = start->next;
			delete temp->value;
			temp->next = nullptr;
			free(temp);
		}
		else
		{
			ListNode<T>* iterator = start;
			while (count < index - 1)
			{
				iterator = iterator->next;
			}
			ListNode<T>* temp = iterator->next;
			iterator->next = temp->next;
			temp->next = nullptr;
			free(temp);
		}
		length--;
		return true;
	}

	void RemoveAll()
	{
		unsigned int index = 0;
		while (length > 0)
		{
			Remove(index);
		}
	}

	unsigned int GetLength()
	{
		return length;
	}
	
	ListNode<T>* start;
private:
	
	unsigned int length;
};
