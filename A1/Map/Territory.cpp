#include "Territory.h"

Territory::Territory() : continent(nullptr), armies(0), index(0)//, owner(nullptr)
{
}

Territory::Territory(std::string territoryName, Continent& cont, int a, int i) //: owner(nullptr)
{
	index = i;
	name = territoryName;
	continent = &cont;
	armies = a;
}

Territory::~Territory()
{
}

Continent* Territory::getContinent() const
{
	return continent;
}

std::string Territory::getName() const
{
	return name;
}

int Territory::getArmies() const
{
	return armies;
}

int Territory::getIndex() const
{
	return index;
}

void Territory::addArmies(int amount)
{
	armies += amount;
}

void Territory::removeArmies(int amount)
{
	armies -= amount;
}
/*
Player* Territory::getOwner() const
{
	return owner;
}

void Territory::setOwner(Player* player)
{
	owner = player;
}
*/

