

#include "Player.h"
#include <vector>
#include <iostream>

int Player::numberOfPlayers = 0; //initializing static variable


//==========CONSTRUCTORS==========//

Player::Player(string name, std::vector<Territory*> territories, Hand *cards, OrdersList *orderList) {
    _playerNumber = numberOfPlayers++;
    _name = name;
     _territories = territories;
     _cards = cards;
    _orderList = orderList;
}

Player::Player() {
    _playerNumber = numberOfPlayers++;
    _name = "Default ";
    vector<Territory*> territories;
    _territories = territories;
     _cards = new Hand();
    _orderList = new OrdersList();
}

//==========DESTRUCTORS==========//
Player::~Player(){
    for (Territory *t : _territories)
    {
        delete t;
        t = nullptr;
    };
    
    delete _cards;
    _cards = nullptr;
    delete _orderList;
    _orderList = nullptr;
}





//==========METHODS==========//

//return territories that player owns
std::vector<Territory*> Player::toDefend() {
    std::cout<< "Player needs to defend: ";
    for (Territory *terr : _territories)
         std::cout << terr->getName() << " ";

    return _territories;
}

//return arbitrary list of territories to attack (As per A1 instructions)
std::vector<Territory*> Player::toAttack() {
    std::cout<< "\nPlayer needs to attack: ";
    for (const Territory *terr : arbitraryTerritoriesToAttack)
         std::cout << terr->getName() << " ";
    return arbitraryTerritoriesToAttack;
}



//issue the order depending on what the player wants
void Player::issueOrder(int orderType) {
    
    switch(orderType) {
        case 1 :{
            Deploy* deploy = new Deploy();
            _orderList->addOrders(deploy);
            std::cout<< "Troops deployed!\n";
            break;
        }

        case 2:{
            Advance* advance = new Advance();
            _orderList->addOrders(advance);
            std::cout<< "Troops advanced!\n";
            break;
        }
            
        case 3: {
            Bomb* bomb = new Bomb();
            _orderList->addOrders(bomb);
            std::cout<< "Bombed!\n";
            break;
        }

        
        case 4:{
            Blockade* blockade = new Blockade();
            _orderList->addOrders(blockade);
            std::cout<< "Blockade!\n";
            break;
        }

        case 5:{
            Airlift* airlift = new Airlift();
            _orderList->addOrders(airlift);
            std::cout<< "Calling Airlift!\n";
            break;
        }

            
        case 6:{
            Negotiate* negotiate = new Negotiate();
            _orderList->addOrders(negotiate);
            std::cout<< "Negotiating...";
            break;
        }

    }
}


void Player::printPlayerOrders(){
    _orderList.printOrders();
}