#pragma once

#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
#include "Hand.h"


class Player {

private:
    std::vector<Territory> _territories;
    Hand _cards;
    OrdersList _playerOrderList;



public:

   Player();
   Player(std::vector<Territory> &territories ,Hand cards);
   std::vector<Territory> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
   std::vector<Territory> toDefend();
   std::vector<Territory> toAttack();
   void issueOrder(int orderType);
   void printPlayerOrders();
  void printPlayerTerritories();


};
