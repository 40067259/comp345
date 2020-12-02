#include <vector>
#include <iostream>
#include "Player.h"
#include"..\Orders\Orders.h"
#include <string>


int Player::numberOfPlayers = 0; //initializing static variable


//==========CONSTRUCTORS==========//

Player::Player(std::string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderList) {
	_playerNumber = ++numberOfPlayers;
	_name = name;
	_territories = territories;
	_cards = cards;
	_orderList = orderList;
	reinforcementPool = 0;

}

Player::Player(std::string name) {
	_playerNumber = ++numberOfPlayers;
	_name = name;
	std::vector<Territory*> territories;
	_territories = territories;
	_cards = new Hand();
	std::cout << "An empty hand of cards created." << std::endl;
	_orderList = new OrdersList();
	std::cout << "An empty order list created." << std::endl;
	reinforcementPool = 0;
}

Player::Player() {
	_playerNumber = ++numberOfPlayers;
	_name = "Default" + std::to_string(_playerNumber);
	std::vector<Territory*> territories;
	_territories = territories;
	_cards = new Hand();
	std::cout << "An empty hand of cards created." << std::endl;
	_orderList = new OrdersList();
	std::cout << "An empty order list created." << std::endl;
	reinforcementPool = 0;
}

//added copy constructor
Player::Player(const Player* p)
{

}
//added copy constructor

//-----------findTer by name------------//
Territory* Player::findTerritory(std::string terName) {
	for (int i = 0; i < this->getTerritories().size(); i++) {
		if (this->_territories[i]->getName() == terName) return _territories[i];
	}
	return nullptr;
}



//==========DESTRUCTORS==========//
Player::~Player() {
	for (Territory* t : _territories)
	{
		delete t;
		t = nullptr;
	};

	delete _cards;
	_cards = nullptr;
	delete _orderList;
	_orderList = nullptr;
}

//=====GETTERS AND SETTERS====//
std::vector<Territory*> Player::getTerritories() {
	return _territories;
}


Hand* Player::getHand() {
	return _cards;
};

OrdersList* Player::getOrdersList() {
	return _orderList;
};

std::string Player::getName() {
	return _name;
};
int Player::getArmies() {
	return _armies;
};

int Player::getReinforcements() {
	return reinforcementPool;
}




//==========METHODS==========//
//add reinforcements to the player
void Player::addReinforcements(int r) {
	reinforcementPool += r;
}


//return territories that player owns
/* Old toDefend
std::vector<Territory*> Player::toDefend() {
	std::cout << "Player needs to defend: ";
	for (Territory* terr : _territories)
		std::cout << terr->getName() << " ";
	return _territories;
}
*/

// A3 NEW toDefend()
void Player::toDefend() {
	playerStrat->toDefend(this);
}


//A3 NEW toAttack()
void Player::toAttack() {
	playerStrat->toAttack(this);
}


//A3 New issueOrder()
void Player::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) {
	playerStrat->issueOrder(orderName, p1, p2, source, target, numberOfArmies);
}

//add territory
void Player::addTerritory(Territory* terr) {
	this->_territories.push_back(terr);
}

//add new army to players
void Player::giveNewArmy(int num) {
	_armies = _armies + num;
}

void Player::printPlayerOrders() {
	_orderList->printOrders();
}

//added for a3
void Player::setStrategy(std::string strategy)
{

	if (strategy.compare("HumanPlayerStrategy") == 0)
	{
		std::cout << "HumanPlayerStrategy is set. (Printed From Player class)" << "\n";
		//need to modify the constructor used
		//justStrat = new HumanPlayerStrategy(); //just keep it for now, will be deleted later
		playerStrat = new HumanPlayerStrategy();
		//need to modify the constructor used
	}

	else if (strategy.compare("AggressivePlayerStrategy") == 0)
	{
		std::cout << "AggressivePlayerStrategy is set. (Printed From Player class)" << "\n";
		//need to modify the constructor used
		//justStrat = new AggressivePlayerStrategy(); //just keep it for now, will be deleted later
		playerStrat = new AggressivePlayerStrategy();
		//need to modify the constructor used
	}

	else if (strategy.compare("BenevolentPlayerStrategy") == 0)
	{
		std::cout << "BenevolentPlayerStrategy is set. (Printed From Player class)" << "\n";
		//need to modify the constructor used
		//justStrat = new BenevolentPlayerStrategy(); //just keep it for now, will be deleted later
		playerStrat = new BenevolentPlayerStrategy();
		//need to modify the constructor used
	}

	else if (strategy.compare("NeutralPlayerStrategy") == 0)
	{
		std::cout << "NeutralPlayerStrategy is set. (Printed From Player class)" << "\n";
		//need to modify the constructor used
		//justStrat = new NeutralPlayerStrategy(); //just keep it for now, will be deleted later
		playerStrat = new NeutralPlayerStrategy();
		//need to modify the constructor used
	}

	else
	{
		std::cout << "Command is not recognized, HumanPlayerStrategy is set as default. (Printed From Player class)" << "\n";
		//need to modify the constructor used
		//justStrat = new HumanPlayerStrategy(); //just keep it for now, will be deleted later
		playerStrat = new HumanPlayerStrategy();
		//need to modify the constructor used
	}
}

void Player::toSkip()
{
	std::cout << _name << " is using NeutralPlayerStrategy. That means the player is not issuing orders. (Printed from toSkip() method)" << "\n";
}

Map* Player::getMap()
{
	return map;
}

//added for a3
void Player::appendOrder(Orders *newOrder) {
	_orderList->addOrders(newOrder);
}