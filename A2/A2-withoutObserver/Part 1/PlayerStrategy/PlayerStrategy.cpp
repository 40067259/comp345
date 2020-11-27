#include <iostream>
#include <fstream>
#include <string>
#include "PlayerStrategy.h"

//======================================PlayerStrategy======================================
PlayerStrategy::PlayerStrategy()
{
}
PlayerStrategy::PlayerStrategy(Player* p)
{
}
PlayerStrategy::~PlayerStrategy()
{
}
//======================================PlayerStrategy======================================


//======================================HumanPlayerStrategy======================================
HumanPlayerStrategy::HumanPlayerStrategy():PlayerStrategy()
{

}
HumanPlayerStrategy::HumanPlayerStrategy(Player* p):PlayerStrategy(p)
{

}
HumanPlayerStrategy::~HumanPlayerStrategy()
{

}
//======================================HumanPlayerStrategy======================================

//======================================AggressivePlayerStrategy======================================
AggressivePlayerStrategy::AggressivePlayerStrategy()
{

}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p)
{

}
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{

}
//======================================AggressivePlayerStrategy======================================

//======================================BenevolentPlayerStrategy======================================
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p)
{

}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{

}
//======================================BenevolentPlayerStrategy======================================

//======================================NeutralPlayerStrategy======================================
NeutralPlayerStrategy::NeutralPlayerStrategy()
{

}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p)
{

}
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{

}
//======================================NeutralPlayerStrategy======================================
