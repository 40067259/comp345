#pragma once
#include <vector>
#include "Territory.h"
#include "Cards.h"
#include "OrdersList.h"
#include "Orders.h"

class Player {

private:
    std::vector<Territory> _territories;
    Card _cards;
    OrdersList _playerOrderList;

public:
   Player(std::vector<Territory> territories, Card cards);
   std::vector<Territory> toDefend();
   std::vector<Territory> toAttack();
   void issueOrder(int orderType);

};
