#pragma once
#include<iostream>
#include"MapLoader.h"
#include "ConquestFileReader.h"

class ConquestFileReaderAdapter : public MapLoader {
private:
	ConquestFileReader conquestReader;
public:
	ConquestFileReaderAdapter();
	~ConquestFileReaderAdapter();
	ConquestFileReaderAdapter(ConquestFileReader);
	void loadMap(std::string path);
};
