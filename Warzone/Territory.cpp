#include "Territory.h"


Territory::Territory(const Territory& c) {
	name = c.name;
	armies = c.armies;
}

std::string Territory::getName() const {
	return name;
}

void Territory::setName(const std::string& name) { //this so can differentiate both names same as doing name = n
	this->name = name;
}

bool Territory::operator==(const Territory& other) const { //sees if 2 territory objects are equal based on name
	return name == other.name;
}

bool Territory::operator<(const Territory& second) const { //overloads operator when comparing two territory objects it compares their names
	return name < second.name;
}
void Territory::increaseArmies() //increase amount of armies on this territory
{
	++armies;
}

int Territory::getArmies() const {
	return armies;
}
void Territory::setArmies(int n) //set armies on this territory
{
	armies = n;
}

void Territory::increaseArmiesBy(int n) {
	armies += n;
}

void Territory::decreaseArmiesBy(int n) {
	armies -= n;
}