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
#include <experimental/filesystem>//for c++14
namespace fs = std::experimental::filesystem;
#include "GameObservers.hpp" //NEW

class GameEngine : public Subject {
public:
    GameEngine();
    ~GameEngine();
    void GameStart();
    void mapSelection();
    void playerSelection();
    vector<Player*> getPlayersVector();
    Map* myMap;
    vector<Player*> playersVector;
    void randomOrderOfPlayers();
    void territoriesAssignment();
    void armiesInitialization();
    void gameStartupPhase();
    int getNbOfPlayers();
    bool getObserverStatus();
    Deck* getDeckCards();
    void startupPhase(); // for part 2
    
    //added for part 3
    void mainGameLoop();
    void reinforcementPhase();
    void issuingOrderPhase();
    void ordersExectionPhase();
    bool ownsContinent();
    //added for part 3
    
    //added for part 5
    string getPhase(); //NEW
    void setPhase(string s); //NEW
    PhaseObserver *phaseScreen; //NEW
    StatisticsObserver *statisticsScreen; //NEW
    Map* getMap(); //NEW
    //added for part5


private:
    string phase; //NEW
    std::string selectedMap;
    int numberOfPlayers;
    bool activateObservers;
    Deck* deckCards;
    vector<string> mapNames;
    MapLoader* mapLoader;
    std::string currentphase;
    void switchObserver();//NEW
    void setObserver(bool value); //NEW
};
