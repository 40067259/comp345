#include <iostream>
#include <fstream>
#include <string>
#include "PlayerStrategy.h"


//======================================PlayerStrategy======================================
PlayerStrategy::PlayerStrategy()
{
	p = new Player();
}
PlayerStrategy::PlayerStrategy(Player* p, GameEngine* g)
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
HumanPlayerStrategy::HumanPlayerStrategy(Player* p, GameEngine* g):PlayerStrategy(p, g)
{
	this->p = p;
	this->gE = g;
	//the normal strategy like the previous one

	// [Asking for orders]
	int orderNb;
	cout << "Issue Order: " << "\n";
	cout << "Enter 1 for 'deploy'\n";
	cout << "Enter 2 for 'advance'\n";
	cout << "Enter 3 for 'bomb'\n";
	cout << "Enter 4 for 'blockade'\n";
	cout << "Enter 5 for 'airlift'\n";
	cout << "Enter 6 for 'negotiate'\n";
	cout << "ENTER 0 TO EXIT\n";
	cout << ">>";
	cin >> orderNb;
	// [Asking for orders]

	// [issue order]
	if (orderNb == 0)
	{
		std::cout << p->getName() << "has pressed \"0\" to exit." << "\n";
	}
	else if (orderNb == 1)
	{
		int numberOfArmies;
		cout << "Enter number of armies you want to deploy:" << endl;
		cin >> numberOfArmies;
		string sourceTerritory;

		cout << "Your territories: " << "\n";
		for (Territory* t : p->getTerritories())
		{
			cout << t->getName() << "\n";
		}
		cout << "\n";

		cout << "Enter name of territory that you want deploy from:" << endl;
		cin >> sourceTerritory;
		string targetTerritory;

		cout << "Enter name of territory that you want deploy to:" << endl;
		cin >> targetTerritory;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(1, p, NULL, p->getMap()->getTerritory(sourceTerritory), p->getMap()->getTerritory(targetTerritory), numberOfArmies);
		//[1. Store order to player's order list]
		//[2. Print out message]           
	}
	else if (orderNb == 2)
	{
		int numberOfArmies2;
		cout << "Enter number of armies you want to advance:" << endl;
		cin >> numberOfArmies2;
		string sourceTerritory2;
		cout << "Enter name of territory that you want advance from:" << endl;
		cin >> sourceTerritory2;
		string targetTerritory2;
		cout << "Enter name of territory that you want advance to:" << endl;
		cin >> targetTerritory2;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(2, p, NULL, p->getMap()->getTerritory(sourceTerritory2), p->getMap()->getTerritory(targetTerritory2), numberOfArmies2);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 3)
	{
		string sourceTerritory3;
		cout << "Enter name of territory that you want to place a bomb:" << endl;
		cin >> sourceTerritory3;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(3, p, NULL, NULL, p->getMap()->getTerritory(sourceTerritory3), 0);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 4)
	{
		string targetTerritory4;
		cout << "Enter name of territory that you want doubling the number of armies on the territory and transferring the ownership of the territory to the Neutral player.:" << endl;
		cin >> targetTerritory4;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(4, p, NULL, NULL, p->getMap()->getTerritory(targetTerritory4), 0);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 5)
	{
		int numberOfArmies5;
		cout << "Enter number of armies you want to airlift:" << endl;
		cin >> numberOfArmies5;
		string sourceTerritory5;
		cout << "Enter name of territory that you want airlift from:" << endl;
		cin >> sourceTerritory5;
		string targetTerritory5;
		cout << "Enter name of territory that you want airlift to:" << endl;
		cin >> targetTerritory5;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(5, p, NULL, p->getMap()->getTerritory(sourceTerritory5), p->getMap()->getTerritory(targetTerritory5), numberOfArmies5);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 6)
	{
		string p2name;
		cout << "Enter name of player that you want negotiate with:" << endl;
		cin >> p2name;
		
		//TODO
		//need to get the player for the 3rd argument
		//need to get the player for the 3rd argument

		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(6, p, gE->getPlayer(p2name), NULL, NULL, 0); //there is an error 
		//[1. Store order to player's order list]
		//[2. Print out message]
	}
	else
	{

		cout << "There is no such option. Default option - Deploy is selected. " << "\n";

		//[Deploy]
		int numberOfArmies;
		cout << "Enter number of armies you want to deploy:" << endl;
		cin >> numberOfArmies;
		string sourceTerritory;

		cout << "Your territories: " << "\n";
		for (Territory* t : p->getTerritories())
		{
			cout << t->getName() << "\n";
		}
		cout << "\n";

		cout << "Enter name of territory that you want deploy from:" << endl;
		cin >> sourceTerritory;
		string targetTerritory;

		cout << "Enter name of territory that you want deploy to:" << endl;
		cin >> targetTerritory;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(1, p, NULL, p->getMap()->getTerritory(sourceTerritory), p->getMap()->getTerritory(targetTerritory), numberOfArmies);
		//[1. Store order to player's order list]
		//[2. Print out message]           
		//[Delpoy]
	}
	// [issue order]

	//the normal strategy like the previous one
}
HumanPlayerStrategy::~HumanPlayerStrategy()
{
	delete p;
}
//======================================HumanPlayerStrategy======================================

