#pragma once
#include <iostream>
#include <string>

class Map;
class MapLoader: public Map
{
public:
    MapLoader();
    ~MapLoader();
    MapLoader loadMap(std::string fileInput);
};
