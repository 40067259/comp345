#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <fstream>
using std::cout;

int main() {

	MapLoader map;
	map.loadMap("google.map");
	//map.loadMap("france.map");
	//map.loadMap("estonia.map");

	cout << "\n";

	map.printMapInfo();
	cout << std::endl;
	
	map.printMap();
	cout << std::endl;

	system("pause");
	
}
