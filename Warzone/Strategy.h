#pragma once

class Player;

class Strategy {
public:
    virtual void reinforcement(Player* player);
    virtual void attack(Player* player);
    virtual void fortify(Player* player);
    virtual ~Strategy();
};