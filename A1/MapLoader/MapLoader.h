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

    // [MapLoader default constructor]
    MapLoader();
    // [MapLoader default constructor]
    
    // [MapLoader destructor]
    ~MapLoader();
    // [MapLoader destructor]

    // [There is a Map object as a variable in a MapLoader object]
    Map map;
    // [There is a Map object as a variable in a MapLoader object]    
    
    // [The method to load .map file into a Map object which is a variable of the MapLoader object]
    void loadMap(string fileInput);
    // [The method to load .map file into a Map object which is a variable of the MapLoader object]

};
