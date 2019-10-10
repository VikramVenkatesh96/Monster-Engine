#pragma once

struct LinkedListNode
{
	size_t size;
	void * allocatedMemPtr;
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
	LinkedListNode * remove();
	LinkedListNode * remove(unsigned int);
	unsigned int GetLength();
	LinkedListNode * GetStart();
	LinkedListNode * GetAt(unsigned int);
	void PrintNodes();
	bool FindElement(void *);
};

struct BinarySearchTreeNode {
	int value;
	BinarySearchTreeNode * lChild;
	BinarySearchTreeNode * rChild;
};

class BinarySearchTree
{
private:
	unsigned int size;
	BinarySearchTreeNode * root;
	BinarySearchTreeNode * FindSuccessor(BinarySearchTreeNode *);
	void PrintPreOrder(BinarySearchTreeNode *);
	void PrintInOrder(BinarySearchTreeNode *);
public:
	BinarySearchTree();
	void Insert(BinarySearchTreeNode *);
	void Remove(int);
	unsigned int GetSize();
	//for visualization
	void PrintPreOrder();
	void PrintInOrder();
};

