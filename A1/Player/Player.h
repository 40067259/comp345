#pragma once
#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"

class Hand;
class Card;


class Player {

private:
    std::vector<Territory*> _territories;
    Hand *_cards;
    OrdersList *_orderList;
    string _name;
    int _playerNumber;
    static int numberOfPlayers;



public:
   Player();
    Player(string name);
   Player(string name, std::vector<Territory*> territories ,Hand *cards, OrdersList *orderlist);
   ~Player();
   std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
   std::vector<Territory*> toDefend();
   std::vector<Territory*> toAttack();
   void issueOrder(int orderType);
   void printPlayerOrders();
  void printPlayerTerritories();


};



