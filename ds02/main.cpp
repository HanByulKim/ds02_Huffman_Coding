/**
*********************************************
2016 Autumn DataStructure HW02
SNU Dept. of Electrical & Computer Engineering
2014-13261
Han-Byul Kim
*********************************************
Rev. log.
look for https://github.com/HanByulKim/ds02_Huffman_Coding
*********************************************
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Heap.h"
#include "KeyMap.h"

int* Rscript(int& cnt); // Reading Script function
std::string CleanLine(const std::string& n); // Sub-function of Rscript
std::string Enscript(KeyMap& keymap); // Encoding function
std::string Decscript(KeyMap& keymap); // Decoding function

void main(){
	std::cout << "*********************************************" << std::endl << "2016 Autumn DataStructure HW02" << std::endl << "SNU Dept. of Electrical & Computer Engineering" << std::endl << "2014-13261" << std::endl << "Han - Byul Kim" << std::endl << "*********************************************" << std::endl << "Rev. log." << std::endl << "look for https://github.com/HanByulKim/ds02_Huffman_Coding" << std::endl << "*********************************************" << std::endl;
	/** 1. Building Tree **/
	int* freq;
	int cnt = 0;
	freq = Rscript(cnt);
	/*for (int i = 0; i < 30; i++)
		std::cout << freq[i] << ", ";*/

	// Constructing Heap
	Heap heap(cnt);
	for (char i = 0; i < 26; i++)
		if(freq[i] != 0) heap.insert((char)(i + 97), freq[i]);
	if (freq[26] != 0) heap.insert('-', freq[26]);
	if (freq[27] != 0) heap.insert(',', freq[27]);
	if (freq[28] != 0) heap.insert('.', freq[28]);
	if (freq[29] != 0) heap.insert('+', freq[29]);

	std::cout << "--------------------------------------------" << std::endl << "     Heap" << std::endl << "--------------------------------------------" << std::endl;
	heap.print(); // Printing Heap

	// Building Tree
	int fin = heap.getSize();
	for (int i = 1; i < fin; i++){
		heap.deletion_for_tree();
	}

	// Constructing encoded keymap
	KeyMap keymap(cnt);
	heap.traverse(keymap);
	std::cout << "--------------------------------------------" << std::endl << "     Binary Mapping Table" << std::endl << "--------------------------------------------" << std::endl;
	keymap.print(); // Printing Encoding Map
	
	// encoding message
	std::cout << "--------------------------------------------" << std::endl << "     Encoding" << std::endl << "--------------------------------------------" << std::endl;
	std::cout << Enscript(keymap) << std::endl;

	// decoding message
	std::cout << "--------------------------------------------" << std::endl << "     Decoding" << std::endl << "--------------------------------------------" << std::endl;
	std::cout << Decscript(keymap) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	system("pause");
}

int* Rscript(int& cnt){
	int* freq = new int[30]; for (int i = 0; i < 30; i++) { freq[i] = 0; }
	std::string filename = "source.txt";
	std::stringstream ss;
	std::string str, cleanstr;

	std::ifstream file(filename);

	if (file){ // Same as Try Catch Exception
		while (!file.eof()) {
			std::getline(file, str);

			// Clean each line.
			cleanstr = CleanLine(str);

			// Pass the cleaned-up string into a stringstream, to parse out the data elements.
			ss.clear();
			// Stringstream will parse directly on whitespace.

			// 0~25 : a-z, 26 : space, 27 : comma, 28 : dot, 29 : new line
			for (int i = 0; i < str.length(); i++){
				switch (str.at(i)){
				case '\0':
					freq[26]++;
					break;
				case ',':
				case 32:
					freq[27]++;
					break;
				case '.':
					freq[28]++;
					break;
				default:
					freq[str.at(i) - 97]++;
				}
			}
			freq[29]++;	// for end of line
		}
	}
	else{ std::cout << "Wrong File!" << std::endl; }
	for (int i = 0; i < 30; i++) if (freq[i] != 0)cnt++;

	return freq;
}

std::string Enscript(KeyMap& keymap){
	std::string filename = "message.txt";
	std::stringstream ss;
	std::string str, cleanstr;
	std::string res="";

	std::ifstream file(filename);

	if (file){ // Same as Try Catch Exception
		while (!file.eof()) {
			std::getline(file, str);
			std::cout << str << std::endl << " -> ";

			// Clean each line.
			cleanstr = CleanLine(str);

			// Pass the cleaned-up string into a stringstream, to parse out the data elements.
			ss.clear();
			// Stringstream will parse directly on whitespace.

			// 0~25 : a-z, 26 : space, 27 : comma, 28 : dot, 29 : new line
			for (int i = 0; i < str.length(); i++){
				if (str.at(i) == '\0') str.at(i) = '-';
				if (str.at(i) == '\n') str.at(i) = '+';
				res = res + keymap.find(str.at(i));
			}
		}
	}
	else{ std::cout << "Wrong File!" << std::endl; }

	return res;
}

std::string Decscript(KeyMap& keymap){
	std::string filename = "binary.txt";
	std::stringstream ss;
	std::string str, cleanstr;
	std::string res = "";
	int border = 0;

	std::ifstream file(filename);

	if (file){ // Same as Try Catch Exception
		while (!file.eof()) {
			std::getline(file, str);
			std::cout << str << std::endl << " -> ";

			// Clean each line.
			cleanstr = CleanLine(str);

			// Pass the cleaned-up string into a stringstream, to parse out the data elements.
			ss.clear();
			// Stringstream will parse directly on whitespace.

			// 0~25 : a-z, 26 : space, 27 : comma, 28 : dot, 29 : new line
			keymap.init();
			for (int i = 0; i < str.length(); i++){
				//if (str.at(i) != 0 && str.at(i) != 1){ std::cout << "Exception:Wrong Word." << std::endl; break; }
				if (!keymap.findbinary(str.at(i), res)){ std::cout << "Wrong Word" << std::endl; }
			}
		}
	}
	else{ std::cout << "Wrong File!" << std::endl; }

	return res;
}

std::string CleanLine(const std::string& n){
	std::string cleanline;
	char* char_line = (char*)n.c_str(); // Non-const cast required.

	char* token = NULL;
	char* context = NULL;
	char  delims[] = " ,\t\n";

	// During the first read, establish the char string and get the first token.
	token = strtok_s(char_line, delims, &context);

	// While there are any tokens left in "char_line"...
	while (token != NULL)
	{
		// Accumulate the tokens.
		cleanline += token;
		cleanline += ' ';

		// NOTE: NULL, function just re-uses the context after the first read.
		token = strtok_s(NULL, delims, &context);
	}

	return cleanline;
}