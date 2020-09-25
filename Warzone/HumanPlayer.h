#pragma once
#include "Strategy.h"
#include "Player.h"

class HumanPlayer : public Strategy {
public:
    HumanPlayer() = default;
    void reinforcement(Player* player);
    void attack(Player* player);
    void fortify(Player* player);
};