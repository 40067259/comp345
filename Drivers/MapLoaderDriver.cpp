#include <iostream>
#include "../Risk/Map.h"
#include "../Risk/MapLoader.h"
#include <string>
#include <fstream>
using namespace std;

int main() {
	MapLoader map;
	map.loadMap("Ressources/estonia.map");
	//map.loadMap("france.map");
	//map.loadMap("google.map");
	map.printMapInfo();
	cout << endl;
	map.printMap();
	cout << endl;
	
	system("pause");
}
