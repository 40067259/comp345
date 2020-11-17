#pragma once
#include <stdio.h>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "MapLoader.h"
#include "Map.h"
using std::vector;

class MapLoader;
class GameEngine {
public:
    GameEngine();
    void GameStart();

private:
    Map* map;
    int numberOfPlayers;
    vector<Player*> playersVector;
    bool IsObserverOn;
    void mapSelection();
    void playerSelection();
    void mainGameLoop();
    void reinforcementPhase();
    void issuingOrderPhase();
    void ordersExectionPhase();
};
//
