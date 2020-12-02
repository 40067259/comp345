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
        std::cout << "Troops deployed!\n";
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


void HumanPlayerStrategy::toDefend(Player *p) {
    
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
    //return p->_territoriesToDefend_priority;
    
}




void HumanPlayerStrategy::toAttack(Player *p){

    std::cout << "Which territory you would like to attack?" << "\n";
    std::cout << "You can attack: " << "\n";

    //only print out the land the user does not own
    std::vector<string> temp_territory_vector;
    for (int i = 0; i < p->getMap()->size(); i++)
    {
        for (int j = 0; p->getTerritories().size(); j++)
        {
            if (((p->getMap()->getTerritory(i)->getName()).compare(p->getTerritories()[j]->getName())) == 0)
            {
                continue;
            }
            else
            {
                //add the territory name to the tamp_territory
                temp_territory_vector.push_back(p->getMap()->getTerritory(i)->getName());
                //add the territory name to the tamp_territory
            }
        }
    }
    for (int i = 0; i < temp_territory_vector.size(); i++)
    {
        std::cout << temp_territory_vector[i] << "\n";
    }
    //only print out the land the user does not own
    string user_input;
    cin >> user_input;

    p->arbitraryTerritoriesToAttack.push_back(p->getMap()->getTerritory(user_input));

    //return p->arbitraryTerritoriesToAttack;
  
}





//====AGGRESSIVE PLAYER STRATEGY=====//

//MUST IMPLEMENT
void AggressivePlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){
    std::cout << "Aggressive player never issues any order" << std::endl;    
}

//MUST IMPLEMENT
void AggressivePlayerStrategy::toAttack(Player *p){
    
}

//MUST IMPLEMENT
void AggressivePlayerStrategy:: toDefend(Player *p){
    
}




//====BENEVOLANT PLAYER STRATEGY=====//


void BenevolentPlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies){
    std::cout << "Benevolent player never issues any order" << std::endl;
}



void BenevolentPlayerStrategy::toDefend(Player *p) {
    
   //here, we don't use orderName as all this benevolant player can do is deploy armies to the weakest territory
	//1) DETECT WEAKEST TERRITORY
	Territory *weakestTerritory = p->getTerritories().at(0);

	for (Territory *t : p->getTerritories()) {
		if (t->getArmies() < weakestTerritory->getArmies()) {
			weakestTerritory = t;
		}
	}

	//2) DETECT THE STRONGEST TERRITORY
	Territory *strongestTerritory = p->getTerritories().at(0);

	for (Territory *t : p->getTerritories()) {
		if (t->getArmies() > weakestTerritory->getArmies()) {
			strongestTerritory = t;
		}
	}

	//3) ADD HALF OF STRONGEST ARMIES TERRITORIES TO WEAKEST
	int armiesToAddToWeakest = strongestTerritory->getArmies() / 2;
	strongestTerritory->removeArmies(armiesToAddToWeakest);
	weakestTerritory->addArmies(armiesToAddToWeakest);

    vector<Territory*> toDefend = p->getTerritories();
    
    std::cout << "Player needs to defend: " << "\n";
    for (Territory* terr : p->getTerritories())
        std::cout << terr->getName() << "\n";

   // return p->_territoriesToDefend_priority;
    
}


void BenevolentPlayerStrategy::toAttack(Player *p){
    std::cout << "neutral player never attack" << std::endl;
	//return p->arbitraryTerritoriesToAttack;
    
}


//====NEUTRAL PLAYER STRATEGY=====//

NeutralPlayerStrategy::NeutralPlayerStrategy(){
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

void NeutralPlayerStrategy::issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies) {
	std::cout << "neutral player never issues any order" << std::endl;
}
void NeutralPlayerStrategy::toDefend(Player* p) {
	std::cout << "neutral player never defend" << std::endl;
}
void NeutralPlayerStrategy::toAttack(Player* p) {
	std::cout << "neutral player never attack" << std::endl;
}

