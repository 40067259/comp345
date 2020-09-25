#include "Map.h"
#include "Player.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Territory> Map::getTerritories() const {
	return territories;
}

std::vector<std::vector<bool>> Map::getAdjacencyMatrix() const {
	return adjacencyMatrix;
}

std::vector<Territory> Map::getContinent(const std::string& continentName) const {
	const std::vector<int> indices = continents.at(continentName);
	std::vector<Territory> names;
	for (int index : indices) {
		names.push_back(territories[index]);
	}

	return names;
}

int Map::getContinentValue(const std::string& continentName) const {
	return continentValues.find(continentName)->second;
}

std::vector<std::string> Map::getContinentNames() const {
	std::vector<std::string> continentNames;
	for (const auto& kv : continents) {
		continentNames.push_back(kv.first);
	}

	return continentNames;
}

std::vector<Territory> Map::adjacent(const Territory& territory) const {
	std::vector<Territory> adjacentTerritories;
	// Find index of the specified territory.
	int territoryIndex;
	for (territoryIndex = 0; territoryIndex < territories.size(); ++territoryIndex) {
		if (territory == territories[territoryIndex]) break;
	}

	// Get row of the adjacency matrix.
	std::vector<bool> indices = adjacencyMatrix[territoryIndex];

	// Iterate over this row. Every time a true value is encountered, push the territory onto the vector.
	for (int i = 0; i < indices.size(); ++i) {
		if (indices[i]) {
			adjacentTerritories.push_back(territories[i]);
		}
	}

	return adjacentTerritories;
}

std::vector<Territory>
Map::adjacentInContinent(const Territory& territory, const std::string& continent) const {
	std::vector<Territory> adjacentTerritories;
	// Find index of the specified territory.
	int territoryIndex;
	for (territoryIndex = 0; territoryIndex < territories.size(); ++territoryIndex) {
		if (territory == territories[territoryIndex]) break;
	}

	// Get row of the adjacency matrix.
	std::vector<bool> indices = adjacencyMatrix[territoryIndex];

	// Iterate over this row. Every time a true value is encountered, push the territory onto the vector.
	for (int i = 0; i < indices.size(); ++i) {
		if (indices[i]) {
			auto continentIndices = continents.at(continent);
			// Check to make sure the index i is in continentIndices before adding the territory.
			for (int continentIndex : continentIndices) {
				if (continentIndex == i) {
					adjacentTerritories.push_back(territories[i]);
					break;
				}
			}
		}
	}

	return adjacentTerritories;
}

std::vector<std::string> Map::continentsOwned(const Player& player) const {
	std::vector<std::string> continentsOwned;
	const std::vector<Territory>& playerTerritories = player.getTerritories();
	std::vector<int> playerTerritoryIndices;

	// Add territory indice from the player's territories if the player owns the territory
	for (int i = 0; i < territories.size(); ++i) {
		const auto Territory = territories[i];
		if (std::find(playerTerritories.begin(), playerTerritories.end(), Territory) != playerTerritories.end()) {
			playerTerritoryIndices.push_back(i);
		}
	}

	// Add continent name to continentsOwned if player owns all territories in the continent
	for (const auto& kv : continents) {
		const auto continentName = kv.first;
		const auto& continentIndices = kv.second;

		if (std::is_permutation(playerTerritoryIndices.begin(), playerTerritoryIndices.end(), continentIndices.begin(), continentIndices.end())) {
			continentsOwned.push_back(kv.first);
		}
	}

	return continentsOwned;
}

void Map::print() const {
	std::cout << "Territories:\n";
	for (int i = 0; i < territories.size(); ++i) {
		std::cout << i << ' ' << territories[i].getName() << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Adjacency Matrix:\n";
	for (int row = 0; row < adjacencyMatrix.size(); ++row) {
		for (int col = 0; col < adjacencyMatrix.size(); ++col) {
			std::cout << adjacencyMatrix[row][col] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Continents:\n";
	for (const auto& kv : continents) {
		std::cout << kv.first << ": ";
		std::vector<int> indices = kv.second;
		for (int index : indices) {
			std::cout << territories[index].getName() << ' ';
		}
		std::cout << std::endl;
	}
}

