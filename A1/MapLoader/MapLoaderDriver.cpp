#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <fstream>
using std::cout;

int main() {

	MapLoader maploader;
	//map.loadMap("google.map");
	maploader.loadMap("france.map");
	//map.loadMap("estonia.map");

	cout << "\n";

	maploader.map.printMapInfo();
	cout << std::endl;
	
	maploader.map.printMap();
	cout << std::endl;

	system("pause");
	
}
