#include<iostream>
#include"ConquestFileReaderAdapter.h"
#include<string>

ConquestFileReaderAdapter::ConquestFileReaderAdapter(){
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter(){
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader loadmap) {
	conquestReader = loadmap;
}

void ConquestFileReaderAdapter::loadMap(std::string path) {
	conquestReader.loadMap(path);
}