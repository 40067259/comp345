#include "Map.h"
#include "MapLoader.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Map map = MapLoader::loadMap("swiss.map");
	map.printMapInfo();
	cout << endl;
	map.printMap();
	cout << endl;
	
	system("pause");
}