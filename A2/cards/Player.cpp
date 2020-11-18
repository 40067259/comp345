#include <vector>
#include <iostream>
#include "Player.h"
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
    _orderList = new OrdersList();
    reinforcementPool = 0;
}

Player::Player() {
    _playerNumber = ++numberOfPlayers;
    _name = "Default" + std::to_string(_playerNumber);
    std::vector<Territory*> territories;
    _territories = territories;
    _cards = new Hand();
    _orderList = new OrdersList();
    reinforcementPool = 0;
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

//-----------findTer by name------------//
Territory* Player::findTerritory(std::string terName) {
    for (int i = 0; i < this->getTerritories().size(); i++) {
        if (this->_territories[i]->getName() == terName) return _territories[i];
    }
    return nullptr;
}


//return territories that player owns
std::vector<Territory*> Player::toDefend() {
    std::cout << "Player needs to defend: ";
    for (Territory* terr : _territories)
        std::cout << terr->getName() << " ";

    return _territories;
}

//return arbitrary list of territories to attack (As per A1 instructions)
std::vector<Territory*> Player::toAttack() {
    std::cout << "\nPlayer needs to attack: ";
    for (const Territory* terr : arbitraryTerritoriesToAttack)
        std::cout << terr->getName() << " ";
    return arbitraryTerritoriesToAttack;
}


//issue the order depending on what the player wants
void Player::issueOrder(int orderType) {

    switch (orderType) {
    case 1: {
        cout << "Please input your number of armies and territory name" << endl;
        int number = 0; std::string name = "User";
        cin >> number >> name;
        Deploy* deploy = new Deploy(this,number,name);
        _orderList->addOrders(deploy);
        std::cout << "Troops deployed!\n";
        break;
    }

    case 2: {
        cout << "Please choose your source territory, input your number of armies from source territory, and input target territory" << endl;
        int number = 0; std::string sourceName = "sourceTer", targetName = "targetTer";
        cin >> number>>sourceName>>targetName;
        Advance* advance = new Advance(this,number,sourceName,targetName);
        _orderList->addOrders(advance);
        std::cout << "Troops advanced!\n";
        break;
    }

    case 3: {
        Bomb* bomb = new Bomb();
        _orderList->addOrders(bomb);
        std::cout << "Bombed!\n";
        break;
    }


    case 4: {
        Blockade* blockade = new Blockade();
        _orderList->addOrders(blockade);
        std::cout << "Blockade!\n";
        break;
    }

    case 5: {
        cout << "Please choose your source territory, input your number of armies from source territory, and input target territory" << endl;
        int number = 0; std::string sourceName = "sourceTer", targetName = "targetTer";
        cin >> number >> sourceName >> targetName;
        Airlift* airlift = new Airlift(this, number, sourceName, targetName);
        _orderList->addOrders(airlift);
        std::cout << "Calling Airlift!\n";
        break;
    }


    case 6: {
        Negotiate* negotiate = new Negotiate();
        _orderList->addOrders(negotiate);
        std::cout << "Negotiating...";
        break;
    }

    }
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
