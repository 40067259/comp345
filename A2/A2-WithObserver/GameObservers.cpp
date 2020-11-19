#include "GameEngine.h"
#include "GameObservers.hpp"




//=====OBSERVER CLASS====//
Observer::Observer(){};

Observer::~Observer(){};

//=====SUBJECT CLASS=====//
Subject::Subject(){
    observersList = new list<Observer*>;
}

Subject::~Subject(){
    delete observersList;
}

//add observer to the observersList
void Subject::addObserver(Observer *o) {
    observersList->push_back(o);
}
//remove observer from the observersList
void Subject::removeObserver(Observer *o) {
    observersList->remove(o);
}


//notify all of the observers for any change
void Subject::notify(){
    list<Observer*>::iterator iterator = observersList->begin();
    for(; iterator !=observersList->end(); ++iterator) {
        (*iterator)->update();
    }
};

//=====Phase Observer=====//
//Right when you create a phase observer, add it to the list of observers we have
PhaseObserver::PhaseObserver(GameEngine* g){
    _gameEngine = g;
    _gameEngine->addObserver(this);
};

PhaseObserver::~PhaseObserver(){
    _gameEngine->removeObserver(this);
}


//update: display something based on game engine's phase
void PhaseObserver::update(){
    string newPhase = _gameEngine->getPhase();
    cout << "-------------------------------------------------------------"<<endl;
    cout << "------"<< newPhase <<"------------"<<endl;
    cout << "-------------------------------------------------------------"<<endl;
}


//====GAME STATISTICS OBSERVER=====//
//Right when you create a game, add it to the list of observers we have
StatisticsObserver::StatisticsObserver(GameEngine *g) {
    _gameEngine = g;
    _gameEngine->addObserver(this);
}

StatisticsObserver::~StatisticsObserver(){
    _gameEngine->removeObserver(this);
}


//update: this method divides each player's territory with the total map size
void StatisticsObserver::update(){
    int mapSize =  _gameEngine->getMap()->getContinents().size();
    
    for(Player *player : _gameEngine->getPlayersVector()){
        
       int territoriesConquered =  player->getTerritories().size();
       double ratioOfTotal = territoriesConquered/mapSize;
        double ratioAsPercentile = ratioOfTotal*100;
        if(ratioAsPercentile==100) {
            cout<< "Player" << player->getName() << " Owns " << ratioAsPercentile << "% of the total. YOU CONQUERED THE WORLD!" << endl;
        }else{
            cout<< "Player" << player->getName() << " Owns " << ratioAsPercentile << "% of the total. GO CONQUER MORE!" << endl;
        }
        
    }
    
}
