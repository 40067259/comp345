#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <fstream>
using std::cout;

int main() {
	/*
	To use the MapLoader class to load map, the following steps will be followed:
	1) Create 1 MapLoader Object
	2) Use the loadMap() method, and put the .map file inside the argument
	3) Ensure that the .map files are in the same folder of the program
	4) Once the .map file is successfully loaded, the map variable will have the information from the input
	5) Further operation can be performed with the map
	*/
	
	// [A maploader object is created to load map]
	MapLoader maploader;
	// [A maploader object is created to load map]

	// [To loap different map from .map file] 
	maploader.loadMap("canada.map");
	//maploader.loadMap("europe.map");
	//maploader.loadMap("us.map");
	// [To loap different map from .map file] 
	
	//***
	// Remarks: The .map files has to be placed inside the same directory, 
	// but not only in the "Resource Files" folder in order to read the .map files
	//***

	cout << "\n";

	// [To use the "printMapInfo()" method from the Map class]
	maploader.map.printMapInfo();
	// [To use the "printMapInfo()" method from the Map class]

	cout << std::endl;
	
	// [To use the "printMap()" method from the Map class]
	maploader.map.printMap();
	// [To use the "printMap()" method from the Map class]

	cout << std::endl;

	// [Indicate that this part is done]
	cout << "End" << "\n";
	// [Indicate that this part is done]

	system("pause");
	
}
