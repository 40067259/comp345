#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include <string>
#include <fstream>

int main() {
	MapLoader map;
	map.loadMap("estonia.map");
	//map.loadMap("france.map");
	//map.loadMap("google.map");
	map.printMapInfo();
	std::cout << std::endl;
	map.printMap();
	std::cout << std::endl;
	
	system("pause");
}
