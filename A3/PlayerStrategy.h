#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "GameEngine.h"

class PlayerStrategy
{
public:
	PlayerStrategy();
	PlayerStrategy(Player* p, GameEngine* g);
	~PlayerStrategy();

protected:
	Player* p;
	GameEngine* gE;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* p, GameEngine* g);
	~HumanPlayerStrategy();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	AggressivePlayerStrategy();
	AggressivePlayerStrategy(Player* p, GameEngine* g);
	~AggressivePlayerStrategy();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(Player* p, GameEngine* g);
	~BenevolentPlayerStrategy();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(Player* p, GameEngine* g);
	~NeutralPlayerStrategy();
};
