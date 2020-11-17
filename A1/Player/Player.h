#pragma once

#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"
#include "Card.h"

class Hand;
class Cards;

class Player {
private:
    std::vector<Territory*> _territories;
    Hand* _cards;
    OrdersList* _orderList;
    std::string _name;
    int _playerNumber;
    int _armies = 0;
    int reinforcementPool;
    static int numberOfPlayers;

public:
    Player();
    Player(std::string name);
    Player(std::string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderlist);
    ~Player();
    std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
    std::vector<Territory*> toDefend();
    //std::vector<Territory*> toAttack();
    std::vector<Territory*> toAttack(Territory* territoryToAttack);
    void issueOrder(int orderType);
    void printPlayerOrders();
    void printPlayerTerritories();
    void giveNewArmy(int num);
    void addTerritory(Territory* terr);
    void addReinforcements(int r);

    std::vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();
    std::string getName();
    int getArmies();
    int getReinforcements();

    //added
    std::vector<Territory*> _territoriesToDefend_priority;
    std::vector<Territory*> _territoriesToAttack_priority;
    //added

};




