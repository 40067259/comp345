#pragma once
#include <iostream>
#include <string>
using namespace std;


class Map;
class MapLoader
{
public:
    static Map MapLoader::loadMap(std::string fileInput);
};