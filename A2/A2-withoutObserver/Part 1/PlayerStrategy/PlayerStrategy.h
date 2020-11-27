#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"

class PlayerStrategy
{
public:
	PlayerStrategy();
	PlayerStrategy(Player* p);
	~PlayerStrategy();

protected:


};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* p);
	~HumanPlayerStrategy();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	AggressivePlayerStrategy();
	AggressivePlayerStrategy(Player* p);
	~AggressivePlayerStrategy();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(Player* p);
	~BenevolentPlayerStrategy();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(Player* p);
	~NeutralPlayerStrategy();
};
