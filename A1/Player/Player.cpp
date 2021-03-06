#include <vector>
#include <iostream>
#include "Player.h"
#include "Orders.h"
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
//-----------findTer by name------------//
Territory* Player::findTerritory(std::string terName) {
	for (int i = 0; i < this->getTerritories().size(); i++) {
		if (this->_territories[i]->getName() == terName) return _territories[i];
	}
	return nullptr;
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

// Added line of code for implementing part2.
void Player::setReinforcements(int rp) {
    reinforcementPool = rp;
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
std::vector<Territory*> Player::toDefend() {
    std::cout << "Player needs to defend: ";
    for (Territory* terr : _territories)
        std::cout << terr->getName() << " ";

    int count = 1;
    int user_input;
    std::cout << "Which territory would you like to defend?" << "\n";

    for (int i = 0; i < _territories.size(); i++)
    {
        std::cout << "Enter \"" << count << "\" for " + _territories.front()->getName() << "\n";
        count++;
    }
    std::cin >> user_input;
    _territoriesToDefend_priority.push_back(_territories[user_input - 1]);

    std::cout << _territories[user_input - 1] << " will be defended. " << "\n";
    return _territoriesToDefend_priority;
}

/* Old toAttack
//return arbitrary list of territories to attack (As per A1 instructions)
std::vector<Territory*> Player::toAttack() {
    std::cout << "\nPlayer needs to attack: ";
    for (const Territory* terr : arbitraryTerritoriesToAttack)
        std::cout << terr->getName() << " ";
    return arbitraryTerritoriesToAttack;
}
*/
std::vector<Territory*> Player::toAttack(Territory* territoryToAttack) {

    arbitraryTerritoriesToAttack.push_back(territoryToAttack);

    std::cout << "\nPlayer needs to attack: ";
    for (const Territory* terr : arbitraryTerritoriesToAttack)
        std::cout << terr->getName() << " ";

    //_territoriesToAttack_priority.pushback();
    return arbitraryTerritoriesToAttack;
}

/*
//issue the order depending on what the player wants
void Player::issueOrder(int orderType) {

    switch (orderType) {
    case 1: {
        Deploy* deploy = new Deploy();
        _orderList->addOrders(deploy);
        std::cout << "Troops deployed!\n";
        break;
    }

    case 2: {
        Advance* advance = new Advance();
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
        Airlift* airlift = new Airlift();
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
*/
//issue the order 
void Player::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){

	if (orderName._Equal("deploy")) {
		Deploy* deploy = new Deploy(p1, numberOfArmies, target);
        _orderList->addOrders(deploy);
        std::cout << "Troops deployed!\n";
    }

	else if (orderName._Equal("advance")) {
		Advance* advance = new Advance(p1, numberOfArmies, source, target);
        _orderList->addOrders(advance);
        std::cout << "Troops advanced!\n";
    }

	else if (orderName._Equal("airlift")) {
		Airlift* airlift = new Airlift(p1, numberOfArmies, source, target);
        _orderList->addOrders(airlift);
        std::cout << "Calling Airlift!\n";
    }

	else if (orderName._Equal("bomb")) {
		Bomb* bomb = new Bomb(p1, target);
        _orderList->addOrders(bomb);
        std::cout << "Bombed!\n";
    }

	else if (orderName._Equal("blockade")) {
		Blockade* blockade = new Blockade(p1, target);
        _orderList->addOrders(blockade);
        std::cout << "Blockade!\n";
    }


	else if (orderName._Equal("negotiate")) {
		Negotiate* negotiate = new Negotiate(p1, p2);
        _orderList->addOrders(negotiate);
        std::cout << "Negotiating...";
    }
	else {
		cout << "ERROR: invalide order!" << endl;
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
