#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "..\GameEngine.h"

class GameEngine;

class PlayerStrategy
{
public:
	PlayerStrategy();
	~PlayerStrategy();
	virtual void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) = 0;
	virtual void toDefend(Player* p) = 0;
	virtual void toAttack(Player* p) = 0;

protected:
	Player* p;
	GameEngine* gE;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
	HumanPlayerStrategy();
	~HumanPlayerStrategy();
	void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
	void toDefend(Player* p);
	void toAttack(Player* p);
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	AggressivePlayerStrategy();
	~AggressivePlayerStrategy();
	void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
	void toDefend(Player* p);
	void toAttack(Player* p);
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	BenevolentPlayerStrategy();
	~BenevolentPlayerStrategy();
	void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
	void toDefend(Player* p);
	void toAttack(Player* p);
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	NeutralPlayerStrategy();
	~NeutralPlayerStrategy();
	void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
	void toDefend(Player* p);
	void toAttack(Player* p);
};
