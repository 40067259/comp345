#pragma once
#include <iostream>
#include <string>
using namespace std;

class Map;
class MapLoader: public Map
{
public:
    MapLoader();
    ~MapLoader();
    MapLoader loadMap(string fileInput);
};
