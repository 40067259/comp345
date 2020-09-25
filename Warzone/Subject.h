#pragma once
#include "Player.h"
#include <list>

class Observer;

class Subject {
private:
	std::list<Observer*> *_observers;
    int phase;
    int totalTerritories;

protected:
	Subject();

public:
	virtual ~Subject();
	virtual void attach(Observer *);
	virtual void detach(Observer *);
	virtual void notifyPhaseAll();
    virtual void notifyGameAll();
    virtual void setPhase(int& phase);
    virtual void setTotalTerritories(int amt);
};