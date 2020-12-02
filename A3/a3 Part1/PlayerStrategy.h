#pragma once
#include<vector>
#include<iostream>
#include<map>
#include"Hand.h"
#include"Deck.h"
#include"Card.h"
#include"Continent.h"
#include"Map.h"
#include"MapLoader.h"
#include"Orders.h"
#include"OrdersList.h"
#include"Player.h"
#include"Territory.h"

class Map;

using namespace std;

class PlayerStrategy {
public:
	PlayerStrategy();
	~PlayerStrategy();
	virtual vector<Territory*>* toDefend(Player *p) = 0;
	virtual vector<Territory*>* toAttack(Player *p,Map *map) = 0;
	virtual void issueOrder(Player *p) = 0;
};

class HumanPlayerStrategy :public PlayerStrategy {
public:
	HumanPlayerStrategy();
	~HumanPlayerStrategy();
	vector<Territory*>* toDefend(Player* p);
	vector<Territory*>* toAttack(Player* p, Map* map);
	void issueOrder(Player* p);
	
};

class AggressivePlayerStrategy :public PlayerStrategy {

public:
	AggressivePlayerStrategy();
	~AggressivePlayerStrategy();
	vector<Territory*>* toDefend(Player* p);
	vector<Territory*>* toAttack(Player* p, Map* map);
	void issueOrder(Player* p);
};

class BenevolentPlayerStrategy :public PlayerStrategy {
public:
	BenevolentPlayerStrategy();
	~BenevolentPlayerStrategy();
	vector<Territory*>* toDefend(Player* p);
	vector<Territory*>* toAttack(Player* p, Map* map);
	void issueOrder(Player* p);
};

class NeutralPlayerStrategy :public PlayerStrategy {
public:
	NeutralPlayerStrategy();
	~NeutralPlayerStrategy();
	vector<Territory*>* toDefend(Player* p);
	vector<Territory*>* toAttack(Player* p, Map* map);
	void issueOrder(Player* p);
};