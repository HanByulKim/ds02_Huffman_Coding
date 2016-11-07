#pragma once
#include <iostream>
#include <string>

class Map{
public:
	Map(){ key = ""; }
	Map(char c) :n(c){ key = ""; }

	void add(char val, std::string a){
		n = val;
		key = a;
	}
	int size(){ return key.length(); }
	char at(int i){ return key.at(i); }
	char shown(){ return n; }
	std::string showkey(){ return key; }

	char n;
	std::string key;
};