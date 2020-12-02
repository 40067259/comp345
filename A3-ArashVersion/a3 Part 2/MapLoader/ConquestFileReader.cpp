#include<iostream>
#include <iterator>    
#include <vector>       
#include"ConquestFileReader.h"
#include"..\Map\Map.h"
#include <fstream>
#include <string>
#include <sstream>

using std::vector;
using std::string;

ConquestFileReader::ConquestFileReader(const string& loc) : current(""),  line(0)
{
	location = loc;
}

ConquestFileReader::ConquestFileReader(){
}

// destructor
ConquestFileReader::~ConquestFileReader()
{
}

// A function to split string by a delimiter
template <typename Out>
void split(const std::string &s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}
vector<string> split( string &s, char delim) {
	vector<string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

//load map
void ConquestFileReader::loadMap(string location) {

	std::ifstream stream(location);

	// [To check if the file is opened]
	if (!stream.is_open())
	{
		std::cout << location << " is not opened" << "\n";
		return;
	}

	//try to load map
	if(parseContinentBlock(stream) && parseTerritoryBlock(stream)){
		stream.close();
		if (map.size() == 0)
		{
			std::cout<< "This map contains no territories."<<std::endl;
		}
		else if (map.continentSize() == 0)
		{
			std::cout << "This map contains no continents." << std::endl;
		}
		else {
			std::cout << "Successfully load the conquest map." << std::endl;
		}	
	}
	else {
		std::cout << "Cannot load the conquest map." << std::endl;
	}
	
}
// Parses the [Continents] block 
bool ConquestFileReader::parseContinentBlock(std::ifstream& stream)
{
	// [to get the continents section]
	while (getline(stream, current))
	{
		if (current == "[Continents]")
		{
			break;
		}
	}
	
	for (line++; getline(stream, current) && current != "[Territories]"; line++)
	{
		if (current.size() == 0) { continue; }
		vector<string> splits = split(current, '=');

		if (splits.size() != 2)
		{
			std::cout<< "Wrong line format, incorrect amount of equal signs "<<std::endl;
			return false;
		}
		if (!map.addContinent(splits[0], stoi(splits[1])))
		{
			std::cout << "Dupplicate Continent " + splits[0] + " detected " + std::to_string(line) << std::endl;
			return false;
		}

		if (current == "[Territories]"){ break;}
			
	}
	
	return true;
}



// Parses the [Territories] block 
bool ConquestFileReader::parseTerritoryBlock(std::ifstream& stream)
{
	vector<std::pair<string, Territory*>> edges;

	while (getline(stream, current))
	{
		if (current.size() == 0) { continue; }
		vector<string> splits = split(current, ',');

		//There should at lease be a name, two coordinates, a continent, and one adjacent territory
		if (splits.size() < 5)
		{
			std::cout<< "Invalid amount of Territory data @" + line<<std::endl;
			return false;
		}

		std::pair<Territory*, bool> p = map.addTerritory(splits[0], splits[3], stoi(splits[1]), stoi(splits[2]));
		if (!p.second)
		{
			std::cout<< "Dupplicate Territory " + splits[0] + " detected @" + std::to_string(line)<<std::endl;
			return false;
		}

		for (int i = 4; i < splits.size(); i++)
		{
			edges.push_back(make_pair(splits[i], p.first));
		}
	}

	//Setup edges and continents
	for (std::pair<string, Territory*> p : edges)
	{
		if (!map.addEdge(p.first, *p.second))
		{
			std::cout<<"Could not find the adjacent Territory " + p.first + " to connect to " + p.second->getName()<<std::endl;
			return false;
		}
	}
	if (!map.addTerritoriesToContinents())
	{
		std::cout<< "One of the Territories has an invalid Continent name."<<std::endl;
		return false;
	}
	map.printMap();
	return true;
}
