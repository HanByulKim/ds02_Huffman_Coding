#include "Heap.h"

Heap::Heap(int n){
	size = 0;
	idx = 1;
	list = new Node[n+1];
}
Heap::~Heap(){
	delete list;
}

bool Heap::isEmpty(){
	if (size == 0) return true;
	return false;
}

int Heap::getSize(){ return size; }

void Heap::insert(char cat, int freq){
	list[idx].n = cat;
	list[idx].freq = freq;
	idx++;
	size++;
	upheap();
}

void Heap::insert(Node& ins){ //
	list[idx] = ins;
	idx++;
	size++;
	upheap();
}

void Heap::upheap(){
	upheap(idx - 1);
}

void Heap::upheap(int i){
	if (i <= 1) return;
	else if (list[i / 2].freq > list[i].freq){
		Node temp = list[i/2];
		list[i / 2] = list[i];
		list[i] = temp;
		upheap(i / 2);
	}
}

void Heap::deletion_for_tree(){
	Node temp1 = list[1];
	list[1] = list[idx - 1];
	list[idx - 1].n = std::numeric_limits<char>::max();
	list[idx - 1].freq = std::numeric_limits<int>::max();
	
	idx--;
	size--;
	downheap();
	//print();

	Node temp2 = list[1];
	list[1] = list[idx-1];
	list[idx - 1].n = std::numeric_limits<char>::max();
	list[idx - 1].freq = std::numeric_limits<int>::max();

	idx--;
	size--;
	downheap();
	//print();

	Node temp3(temp1.freq + temp2.freq);
	temp3.left = new Node(temp1.n, temp1.freq, temp1.left, temp1.right);
	temp3.right = new Node(temp2.n, temp2.freq, temp2.left, temp2.right);
	insert(temp3);
	//print();
}

void Heap::downheap(){
	downheap(1);
}

void Heap::downheap(int i){

	if (2*i > idx - 1) return;
	else if (list[2*i].freq < list[2*i+1].freq){
		if (list[2 * i].freq < list[i].freq){
			Node temp = list[2*i];
			list[2*i] = list[i];
			list[i] = temp;
			downheap(2*i);
		}
	}
	else{
		if (list[2 * i + 1] .freq < list[i].freq){
			Node temp = list[2 * i+1];
			list[2 * i+1] = list[i];
			list[i] = temp;
			downheap(2 * i+1);
		}
	}
}

void Heap::traverse(KeyMap& keymap){
	list[1].traverse(keymap);
}

void Heap::print(){
	std::cout << std::endl;
	for (int i = 1; i < idx; i++){
		std::cout << i << " : " << list[i].n <<  " " << list[i].freq << std::endl;
	}
	std::cout << "size : " << size << std::endl;
	std::cout << "idx : " << idx << std::endl;
}