//======================================AggressivePlayerStrategy======================================
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
	p = new Player();
	p->toAttack();
}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p, GameEngine* g) : PlayerStrategy(p, g)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made

	//strategy
	p->toAttack();
	//modified toAttack()
	//removed the argument
	//so that it can be used in the AggressivePlayerStrategy
	//and everytime the player use toAttack()
	//ask which territory the player would like to attack

	//put the order only for attack?
	
	// [Asking for orders]
	int orderNb;
	cout << "Issue Order: " << "\n";
	cout << "Enter 1 for 'advance'\n";
	cout << "Enter 2 for 'bomb'\n";
	cout << "Enter 3 for 'blockade'\n";
	cout << "Enter 4 for 'airlift'\n";
	cout << "ENTER 0 TO EXIT\n";
	cout << ">>";
	cin >> orderNb;
	// [Asking for orders]

	// [issue order]
	if (orderNb == 0)
	{
		std::cout << p->getName() << "has pressed \"0\" to exit." << "\n";
	}
	else if (orderNb == 1)
	{
		int numberOfArmies2;
		cout << "Enter number of armies you want to advance:" << endl;
		cin >> numberOfArmies2;
		string sourceTerritory2;
		cout << "Enter name of territory that you want advance from:" << endl;
		cin >> sourceTerritory2;

		cout << "The territory you are going to advance to: " << p->arbitraryTerritoriesToAttack.front() << endl;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(2, p, NULL, p->getMap()->getTerritory(sourceTerritory2), /*p->getMap()->getTerritory(targetTerritory2)*/p->arbitraryTerritoriesToAttack.front(), numberOfArmies2);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 2)
	{
		cout << "The territory you are going to place a bomb: " << p->arbitraryTerritoriesToAttack.front() << endl;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(3, p, NULL, NULL, /*p->getMap()->getTerritory(sourceTerritory3)*/p->arbitraryTerritoriesToAttack.front(), 0);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 3)
	{
		cout << "The territory you are going to double the number of armies on the territory and transferring the ownership of the territory to the Neutral player: " << p->arbitraryTerritoriesToAttack.front() << endl;

		p->issueOrder(4, p, NULL, NULL, /*p->getMap()->getTerritory(targetTerritory4)*/p->arbitraryTerritoriesToAttack.front(), 0);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else if (orderNb == 4)
	{
		int numberOfArmies5;
		cout << "Enter number of armies you want to airlift:" << endl;
		cin >> numberOfArmies5;
		string sourceTerritory5;
		cout << "Enter name of territory that you want airlift from:" << endl;
		cin >> sourceTerritory5;

		cout << "The territory you are going to airlift to: " << p->arbitraryTerritoriesToAttack.front() << endl;

		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(5, p, NULL, p->getMap()->getTerritory(sourceTerritory5), /*p->getMap()->getTerritory(targetTerritory5)*/p->arbitraryTerritoriesToAttack.front(), numberOfArmies5);
		//[1. Store order to player's order list]
		//[2. Print out message] 
	}
	else
	{

		cout << "There is no such option. Default option for AggressiveStrategy - Advance is selected. " << "\n";

		//[advance]
		int numberOfArmies2;
		cout << "Enter number of armies you want to advance:" << endl;
		cin >> numberOfArmies2;
		string sourceTerritory2;
		cout << "Enter name of territory that you want advance from:" << endl;
		cin >> sourceTerritory2;
		
		cout << "The territory you are going to advance to: " << p->arbitraryTerritoriesToAttack.front() << endl;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(2, p, NULL, p->getMap()->getTerritory(sourceTerritory2), /*p->getMap()->getTerritory(targetTerritory2)*/p->arbitraryTerritoriesToAttack.front(), numberOfArmies2);
		//[1. Store order to player's order list]
		//[2. Print out message] 
		//[advance]

	}
	// [issue order]

	//put the order only for attack?

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
	p->toDefend();
}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p, GameEngine* g) : PlayerStrategy(p, g)
{
	this->p = p;
	//need to add copy constructor for player class, 
	//so that deep copy can be made

	//strategy
	p->toDefend();

	//put the order only for defend?

	// [Asking for orders]
	int orderNb;
	cout << "Issue Order: " << "\n";
	cout << "Enter 1 for 'deploy'\n";
	cout << "Enter 2 for 'negotiate'\n";
	cout << "ENTER 0 TO EXIT\n";
	cout << ">>";
	cin >> orderNb;
	// [Asking for orders]

	// [issue order]
	if (orderNb == 0)
	{
		std::cout << p->getName() << "has pressed \"0\" to exit." << "\n";
	}
	else if (orderNb == 1)
	{
		int numberOfArmies;
		cout << "Enter number of armies you want to deploy:" << endl;
		cin >> numberOfArmies;
		string sourceTerritory;

		cout << "Your territories: " << "\n";
		for (Territory* t : p->getTerritories())
		{
			cout << t->getName() << "\n";
		}
		cout << "\n";

		cout << "Enter name of territory that you want deploy from:" << endl;
		cin >> sourceTerritory;

		cout << "Armies will be deployed to: " << p->_territoriesToDefend_priority.front() << endl;

		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(1, p, NULL, p->getMap()->getTerritory(sourceTerritory), p->_territoriesToDefend_priority.front(), numberOfArmies);
		//[1. Store order to player's order list]
		//[2. Print out message]           
	}
	else if (orderNb == 2)
	{
		string p2name;
		cout << "Enter name of player that you want negotiate with:" << endl;
		cin >> p2name;

		//TODO
		//need to get the player for the 3rd argument
		//need to get the player for the 3rd argument

		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(6, p, gE->getPlayer(p2name), NULL, NULL, 0); //there is an error 
		//[1. Store order to player's order list]
		//[2. Print out message]
	}
	else
	{

		cout << "There is no such option. Default option for BenevolentPlayerStrategy - Deploy is selected. " << "\n";

		//[Deploy]
		int numberOfArmies;
		cout << "Enter number of armies you want to deploy:" << endl;
		cin >> numberOfArmies;
		string sourceTerritory;

		cout << "Your territories: " << "\n";
		for (Territory* t : p->getTerritories())
		{
			cout << t->getName() << "\n";
		}
		cout << "\n";

		cout << "Enter name of territory that you want deploy from:" << endl;
		cin >> sourceTerritory;

		cout << "Armies will be deployed to: " << p->_territoriesToDefend_priority.front() << endl;

		cout << "Enter name of territory that you want deploy to:" << endl;
		//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
		p->issueOrder(1, p, NULL, p->getMap()->getTerritory(sourceTerritory), p->_territoriesToDefend_priority.front(), numberOfArmies);
		//[1. Store order to player's order list]
		//[2. Print out message]           
		//[Delpoy]
	}
	// [issue order]

	//put the order only for defend?


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
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p, GameEngine* g) : PlayerStrategy(p, g)
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
