#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include <string>
#include <fstream>
using namespace std;

int main() {
	MapLoader map;
	map.loadMap("estonia.map");
	map.printMapInfo();
	cout << endl;
	map.printMap();
	cout << endl;
	
	system("pause");
}