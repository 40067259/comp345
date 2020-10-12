#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include <string>
#include <fstream>

int main() {
	MapLoader map;
	map.loadMapAlt("google.map");
	//map.loadMap("france.map");
	//map.loadMap("estonia.map");
	map.printMapInfo();
	std::cout << std::endl;
	map.printMap();
	std::cout << std::endl;
	
	system("pause");
}
