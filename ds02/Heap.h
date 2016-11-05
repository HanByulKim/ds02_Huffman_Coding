#pragma once
#include "Node.h"
#include "KeyMap.h"

class Heap{
public:
	Heap(int n);
	~Heap();
	bool isEmpty();
	int getSize();
	void insert(char cat, int freq);
	void insert(Node& ins);
	void upheap();
	void upheap(int i);
	void deletion_for_tree();
	void downheap();
	void downheap(int i);
	void traverse(KeyMap& keymap);
	void print(); // for test

	int integrate;

private:
	int size;
	int idx;
	Node* list;
};