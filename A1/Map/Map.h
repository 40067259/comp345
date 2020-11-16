#pragma once

#include "Territory.h"
#include "Continent.h"
#include <unordered_map>

struct Edge
{
	Territory* territory;
};

struct Node
{
	Territory* territory;
	std::vector<Edge> adjList;
};

class Map
{
public:

	Map();
	~Map();
	int size() const;
	int continentSize() const;
	std::unordered_map<std::string, Continent> getContinents() const;
	bool addEdge(std::string terr, Territory& newCountry);
	std::pair<Territory*, bool> addTerritory(std::string TerritoryName, std::string continentName, int armies, int index);
	bool addContinent(std::string continentName, int nativeArmy);
	Continent& getContinent(std::string continentName);
	Territory* getTerritory(std::string territoryName);
	Territory* getTerritory(int index);
	void printMap();
	void clearMap();
	bool addTerritoriesToContinents();	
	void printMapInfo();
	bool validate();
	bool reachable(std::string source, std::string destination);
	Node& getNodeFromMap(std::string countrytName);
	std::unordered_map<std::string, Continent> getContinents() const;


private:
	std::unordered_map<std::string, Territory*> auxStorage;
	std::unordered_map<std::string, Continent> continents;
	std::vector<Node> map;
};

