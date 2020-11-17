#pragma once

#include <vector>
#include "Map.h"

class Territory;
//class Player;
struct Node;

class Continent
{
public:
	Continent(std::string name, int nativeArmy);
	~Continent();
	int getNativeArmy() const;
	int numOfTerritories();
	void addTerritory(Node& Territory);
	std::string getName() const;
	void printTerritory();
	//bool owner(const Player* player);
	std::vector<Node*> getTerritories() const;
	// check if a territory is in this continent
	bool checkTerritory(std::string n);

private:
	int nativeArmy;
	std::string continentName;
	std::vector<Node*> territories;
};
