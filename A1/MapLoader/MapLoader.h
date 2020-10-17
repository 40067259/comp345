#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include "Map.h"
using std::string;

//class Map;
class MapLoader/* : public Map*/
{
public:
    MapLoader();
    Map map;
    void loadMap(string fileInput);
    
};
