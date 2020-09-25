#include "Warzone/Map.h"
#include "Warzone/MapLoader.h"
#include <iostream>
#include <queue>
#include <set>

void bfs(const Map& map) {
	std::queue<Territory> toVisit;
	std::set<Territory> visited;
	toVisit.push(map.getTerritories()[0]);

	while (!toVisit.empty()) {
		Territory next = toVisit.front();
		toVisit.pop();
		
		// Skip if node visited.
		if (visited.find(next) != visited.end()) {
			continue;
		}

		std::cout << next.getName() << std::endl;
		visited.insert(next);

		std::vector<Territory> adjacentNodes = map.adjacent(next);
		for (const Territory& territory : adjacentNodes) {
			toVisit.push(territory);
		}
	}
}

void bfs_continent(const Map& map, const std::string& continent) {
	std::queue<Territory> toVisit;
	std::set<Territory> visited;
	toVisit.push(map.getContinent(continent)[0]);

	while (!toVisit.empty()) {
		Territory next = toVisit.front();
		toVisit.pop();

		// Skip if node visited.
		if (visited.find(next) != visited.end()) {
			continue;
		}

		std::cout << next.getName() << std::endl;
		visited.insert(next);

		std::vector<Territory> adjacentNodes = map.adjacentInContinent(next, continent);
		for (const Territory& territory : adjacentNodes) {
			toVisit.push(territory);
		}
	}
}

int main() {
	Map map = MapLoader::loadMap("World.map");
	if (map.getTerritories().size() == 0) {
		std::cerr << "Exiting\n";
		return -1;
	}
	map.print();

	std::cout << std::endl;

	bfs(map);

	std::cout << std::endl;

	for (const auto& continent : map.getContinentNames()) {
		std::cout << "Traversal for " << continent << ": " << std::endl;
		bfs_continent(map, continent);
		std::cout << std::endl;
	}

	system("pause");
}