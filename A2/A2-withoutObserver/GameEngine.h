#pragma once
#include "Player.h"
#include "GameObservers.h"
#include<iostream>
using namespace std;

class GameEngine : public Observable{
    public:
        // Constructors
        GameEngine();
        void GameStart();

        // Accessors
        int getNbOfPlayers();
        Deck* getDeckCards();
        vector<Player*> getPlayersList();
        bool getObserverStatus();
        void setObserverStatus(bool status);
        Map* getMap();
        void setPhase(string s);
        string getPhase();

        // Methods
        void startupPhase();
        void mainGameLoop();
        
    private:
        int nbOfPlayers;
        Deck* deckCards;
        vector<Player*> players;
        bool activateObservers;
        Map* gameMap;
        bool isMapInDirectory(string fileName);
        bool equals(const string& a, const string& b);
        void setNbOfPlayers();
        void toggleObservers();
        string selectMap();
        string currentphase;
};


