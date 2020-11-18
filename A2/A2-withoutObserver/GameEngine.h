
#pragma once
#include "Player.h"
//#include "GameObservers.h"
#include "MapLoader.h"
#include<iostream>
#include<string>
#include <fstream>
#include <cstdint>
#include <filesystem>

namespace fs = std::experimental::filesystem;
class GameEngine {
public:
	// Constructors
	GameEngine();
	~GameEngine();
	void GameStart();

	// Accessors
	int getNbOfPlayers();
	Deck* getDeckCards();
	vector<Player*> getPlayersList();
	bool getObserverStatus();
	void mapSelection();
	void playerSelection();
	void randomOrderOfPlayers();
	void territoriesAssignment();
	void armiesInitialization();
	void gameStartupPhase();

private:
	std::string selectedMap;
	int nbOfPlayers;
	Deck* deckCards;
	vector<Player*> players;
	bool activateObservers;
	Map* gameMap;
	MapLoader* mapLoader;
	vector<string> mapNames;
	std::string currentphase;
};