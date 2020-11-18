#pragma once

#include <string>

class Player;
class Continent;

class Territory
{
public:
	Territory();
	Territory(std::string territoryName, Continent& cont, int a, int i);
	~Territory();
	Continent* getContinent() const;
	std::string getName() const;
	int getArmies() const;
	int getIndex() const;
	void setArmies(int a) { armies = a; }
	void addArmies(int a);
	void removeArmies(int a);
	Player* getOwner() const;
	void setOwner(Player* player);

private:
	Continent* continent;
	std::string name;
	int armies;
	int index;
	Player* owner;
};