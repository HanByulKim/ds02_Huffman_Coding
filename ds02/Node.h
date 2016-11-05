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

	void traverse(KeyMap& keymap){	// itself as root
		keymap.addtemp('0');
		traverse(left, keymap);
		keymap.deltemp();
		keymap.addtemp('1');
		traverse(right, keymap);
		keymap.deltemp();
		if (left == NULL&&right == NULL){
			keymap.assign(n);
			std::cout << keymap--.n << " : " << keymap++.key << std::endl;
		}
	}
	void traverse(Node* tvl, KeyMap& keymap){
		if (tvl == NULL) return;
		keymap.addtemp('0');
		traverse(tvl->left, keymap);
		keymap.deltemp();
		keymap.addtemp('1');
		traverse(tvl->right, keymap);
		keymap.deltemp();
		if (tvl->left == NULL&&tvl->right == NULL){
			keymap.assign(tvl->n);
			std::cout << keymap--.n << " : " << keymap++.key << std::endl;
	}

	char n;
	int freq;

	// For Building Tree
	Node* left = NULL;
	Node* right = NULL;
};