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
		std::cout << map[i].territory->getName() << " belongs to continent (" << map[i].territory->getContinent()->getName() << ")" << std::endl;
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
