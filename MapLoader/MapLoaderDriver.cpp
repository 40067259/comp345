#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include <string>
#include <fstream>
#include <queue>
#include <set>
using namespace std;

int main() {
	Map map = MapLoader::loadMap("estonia.map");
	map.printMapInfo();
	cout << endl;
	map.printMap();
	cout << endl;
	
	system("pause");
}