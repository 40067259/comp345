#include "Continent.h"
#include "Player.h"
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

int Continent::numOfTerritories() {
	return territories.size();
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

// check if a territory in this continent
bool Continent::checkTerritory(std::string n)
{
	for (int i = 0; i < territories.size(); i++){
		if (n == territories[i]->territory->getName()) {
			return true;
		}		
	}
	return false;
}


bool Continent::owner(Player* player)
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

vector<Node*> Continent::getTerritories() const
{
	return territories;
}
