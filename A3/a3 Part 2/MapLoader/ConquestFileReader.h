#pragma once
#include<iostream>
#include<string>
#include"..\Map\Map.h"
using std::string;

class ConquestFileReader {
	
public:
	ConquestFileReader();
	ConquestFileReader(const string& location);
	~ConquestFileReader();
	void loadMap(string fileInput);

private:
	Map map;
	string location;
	string current;
	int line;
	bool parseContinentBlock(std::ifstream& stream);
	bool parseTerritoryBlock(std::ifstream& stream);

};
