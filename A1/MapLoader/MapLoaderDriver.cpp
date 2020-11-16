#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include <fstream>
using std::cout;

int main() {

	// [A maploader object is created to load map]
	MapLoader maploader;
	// [A maploader object is created to load map]

	// [To loap different map from .map file] 
	maploader.loadMap("google.map");
	//maploader.loadMap("france.map");
	//maploader.loadMap("estonia.map");
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
