

#include "Player.h"
#include <vector>
#include <iostream>

Player::Player(std::vector<Territory> &territories, Hand cards) {
     _territories = territories;
     _cards = cards;
}


//return territories that player owns
std::vector<Territory> Player::toDefend() {
    return _territories;

}

//return arbitrary list of territories to attack (As per A1 instructions)
std::vector<Territory> Player::toAttack() {
    return arbitraryTerritoriesToAttack;
}

//issue the order depending on what the player wants
void Player::issueOrder(int orderType) {
    
    switch(orderType) {
        case 1 :{
            Deploy* deploy = new Deploy();
            _playerOrderList.addOrders(deploy);
            std::cout<< "Troops deployed!\n";
            break;
        }

        case 2:{
            Advance* advance = new Advance();
            _playerOrderList.addOrders(advance);
            std::cout<< "Troops advanced!\n";
            break;
        }
            
        case 3: {
            Bomb* bomb = new Bomb();
            _playerOrderList.addOrders(bomb);
            std::cout<< "Bombed!\n";
            break;
        }

        
        case 4:{
            Blockade* blockade = new Blockade();
            _playerOrderList.addOrders(blockade);
            std::cout<< "Blockade!\n";
            break;
        }

        case 5:{
            Airlift* airlift = new Airlift();
            _playerOrderList.addOrders(airlift);
            std::cout<< "Calling Airlift!\n";
            break;
        }

            
        case 6:{
            Negotiate* negotiate = new Negotiate();
            _playerOrderList.addOrders(negotiate);
            std::cout<< "Negotiating...";
            break;
        }

    }
}


void Player::printPlayerOrders(){
    _playerOrderList.printOrders();
}

