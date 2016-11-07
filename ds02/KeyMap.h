#pragma once
#include "Map.h"

class KeyMap{
public:
	friend class MapIterator;
	KeyMap(int cnt){
		idx = 0;
		MapIterator = 0;
		WordIterator = 0;
		map = new Map[cnt];
		mapseries = new Map[cnt];
	}
	~KeyMap(){ delete map; }

	void addtemp(char a){ temp.push_back(a); }
	void deltemp(){ temp.pop_back(); }
	void assign(char val){ map[idx].add(val, temp); addseries(val, temp); }
	void print(){
		for (int i = 0; i < idx; i++)
			std::cout << map[i].shown() << " : " << map[i].showkey() << std::endl;
		std::cout << std::endl;
	}
	void printseries(){
		for (int i = 0; i < idx; i++)
			std::cout << mapseries[i].shown() << " : " << mapseries[i].showkey() << std::endl;
		std::cout << std::endl;
	}
	std::string find(char word){
		for (int i = 0; i < idx; i++)
			if (map[i].n == word) return map[i].showkey();
	}

	void init(){ MapIterator = 0; WordIterator = 0; }
	bool findbinary(char serial, std::string& res){
		while (MapIterator < idx){
			while (WordIterator < map[MapIterator].size()){
				if (serial != map[MapIterator].at(WordIterator)){
					MapIterator++;
				}
				else{
					if (WordIterator == map[MapIterator].size() - 1){
						res += map[MapIterator].shown();
						init();
						return true;
					}
					WordIterator++;
					return true;
				}
			}
		}
		return false;
	}


	void addseries(char val, std::string a){
		switch (val){
		case '-':
			mapseries[26].add(val, a);
			break;
		case ',':
			mapseries[27].add(val, a);
			break;
		case '.':
			mapseries[28].add(val, a);
			break;
		case '+':
			mapseries[29].add(val, a);
			break;
		default:
			mapseries[val - 97].add(val, a);
			break;
		}
	}

	Map& KeyMap::operator--(int){ return map[idx]; }
	Map& KeyMap::operator++(int){ return map[idx++]; }
	Map& KeyMap::operator[](int i){ return map[i]; }

private:
	Map* map;
	Map* mapseries;
	int idx;
	int MapIterator;
	int WordIterator;
	std::string temp = "";
};