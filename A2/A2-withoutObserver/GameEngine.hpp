#pragma once
#include <stdio.h>
#include <iostream>
#include "Map.h"
#include "MapLoader.h"


class MapLoader;
class GameEngine {
public:
    GameEngine();
    void GameStart();
    
private:
    Map *map;
    int numberOfPlayers;
    vector<Player*> players;
    bool IsObserverOn;
    void mapSelection();
    void playerSelection();

    
    
}


