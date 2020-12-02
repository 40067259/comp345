#pragma once
#include <stdio.h>
#include <iostream>
#include <list>
#include "C:\Users\amadeus\source\repos\part1\part1\Player\Player.h"
#include "GameEngine.h"

using namespace std;

class Player;
class GameEngine;

//=====Observer Abstract Class====//
/**
 This is the controller. Classes that have (inherit) the observer listen to what's happening in the Subject class,
 They then update themselves accordingly
 */
class Observer {
public:
	~Observer();
	virtual void update() = 0;

protected:
	Observer();

};

//=====Subject Class=====//
/**
 This is the model. This is the class that the observers listen to and make updates.
 */
class Subject {
public:
	Subject();
	~Subject();
	virtual void addObserver(Observer *o);
	virtual void removeObserver(Observer *o);
	virtual void notify();
private:
	list<Observer*> *observersList;
};


//=====Phase Observer====//
/**
 This observes the phase changes
 */
class PhaseObserver : Observer {
public:
	PhaseObserver(GameEngine *gameEngine);
	~PhaseObserver();
	void update();
private:
	GameEngine* _gameEngine;

};


//=====Statistics Observer=====//
/**
 This observes the game stats
 */
class StatisticsObserver : Observer {
public:
	StatisticsObserver(GameEngine *gameEngine);
	~StatisticsObserver();
	void update();
private:
	GameEngine* _gameEngine;

};
