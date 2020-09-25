#pragma once
#include <string>

class Map;

class MapLoader {
	public:
		static Map loadMap(std::string filename);
};