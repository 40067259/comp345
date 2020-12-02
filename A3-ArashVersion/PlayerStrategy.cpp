#include <iostream>
#include <fstream>
#include <string>
#include "PlayerStrategy.h"

//====HUMAN PLAYER STRATEGY=====//
void HumanPlayerStrategy::issueOrder(int orderName, Player *p1, Player *p2, Territory *source, Territory *target, int numberOfArmies)
{

    if (orderName == 1) {
        Deploy* deploy = new Deploy(p1, numberOfArmies, target);
        p1->appendOrder(deploy);
        std::cout << "Troops deployed!\n"; //Problem is here: do we really need this statement?
    }

    else if (orderName == 2) {
        Advance* advance = new Advance(p1, numberOfArmies, source, target);
        p1->appendOrder(advance);
        std::cout << "Troops advanced!\n";
    }

    else if (orderName == 5) {
        Airlift* airlift = new Airlift(p1, numberOfArmies, source, target);
        p1->appendOrder(airlift);
        std::cout << "Calling Airlift!\n";
    }

    else if (orderName == 3) {
        Bomb* bomb = new Bomb(p1, target);
        p1->appendOrder(bomb);
        std::cout << "Bombed!\n";
    }

    else if (orderName == 4) {
        Blockade* blockade = new Blockade(p1, target);
        p1->appendOrder(blockade);
        std::cout << "Blockade!\n";
    }


    else if (orderName == 6) {
        Negotiate* negotiate = new Negotiate(p1, p2);
        p1->appendOrder(negotiate);
        std::cout << "Negotiating...";
    }
    else {
        cout << "ERROR: invalide order!" << endl;
    }
}


vector<Territory*> HumanPlayerStrategy::toDefend(Player *p) {
    
    vector<Territory*> toDefend = p->getTerritories();
    
    std::cout << "Player needs to defend: " << "\n";
    for (Territory* terr : p->getTerritories())
        std::cout << terr->getName() << "\n";

    //int count = 0;
    int user_input;
    std::cout << "Which territory would you like to defend?" << "\n";

    for (int i = 0; i < p->getTerritories().size(); i++)
    {
        std::cout << "Enter \"" << i << "\" for " + p->getTerritories()[i]->getName() << "\n";
        //count++;
    }
    std::cin >> user_input;
    
    p->_territoriesToDefend_priority.push_back(p->getTerritories()[user_input]);

    std::cout << p->getTerritories()[user_input]->getName() << " will be defended. " << "\n";
    return p->_territoriesToDefend_priority;
    
}

//MUST IMPLELEMNT
vector<Territory*> HumanPlayerStrategy::toAttack(Player *p){}





//====AGGRESSIVE PLAYER STRATEGY=====//

//MUST IMPLEMENT
void AggressivePlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){
    
}

//MUST IMPLEMENT
vector<Territory*> AggressivePlayerStrategy::toAttack(Player *p){
    
}

//MUST IMPLEMENT
vector<Territory*> AggressivePlayerStrategy:: toDefend(Player *p){
    
}




//====BENEVOLANT PLAYER STRATEGY=====//

//MUST IMPLEMENT
void BenevolentPlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){
    
}

//MUST IMPLEMENT
vector<Territory*> BenevolentPlayerStrategy::toDefend(Player *p) {
    
}

//MUST IMPLEMENT
vector<Territory*> BenevolentPlayerStrategy::toAttack(Player *p){
    
}


//====NEUTRAL PLAYER STRATEGY=====//


//MUST IMPLEMENT
void NeutralPlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){
    
}

//MUST IMPLEMENT
vector<Territory*> NeutralPlayerStrategy::toDefend(Player *p) {
    
}

//MUST IMPLEMENT
vector<Territory*> NeutralPlayerStrategy::toAttack(Player *p){
    
}
