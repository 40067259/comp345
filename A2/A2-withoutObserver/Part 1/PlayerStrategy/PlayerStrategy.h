#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"

class PlayerStrategy
{
	PlayerStrategy();
};

class HumanPlayerStrategy : public PlayerStrategy
{
	HumanPlayerStrategy();
	~HumanPlayerStrategy();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
	AggressivePlayerStrategy();
	~AggressivePlayerStrategy();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
	BenevolentPlayerStrategy();
	~BenevolentPlayerStrategy();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
	NeutralPlayerStrategy();
	~NeutralPlayerStrategy();
};
