#pragma once
#include "Player.h"
//#include "GameObservers.h"
#include "MapLoader.h"
#include "Map.h"
#include<iostream>
#include<string>
#include <fstream>
#include <cstdint>
#include <filesystem>

class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    void GameStart();
    void mapSelection();
    void playerSelection();
    vector<Player*> getPlayersVector();
    void randomOrderOfPlayers();
    void territoriesAssignment();
    void armiesInitialization();
    void gameStartupPhase();

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


