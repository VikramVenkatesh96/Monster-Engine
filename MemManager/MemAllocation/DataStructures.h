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

