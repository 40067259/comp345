#include <vector>
#include <iostream>
#include "Player.h"
#include"Orders.h"
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



//A3 NEW toDefend()
std::vector<Territory*> Player::toDefend() {
    return playerStrat->toDefend(this);
}

/*
//A3 NEW toAttack()
std::vector<Territory*> Player::toAttack() {
    return playerStrat->toAttack(this);
}


//A3 New issueOrder()
void Player::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) {
    return playerStrat->issueOrder(orderName, p1, p2, source, target, numberOfArmies);
}


//A3 setStrategy()
void Player::setStrategy(PlayerStrategy *strategy)
{
    playerStrat = strategy;
}
*/
void Player::toDefend(Territory* territoryToDefend) {
	return this->justStrat->toDefend(territoryToDefend);
}

void Player::toAttack(Territory* territoryToAttack) {
	return this->justStrat->toAttack(territoryToAttack);
}


//issue the order depending on what the player wants
void Player::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) {
	return this->justStrat->issueOrder(orderName, p1, p2, source, target, numberOfArmies);
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





void Player::toSkip()
{
    std::cout << _name << " is using NeutralPlayerStrategy. That means the player is not issuing orders. (Printed from toSkip() method)" << "\n";
}

Map* Player::getMap()
{
    return map;
}


//added for a3
void Player::appendOrder(Orders *newOrder){
    _orderList->addOrders(newOrder);
}
