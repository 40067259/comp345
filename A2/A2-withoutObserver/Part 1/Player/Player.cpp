#include <vector>
#include <iostream>
#include "Player.h"
#include"C:\Users\amadeus\source\repos\part1\part1\Orders\Orders.h"
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
std::vector<Territory*> Player::toDefend() {
    std::cout << "Player needs to defend: ";
    for (Territory* terr : _territories)
        std::cout << terr->getName() << "\n";

    //int count = 1; //should be deleted
    int user_input;
    std::cout << "Which territory would you like to defend?" << "\n";

    for (int i = 0; i < _territories.size(); i++)
    {
        std::cout << "Enter \"" << i << "\" for " + _territories[i]->getName() << "\n";
    }
    std::cin >> user_input;
    _territoriesToDefend_priority.push_back(_territories[user_input]);

    std::cout << _territories[user_input]->getName() << " will be defended. " << "\n";
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
    {
        std::cout << terr->getName() << "\n";
    }
	std::cout << "===From Player: toAttack()===" << "\n";

    //_territoriesToAttack_priority.pushback();
    return arbitraryTerritoriesToAttack;
}


//issue the order depending on what the player wants
void Player::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){

	if (orderName == 1) {
		Deploy* deploy = new Deploy(p1, numberOfArmies, target);
        _orderList->addOrders(deploy);
        std::cout << "Troops deployed!\n";
    }

	else if (orderName==2) {
		Advance* advance = new Advance(p1, numberOfArmies, source, target);
        _orderList->addOrders(advance);
        std::cout << "Troops advanced!\n";
    }

	else if (orderName==5) {
		Airlift* airlift = new Airlift(p1, numberOfArmies, source, target);
        _orderList->addOrders(airlift);
        std::cout << "Calling Airlift!\n";
    }

	else if (orderName==3) {
		Bomb* bomb = new Bomb(p1, target);
        _orderList->addOrders(bomb);
        std::cout << "Bombed!\n";
    }

	else if (orderName==4) {
		Blockade* blockade = new Blockade(p1, target);
        _orderList->addOrders(blockade);
        std::cout << "Blockade!\n";
    }


	else if (orderName==6) {
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

//added for a3
void Player::setStrategy(std::string strategy)
{

    if (strategy.compare("HumanPlayerStrategy") == 0)
    {
        std::cout << "HumanPlayerStrategy is set." << "\n";
        justStrat = new HumanPlayerStrategy();
    }

    else if (strategy.compare("AggressivePlayerStrategy") == 0)
    {
        std::cout << "AggressivePlayerStrategy is set." << "\n";
        justStrat = new AggressivePlayerStrategy();
    }

    else if (strategy.compare("BenevolentPlayerStrategy") == 0)
    {
        std::cout << "BenevolentPlayerStrategy is set." << "\n";
        justStrat = new BenevolentPlayerStrategy();
    }

    else if (strategy.compare("NeutralPlayerStrategy") == 0)
    {
        std::cout << "NeutralPlayerStrategy is set." << "\n";
        justStrat = new NeutralPlayerStrategy();
    }

    else
    {
        std::cout << "Command is not recognized, HumanPlayerStrategy is set as default." << "\n";
        justStrat = new HumanPlayerStrategy();
    } 
}
//added for a3
