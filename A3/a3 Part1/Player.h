#pragma once
#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"
#include "PlayerStrategy.h"

class Map;
class OrdersList;//why I need this line to avoid errors????
class PlayerStrategy;
using namespace std;

class Player {
private:
    std::vector<Territory*> _territories;
    Hand* _cards;
    OrdersList* _orderList;
    string _name;
    int _playerNumber;
    int _armies = 0;
    int reinforcementPool;
    PlayerStrategy* usedStrategy;
    static int numberOfPlayers;
    //added
    std::vector<Territory*> *_territoriesToDefend_priority;
    std::vector<Territory*> *_territoriesToAttack_priority;
    //added
    Map* map;
    Deck* deck;

   
public:
    Player();
    Player(PlayerStrategy *strategy,Map *map, Deck* deck);
    Player(string name);
    Player(string name, PlayerStrategy *strategy, Map *map,Deck *deck);
  //  Player(string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderlist);
    ~Player();
    std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    Territory* findTerritory(std::string terName);
    vector<Territory*>* getTodefend() {
        return _territoriesToDefend_priority;
    } 
    vector<Territory*>* getToAttack() {
        return _territoriesToAttack_priority;
    }
    Map* getMap() { return map;}
    Deck* getDeck() { return deck;}
    void issueOrder();
    void printPlayerOrders();
    void printPlayerTerritories();
    void giveNewArmy(int num);
    void addTerritory(Territory* terr);
    void addReinforcements(int r);
    //add
    void printToDefend();
    void printToAttack();
    void setStrategy(PlayerStrategy* usedStrategy);
    vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();
    string getName();
    int getArmies();
    int getReinforcements();

};





