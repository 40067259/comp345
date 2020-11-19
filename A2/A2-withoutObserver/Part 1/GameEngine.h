#pragma once
#include "Player.h"
//#include "GameObservers.h"
#include "MapLoader.h"
#include<iostream>
#include<string>
#include <fstream>
#include <cstdint>
#include <experimental/filesystem>  // for C++14
//#include <filesystem>  // for C++17

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void GameStart();
	void mapSelection();
	void playerSelection();
	vector<Player*> getPlayersVector();

	void mainGameLoop();
	void reinforcementPhase();
	void issuingOrderPhase();
	void ordersExectionPhase();
	bool ownsContinent();

private:
	std::string selectedMap;
	int numberOfPlayers;
	Deck* deckCards;
	vector<Player*> playersVector;
	Map* myMap;
	MapLoader* mapLoader;
	vector<string> mapNames;
	std::string currentphase;


};