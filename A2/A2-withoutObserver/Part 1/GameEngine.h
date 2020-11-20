#pragma once
#include "C:\Users\amadeus\source\repos\part1\part1\Player\Player.h"
//#include "GameObservers.h"
#include "C:\Users\amadeus\source\repos\part1\part1\MapLoader\MapLoader.h"
#include "C:\Users\amadeus\source\repos\part1\part1\Map\Map.h"
#include<iostream>
#include<string>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <experimental/filesystem>//for c++14
namespace fs = std::experimental::filesystem;

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void GameStart();
	void mapSelection();
	void playerSelection();
	vector<Player*> getPlayersVector();
	Player* getPlayer(std::string name);
	Map* myMap;
	vector<Player*> playersVector;
	int getNbOfPlayers();
	bool getObserverStatus();
	void startupPhase(); // for part 2

	//added for part 3
	void mainGameLoop();
	void reinforcementPhase();
	void issuingOrderPhase();
	void ordersExectionPhase();
	//added for part 3


private:
	std::string selectedMap;
	int numberOfPlayers;
	bool activateObservers;
	Deck* deckCards;
	vector<string> mapNames;
	MapLoader* mapLoader;
	std::string currentphase;
};


