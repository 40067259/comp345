#include <iostream>
#include <list>
//#include "Player.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

int Map::size() const
{
	return map.size();
}

int Map::continentSize() const
{
	return continents.size();
}


std::unordered_map<std::string, Continent> Map::getContinents() const
{
	return continents;
}

bool Map::addEdge(std::string terr, Territory& newTerritory)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].territory->getName() == terr)
		{
			Edge e;
			e.territory = &newTerritory;
			map[i].adjList.push_back(e);
			return true;
		}
	}
	return false;
}

std::pair<Territory*, bool> Map::addTerritory(std::string territoryName, std::string continentName, int armies, int index)
{
	Territory* t = new Territory(territoryName, getContinent(continentName),armies, index);
	std::pair<std::string, Territory*> pair(territoryName, t);
	if (!auxStorage.insert(pair).second)
	{
		return std::make_pair(t, false);
	}

	Node n;
	n.territory = getTerritory(territoryName);
	map.push_back(n);

	return std::make_pair(t, true);
}

bool Map::addContinent(std::string continentName, int nativeArmy)
{
	Continent continent = Continent(continentName, nativeArmy);
	std::pair<std::string, Continent> pair(continent.getName(), continent);
	return continents.insert(pair).second;
}

Continent& Map::getContinent(std::string continentName)
{
	std::unordered_map<std::string, Continent>::iterator found = continents.find(continentName);

	return found->second;
}

Territory* Map::getTerritory(std::string territoryName)
{
	std::unordered_map<std::string, Territory*>::iterator found = auxStorage.find(territoryName);

	return found->second;
}

Territory* Map::getTerritory(int index)
{
	return map[index].territory;
}

void Map::printMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		std::cout << map[i].territory->getName() << "belongs to continent (" << map[i].territory->getContinent()->getName() << ")" << std::endl;
		std::cout << "\tIt's adjacent territories are:"  << std::endl;

		for (int j = 0; j < map[i].adjList.size(); j++)
		{
			std::cout << "\t" << map[i].adjList[j].territory->getName() << "(" << map[i].adjList[j].territory->getContinent()->getName() << ")" << std::endl;
		}

		std::cout << std::endl;
	}
}

void Map::clearMap()
{
	map.clear();
	auxStorage.clear();
	continents.clear();
}

bool Map::addTerritoriesToContinents()
{
	for (Node& n : map)
	{
		std::string name = n.territory->getContinent()->getName();
		if (!continents.count(name))
		{
			return false;
		}
		getContinent(name).addTerritory(n);
	}
	return true;
}

//Prints info about the armies in each Territory
void Map::printMapInfo()
{
	for (int i = 0; i < size(); i++)
	{
		//See who owns the Territory
		Territory* t = getTerritory(i);
		std::cout << t->getName() << std::endl;
		//std::cout << t->getName() << "'s owner is " << t->getOwner()->getName() << std::endl;
	}
}

bool Map::validate()
{
	// check if the map is a connected graph 
	// by verifying if every node/territory can reach all the rest nodes/territories
	for (int i = 0; i < map.size(); i++)
	{
		std::string t1 = map[i].territory->getName();
		for (int i1 = 0; i1 < map.size(); i1++) {
			std::string t2 = map[i1].territory->getName();
			if (!reachable(t1, t2)) {
				std::cout << "This is not a connected graph." << std::endl;
				return false;
			}
		}
	}
	std::cout << "This is a connected graph." << std::endl;

	// check if continents are connected subgraphs
	// by verifying all continents contain at least one territory
	// since continents contain territories and all territories are connected
	for (auto& m : continents) {
		if (m.second.numOfTerritories()==0) {
			std::cout << "Continents are not connected subgraphs." << std::endl;
			return false;
		}
	}
	std::cout << "Continents are connected subgraphs." << std::endl;

	// verify all territories should belong to at least one continent
	for (int x = 0; x < map.size(); x++)
	{
		if (map[x].territory->getContinent() == nullptr) {
			return false;
		}
	}
	// check each territory belongs to only one continent
	for (int k = 0; k < size(); k++)
	{
		std::string t3 = map[k].territory->getName();
		std::string c = map[k].territory->getContinent()->getName();
		for (auto& n : continents) {
			if (n.second.checkTerritory(t3) && (c != n.first)) {
				std::cout << "There exists a country that not belongs to one unique continent." << std::endl;
				return false;
			}
		}
	}
	std::cout << "Each country belongs to one and only one continent." << std::endl;
	std::cout << "Map validity is verified. This map has no issue." << std::endl;
	return true;
}

// Check if a source territory can reach a destinatation territory
bool Map::reachable(std::string source, std::string destination)
{
	if (source == destination)
		return true;

	// Keep track of visited territories.
	std::unordered_map<std::string, bool> visited;

	//initialize them all to false
	std::unordered_map<std::string, Territory*>::iterator beg = auxStorage.begin();
	for (beg; beg != auxStorage.end(); ++beg)
	{
		std::pair<std::string, bool> pair(beg->first, false);
		visited.insert(pair);
	}

	//Create a queue and mark the source as visited
	std::list<std::string> queue;
	visited[source] = true;
	queue.push_back(source);

	while (!queue.empty())
	{
		std::string name = queue.front();
		queue.pop_front();

		//Get edges 
		std::vector<Edge>::iterator i = getNodeFromMap(name).adjList.begin();
		for (i; i != getNodeFromMap(name).adjList.end(); ++i)
		{
			// If this adjacent node is the destination node, then 
			// return true
			if (i->territory->getName() == destination)
				return true;

			if (!visited[i->territory->getName()])
			{
				visited[i->territory->getName()] = true;
				queue.push_back(i->territory->getName());
			}
		}
	}

	return false;
}

//Search the map for a Node by name of the territory
Node& Map::getNodeFromMap(std::string territoryName)
{
	for (int y = 0; y < map.size(); y++)
	{
		if (map[y].territory->getName() == territoryName)
		{
			return map[y];
		}
	}
	std::cout << "error, cannot find the territory in this map." << std::endl;
	return map[0];	
}
