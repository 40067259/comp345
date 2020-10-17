#include "Continent.h"
//#include "Player.h"
#include <iostream>

using std::vector;

Continent::Continent(std::string name, int na)
{
	continentName = name;
	nativeArmy = na;
}

Continent::~Continent()
{
}

std::string Continent::getName() const
{
	return continentName;
}


int Continent::getNativeArmy() const
{
	return nativeArmy;
}

void Continent::addTerritory(Node& node)
{
	territories.push_back(&node);
}

void Continent::printTerritory()
{
	for (int i = 0; i < territories.size(); i++)
	{
		std::cout << territories[i]->territory->getName() << "'s adjacent territories: " << std::endl;

		for (int j = 0; j < territories[i]->adjList.size(); j++)
		{
			std::cout << "\t" << territories[i]->adjList[j].territory->getName() << std::endl;
		}

		std::cout << std::endl;
	}
}

/*
bool Continent::owner(const Player* player)
{
	for (Node* n : territories)
	{
		if (n->territory->getOwner()->getName() != player->getName())
		{
			return false;
		}
	}
	return true;
}
*/
vector<Node*> Continent::getTerritories() const
{
	return territories;
}
