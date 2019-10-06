#pragma once
struct LinkedListNode
{
	int value;
	LinkedListNode * next;
};

//If using default functions, this acts like a queue
class LinkedList
{
private:
	unsigned int length;
	LinkedListNode * start;
public:
	LinkedList();
	void insert(LinkedListNode *);
	void insert(LinkedListNode *, unsigned int);
	void remove();
	void remove(unsigned int);
	unsigned int GetLength();
	LinkedListNode * GetAt(unsigned int);
};

