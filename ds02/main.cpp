/**
*********************************************
2016 Autumn DataStructure HW02
SNU Dept. of Electrical & Computer Engineering
2014-13261
Han-Byul Kim
*********************************************
Rev. log.
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Heap.h"

int* Rscript(int& cnt);
std::string CleanLine(const std::string& n);

void main(){
	int* freq;
	int cnt = 0;
	freq = Rscript(cnt);
	for (int i = 0; i < 30; i++)
		std::cout << freq[i] << ", ";

	// Heap Construct
	Heap heap(cnt);
	for (char i = 0; i < 26; i++)
		if(freq[i] != 0) heap.insert((char)(i + 97), freq[i]);
	if (freq[26] != 0) heap.insert(' ', freq[26]);
	if (freq[27] != 0) heap.insert(',', freq[27]);
	if (freq[28] != 0) heap.insert('.', freq[28]);
	if (freq[29] != 0) heap.insert('\n', freq[29]);

	heap.print();

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
					freq[27]++;
					break;
				case '.':
					freq[28]++;
					break;
				default:
					freq[str.at(i) - 97]++;
				}
			}
			freq[29]++;// for end of line
		}
	}
	else{ std::cout << "Wrong File!" << std::endl; }
	for (int i = 0; i < 30; i++) if (freq[i] != 0)cnt++;

	return freq;
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