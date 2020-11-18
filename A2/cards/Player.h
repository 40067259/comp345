#pragma once
#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"

class OrdersList;//why I need this line to avoid errors????
using namespace std;

class Player {
private:
    std::vector<Territory*> _territories;
    Hand* _cards;
    OrdersList *_orderList;
    string _name;
    int _playerNumber;
    int _armies = 0;
    int reinforcementPool;
    static int numberOfPlayers;

public:
    Player();
    Player(string name);
    Player(string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderlist);
    ~Player();
    std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    Territory* findTerritory(std::string terName);
    void issueOrder(int orderType);
    void printPlayerOrders();
    void printPlayerTerritories();
    void giveNewArmy(int num);
    void addTerritory(Territory* terr);
    void addReinforcements(int r);


    vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();
    string getName();
    int getArmies();
    int getReinforcements();





};





