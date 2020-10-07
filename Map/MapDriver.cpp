#include "Map.h"
//#include "MapLoader.h"
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

int main() {
	Map map;
	//vector<std::pair<string, Territory*>> edges;
	
	// add continents: Bretagne 3, Languedoc-Roussillon 3 
	map.addContinent("Bretagne", 3);
	map.addContinent("Languedoc-Roussillon", 3);
	
	// add territory 56 Morbihan, its adj territories indices: 29 22 35 44
	map.addTerritory("Morbihan", "Bretagne", 2, 56);
	// add territory 29 Finistere 1
	map.addTerritory("Finistere", "Bretagne", 1, 29);
	// 22 Cotes-d-Armor 1
	map.addTerritory("Cotes-d-Armor", "Bretagne", 1, 22);
	// 34 Herault 13 
	map.addTerritory("Herault", "Languedoc-Roussillon", 13, 34);
	// 35 Ille-et-Vilaine 1
	map.addTerritory("Ille-et-Vilaine", "Bretagne", 1, 35);
	
	//Setup edges 
	map.addEdge("Morbihan", * map.getTerritory(1));
	map.addEdge("Morbihan", * map.getTerritory(2));
	map.addEdge("Morbihan", * map.getTerritory(3));
	map.addEdge("Finistere", *map.getTerritory(0));
	map.addEdge("Cotes-d-Armor", *map.getTerritory(0));
	map.addEdge("Herault", *map.getTerritory(0));
	map.addEdge("Ille-et-Vilaine", *map.getTerritory(0));

	//Setup continents
	map.addTerritoriesToContinents();
	
	map.printMapInfo();
	cout << endl;
	map.printMap();
	cout << endl;
	
	system("pause");
}

