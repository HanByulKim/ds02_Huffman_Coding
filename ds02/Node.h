#pragma once
#include <limits>
#include <iostream>

class Node{
public:
	Node(){
		n = std::numeric_limits<char>::max();
		freq = std::numeric_limits<int>::max();
	}
	Node(int f) :n(std::numeric_limits<char>::max()), freq(f){}
	Node(char c, int f) :n(c), freq(f){}
	Node(char c, int f, Node*& l, Node*& r) :n(c), freq(f), left(l), right(r){}

	Node& Node::operator=(const Node& b){
		this->n = b.n;
		this->freq = b.freq;
		this->left = b.left;
		this->right = b.right;
		return (*this);
	}

	void traverse(){	// itself as root
		traverse(left);
		traverse(right);
		if (left == NULL&&right == NULL)
			std::cout << n << " : " << freq << std::endl;
	}
	void traverse(Node* tvl){
		if (tvl == NULL) return;
		traverse(tvl->left);
		traverse(tvl->right);
		if (tvl->left == NULL&&tvl->right == NULL)
			std::cout << n << " : " << freq << std::endl;
	}
	char n;
	int freq;

	// For Building Tree
	Node* left = NULL;
	Node* right = NULL;
};