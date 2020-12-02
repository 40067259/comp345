#pragma once
#include "Player.h"

#include "Territory.h"
class Territory;
class PlayerStrategy{
public:
    virtual void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) =0;
    virtual void toAttack(Player *p) = 0;
    virtual void toDefend(Player *p) = 0;
};


class HumanPlayerStrategy : public PlayerStrategy
{
public:
    void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
    void toAttack(Player *p);
    void toDefend(Player *p);
};




class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
    void toAttack(Player *p);
    void toDefend(Player *p);
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
    void toAttack(Player *p);
    void toDefend(Player *p);
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
    void toAttack(Player *p);
    void toDefend(Player *p);
};


