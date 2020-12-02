#include <vector>
#include <iostream>
#include "Player.h"
#include <string>


int Player::numberOfPlayers = 0; //initializing static variable


//==========CONSTRUCTORS==========//
/*
Player::Player(std::string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderList) {
    _playerNumber = ++numberOfPlayers;
    _name = name;
    _territories = territories;
    _cards = cards;
    _orderList = orderList;
    reinforcementPool = 0;
    this->_territoriesToAttack_priority = new vector<Territory*>();
    this->_territoriesToDefend_priority = new vector<Territory*>();

}*/

Player::Player(std::string name) {
    _playerNumber = ++numberOfPlayers;
    _name = name;
    std::vector<Territory*> territories;
    _territories = territories;
    _cards = new Hand();
    _orderList = new OrdersList();
    reinforcementPool = 0;
    this->_territoriesToAttack_priority = new vector<Territory*>();
    this->_territoriesToDefend_priority = new vector<Territory*>();
}

Player::Player(std::string name,PlayerStrategy* strategy,Map *map,Deck *deck) {
    this->map = map;
    this->deck = deck;
    usedStrategy = strategy;
    _playerNumber = ++numberOfPlayers;
    _name = name;
    std::vector<Territory*> territories;
    _territories = territories;
    _cards = new Hand();
    _orderList = new OrdersList();
    reinforcementPool = 0;
    this->_territoriesToAttack_priority = new vector<Territory*>();
    this->_territoriesToDefend_priority = new vector<Territory*>();
}

Player::Player() {
    _playerNumber = ++numberOfPlayers;
    _name = "Default" + std::to_string(_playerNumber);
    std::vector<Territory*> territories;
    _territories = territories;
    _cards = new Hand();
    _orderList = new OrdersList();
    reinforcementPool = 0;
    this->_territoriesToAttack_priority = new vector<Territory*>();
    this->_territoriesToDefend_priority = new vector<Territory*>();
}

Player::Player(PlayerStrategy* strategy,Map *map,Deck *deck) {
    this->deck = deck;
    this->map = map;
    usedStrategy = strategy;
    _playerNumber = ++numberOfPlayers;
    _name = "Default" + std::to_string(_playerNumber);
    std::vector<Territory*> territories;
    _territories = territories;
    _cards = new Hand();
    _orderList = new OrdersList();
    reinforcementPool = 0;
    this->_territoriesToAttack_priority = new vector<Territory*>();
    this->_territoriesToDefend_priority = new vector<Territory*>();
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
    delete _territoriesToAttack_priority;
    delete _territoriesToDefend_priority;
    if (usedStrategy != nullptr) delete usedStrategy;
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

//-----------findTer by name------------//
Territory* Player::findTerritory(std::string terName) {
    for (int i = 0; i < this->getTerritories().size(); i++) {
        if (this->_territories[i]->getName() == terName) return _territories[i];
    }
    return nullptr;
}


//return territories that player owns
std::vector<Territory*> Player::toDefend() {
    if (usedStrategy != nullptr) {
      usedStrategy->toDefend(this);
    }
    else {
        cout << "No strategy is used " << endl;
    }
    
    return *this->getTodefend();
}

//return arbitrary list of territories to attack (As per A1 instructions)

std::vector<Territory*> Player::toAttack() {
    if (usedStrategy != nullptr) {
        usedStrategy->toAttack(this, this->getMap());
    }
    else {
        cout << "No strategy to be used to attack" << endl;
    }
   
    return *this->getToAttack();
}


//issue the order depending on what the player wants
void Player::issueOrder() {
    usedStrategy->issueOrder(this);
}
//set strategy
void Player::setStrategy(PlayerStrategy* strategy) {
    this->usedStrategy = strategy;
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
void Player::printPlayerTerritories() {
    cout << "You own these territories: ";
    for (int i = 0; i < this->_territories.size(); i++) {
        cout << this->_territories[i]->getName() << " ";
    }
    cout << endl;

}
void Player::printToDefend() {
    cout << "Your own defend list is: ";
    for (int i = 0; i < this->_territoriesToDefend_priority->size(); i++) {
        //string name = this->_territoriesToDefend_priority[i]->getName();
        cout<< this->getTodefend()->at(i)->getName()<<" ";
    }
    cout << endl;

}
void Player::printToAttack() {
    cout << "Your own attack list is: ";
    for (int i = 0; i < this->_territoriesToAttack_priority->size(); i++) {
        //string name = this->_territoriesToDefend_priority[i]->getName();
        cout << this->getToAttack()->at(i)->getName() << " ";
    }
    cout << endl;
}
