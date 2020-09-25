#include "MapLoader.h"
#include "Map.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

namespace {
	std::vector<std::string> split(const std::string &input, char delim) {
		std::stringstream ss(input);
		std::string segment;
		std::vector<std::string> contents;
		while (std::getline(ss, segment, delim)) {
			contents.push_back(segment);
		}
		return contents;
	}
}

Map MapLoader::loadMap(std::string filename) {
	Map map;

	std::ifstream ifs(filename);
	std::string line;

	// Get the continents.
	while (std::getline(ifs, line) && line != "[Continents]") {}
	while (std::getline(ifs, line) && line != "") {
		const int equalsIndex = line.find('=');
		const std::string continent = line.substr(0, equalsIndex);
		const int value = std::stoi(line.substr(equalsIndex + 1));
		map.continents.insert({ continent, std::vector<int>() });
		map.continentValues.insert({ continent, value });
	}

	// Get all the territories.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		// Get the territory name.
		if (line != "") {
			const int commaIndex = line.find(',');
			const std::string territoryName = line.substr(0, commaIndex);
			const auto territory = Territory(territoryName);
			// Confirm that territory is unique.
			if (std::find(map.territories.begin(), map.territories.end(), territory) != map.territories.end()) {
				std::cerr << "Duplicate territory detected: " << territoryName << std::endl;
				return Map();
			}
			map.territories.push_back(territory);
		}
	}

	// Re-read file.
	ifs.clear();
	ifs.seekg(0, ifs.beg);

	// Initialize the adjacency matrix.
	map.adjacencyMatrix.resize(map.territories.size(), std::vector<bool>(map.territories.size()));

	// Set adjacencyMatrix and continents territory by territory.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		if (line == "") {
			continue;
		}

		// Split the line by comma.
		const std::vector<std::string> splitLine = split(line, ',');

		const std::string territoryName = splitLine[0];
		const std::string continentName = splitLine[3];

		// Get index for territory.
		const auto territoryIt = std::find(map.territories.begin(),
			map.territories.end(),
			territoryName);
		const int territoryIndex = territoryIt - map.territories.begin();

		// Associate territory with continent.
		try {
			map.continents.at(continentName).push_back(territoryIndex);
		}
		// Exception is thrown if continent does not exist.
		catch (...) {
			std::cerr << "Invalid continent detected: " << continentName << " for territory: " << territoryName << std::endl;
			return Map();
		}

		// Iterate over the remaining strings in splitLine; those respresent
		// the territories adjacent to the current territory.
		for (int i = 4; i < splitLine.size(); ++i) {
			const std::string otherTerritory = splitLine[i];
			// Get territory index.
			const auto otherTerritoryIt = std::find(map.territories.begin(),
				map.territories.end(),
				otherTerritory);
			const int otherTerritoryIndex = otherTerritoryIt - map.territories.begin();

			// Check for uniqueness.
			if (otherTerritoryIndex >= map.territories.size()) {
				std::cerr << "Duplicate territory detected: " << otherTerritory << std::endl;
				return Map();
			}

			map.adjacencyMatrix[territoryIndex][otherTerritoryIndex] = true;
		}
	}

	// Check that the adjacency matrix is valid.
	for (int row = 0; row < map.adjacencyMatrix.size(); ++row) {
		for (int col = row; col < map.adjacencyMatrix.size(); ++col) {
			if (map.adjacencyMatrix[row][col] != map.adjacencyMatrix[col][row]) {
				std::cerr << "There are territories with adjacent territories that don't match.\n";
				return Map();
			}
		}
	}

	return map;
}
