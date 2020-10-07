#pragma once

#include <vector>
#include "Map.h"

class Territory;
class Player;
struct Node;

class Continent 
{
public:
	Continent(std::string name, int nativeArmy);
	~Continent();
	int getNativeArmy() const;
	void addTerritory(Node& Territory);
	std::string getName() const;
	void printTerritory();
	bool owner(const Player* player);
	std::vector<Node*> getTerritories() const;

private:
	int nativeArmy;
	std::string continentName;
	std::vector<Node*> territories;
};
