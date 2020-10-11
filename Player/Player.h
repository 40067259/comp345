#pragma once

#include <vector>
#include "Territory.h"
#include "OrdersList.h"
#include "Orders.h"
#include "Map.h"
//#include "Cards.h"


class Player {

private:
    std::vector<Territory> _territories;
    //Card _cards;
    OrdersList _playerOrderList;



public:

   Player(std::vector<Territory> &territories /*,Card cards*/);
   std::vector<Territory> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
   std::vector<Territory> toDefend();
   std::vector<Territory> toAttack();
   void issueOrder(int orderType);
   void printPlayerOrders();


};
