#pragma once
#include<iostream>
#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"
#include "Card.h"
//added
#include "PlayerStrategy.h"

class Hand;
class Cards;
class OrdersList;
class PlayerStrategy;
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

    //added for a3
    PlayerStrategy* justStrat;
    Map* map;
    //added for a3

public:
    Player();
    Player(std::string name);
    Player(std::string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderlist);
    ~Player();
    std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
    std::vector<Territory*> toDefend();
    //std::vector<Territory*> toAttack();
    std::vector<Territory*> toAttack(/*//===removed the argument===//  Territory* territoryToAttack*/);
    Territory* findTerritory(std::string terName);
    void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
    void printPlayerOrders();
    //void printPlayerTerritories();
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

    //added for a3
    void setStrategy(std::string strategy);
    void toSkip();
    Map* getMap();
    //added for a3

};
//
