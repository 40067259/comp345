#pragma once
#include "Strategy.h"

class AggressivePlayer : public Strategy {
public:
	AggressivePlayer() = default;
    void reinforcement(Player* player);
    void attack(Player* player);
    void fortify(Player* player);
};
