#pragma once

class Observer {

public:
    Observer();
	~Observer();
	virtual void notifyPhase(int) = 0;
    virtual void notifyGame(int) = 0;
};
