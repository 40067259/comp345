#include "Player.h"
#include <vector>

Player::Player(std::vector<Territory> territories, Card cards) {
    territories = _territories;
    cards = _cards;
}



std::vector<Territory> Player::toDefend() {
    return _territories;
}

std::vector<Territory> Player::toAttack() {
    
}

void Player::issueOrder(int orderType) {
    

    switch(orderType) {

        case 1 :{
            Deploy* deploy = new Deploy();
            _playerOrderList.addOrders(deploy);
            break;
        }
       

        case 2:{
            Advance* advance = new Advance();
            _playerOrderList.addOrders(advance);
            break;
        }
        

        case 3: {
            Bomb* bomb = new Bomb();
            _playerOrderList.addOrders(bomb);
            break;

        }
        
        case 4:{
            Blockade* blockade = new Blockade();
            _playerOrderList.addOrders(blockade);
            break;
        }
       

        case 5:{
            Airlift* airlift = new Airlift();
            _playerOrderList.addOrders(airlift);
            break;
        }
        

        case 6:{
            Negotiate* negotiate = new Negotiate();
            _playerOrderList.addOrders(negotiate);
            break;

        }
        
    }
