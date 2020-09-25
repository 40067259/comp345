#pragma once

#include "Territory.h"
#include "MapLoader.h"
#include <string>
#include <unordered_map>
#include <vector>

class Player;

class Map {
private:
	std::vector<Territory> territories;
	std::vector<std::vector<bool>> adjacencyMatrix;
	// continents is a map between strings (representing the continent name) and a vector of ints (representing the indices into territories).
	std::unordered_map<std::string, std::vector<int>> continents;
	// continentValues is a map between strings (for continent names) and their values.
	std::unordered_map<std::string, int> continentValues;

public:
	std::vector<Territory> getTerritories() const;

	std::vector<std::vector<bool>> getAdjacencyMatrix() const;

	std::vector<Territory> getContinent(const std::string& continentName) const;

	int getContinentValue(const std::string& continentName) const;

	std::vector<std::string> getContinentNames() const;

	std::vector<Territory> adjacent(const Territory& territory) const;

	std::vector<Territory>
	adjacentInContinent(const Territory& territory, const std::string& continent) const;

	std::vector<std::string> continentsOwned(const Player& player) const;

	void print() const;

	friend Map MapLoader::loadMap(std::string filename);
};
