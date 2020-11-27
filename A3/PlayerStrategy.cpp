#include <iostream>
#include <fstream>
#include <string>
#include "PlayerStrategy.h"

//======================================PlayerStrategy======================================
PlayerStrategy::PlayerStrategy()
{
	p = new Player();
}
PlayerStrategy::PlayerStrategy(Player* p)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made
}
PlayerStrategy::~PlayerStrategy()
{
}
//======================================PlayerStrategy======================================


//======================================HumanPlayerStrategy======================================
HumanPlayerStrategy::HumanPlayerStrategy():PlayerStrategy()
{
	p = new Player();
}
HumanPlayerStrategy::HumanPlayerStrategy(Player* p):PlayerStrategy(p)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made
}
HumanPlayerStrategy::~HumanPlayerStrategy()
{
	delete p;
}
//======================================HumanPlayerStrategy======================================

//======================================AggressivePlayerStrategy======================================
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
	
}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made

	//strategy
	p->toAttack(); 
	//need to modify toAttack method
	//need to remove the argument
	//so that it can be used in the AggressivePlayerStrategy
	//and everytime the player use toAttack()
	//ask which territory the player would like to attack
}
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
	delete p;
}
//======================================AggressivePlayerStrategy======================================

//======================================BenevolentPlayerStrategy======================================
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
	p = new Player();
}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made

	//strategy
	p->toDefend();
}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
	delete p;
}
//======================================BenevolentPlayerStrategy======================================

//======================================NeutralPlayerStrategy======================================
NeutralPlayerStrategy::NeutralPlayerStrategy()
{
	p = new Player();
}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made

	//strategy
	p->toSkip();
	//need to add a toSkip method to the player class
	//so that player can still rounds
	//which means issue no order

}
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
	delete p;
}
//======================================NeutralPlayerStrategy======================================
