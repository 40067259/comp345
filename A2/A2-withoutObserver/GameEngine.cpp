#include "GameEngine.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include "Map.h"
#include "Territory.h"
using std::cout;
using std::endl;
using std::cin;


GameEngine::GameEngine() {

}


//method that starts the game
void GameEngine::GameStart() {
    cout << "=======================================" << endl;
    cout << "          LET'S PLAY WARZONE           " << endl;
    cout << "=======================================" << endl;

    //Step 1: Select the map
    mapSelection();

    //Step 2: Select the amount of players
    playerSelection();
}



//TODO: CHECK HOW TO REJECT A MAP BASED ON THE FACT IF ITS A CONNECTED GRAPH OR NOT
void GameEngine::mapSelection() {
    int selectedMap;
    cout << "Let's select a map: (1)USA (2)Canada (3)Europe" << endl;
    cout << "Enter an integer 1, 2, or 3" << endl;
    cin >> selectedMap;
    while (selectedMap != 1 || selectedMap != 2 || selectedMap != 3) {
        cout << "You have made an invalid selection. Please choose from one of 3 options." << endl;
        cin >> selectedMap;
    }

    MapLoader* mapLoader = new MapLoader();
    switch (selectedMap) {
    case 1:
        mapLoader->loadMap("us.map");
        break;
    case 2:
        mapLoader->loadMap("canada.map");
        break;
    case 3:
        mapLoader->loadMap("europe.map");
        break;
    }
}

void GameEngine::playerSelection() {
    int numberOfPlayersSelected;
    cout << "How many players will play? Choose between 2 to 5.";
    cin >> numberOfPlayersSelected;
    if (numberOfPlayersSelected < 2 || numberOfPlayersSelected >5) {
        cout << "Invalid. Select between 2 to 5";
        cin >> numberOfPlayersSelected;
    }

    numberOfPlayers = numberOfPlayersSelected;

    for (int i = 0; i < numberOfPlayers; i++) {
        string name;
        cout << "Enter the name of player " << i + 1 << endl;
        cin >> name;
        Player* player = new Player(name);
        playersVector.push_back(player);
    }

}



//==========PART 3: MAIN GAME LOOP==========//
void GameEngine::mainGameLoop() {
    
    reinforcementPhase();
    issuingOrderPhase();
    ordersExectionPhase();
}

/*old reunforcementPhase()
void GameEngine::reinforcementPhase() {
    for (Player* p : playersVector) {
        int armiesGiven = 3;

        int territoriesowned = p->getTerritories().size();
    }
}
*/
//PART 3 - ReinforcementPhase
void GameEngine::reinforcementPhase() {
    //For each player playing the game, give them armies
    for (Player* p : playersVector) {
        int minimumArmy = 3; //minimum amount of armies
        int territorialArmies = 0; //armies depending on the amount of territories owned
        int bonusArmy = 0; //bonus army
        int totalArmy = 0; // total army, with everything added together



        //-----Condition 1:If player owns more than 3 territories, give them army-----//
        int territoriesowned = p->getTerritories().size(); //territories owned
        if (territoriesowned > 3) {
            territorialArmies = territoriesowned / 3;
        }

        //-----Condition 2: If player owns all territories in a continent, give bonus armies-----//
        unordered_map<string, Continent> tableOfContinents = map->getContinents();
        for (auto& continent : tableOfContinents) {
            if (continent.second.owner(p) == true) {
                bonusArmy = continent.second.getNativeArmy();
            };
        }

        totalArmy = minimumArmy + territorialArmies + bonusArmy + totalArmy;

        p->addReinforcements(totalArmy);

    }
}

void GameEngine::issuingOrderPhase()
{
    int orderNb;

    for (Player* p : playersVector)
    {
        // [Asking for orders]
        cout << "Issue Order: " << "\n";
        cout << "Enter 1 for 'deploy'\n";
        cout << "Enter 2 for 'advance'\n";
        cout << "Enter 3 for 'bomb'\n";
        cout << "Enter 4 for 'blockade'\n"; 
        cout << "Enter 5 for 'airlift'\n";
        cout << "Enter 6 for 'negotiate'\n";
        cout << "ENTER 0 TO EXIT\n";
        cout << ">>";
        cin >> orderNb;
        // [Asking for orders]

        // [issue order]
        if (orderNb == 0) 
        {
            break;
        }
        else if(orderNb == 1)
        {
            p->issueOrder(1);
            //[1. Store order to player's order list]
            //[2. Print out message]           
        }
        else if (orderNb == 2)
        {
            p->issueOrder(2);
            //[1. Store order to player's order list]
            //[2. Print out message] 
        }
        else if (orderNb == 3)
        {
            p->issueOrder(3);
            //[1. Store order to player's order list]
            //[2. Print out message] 
        }
        else if (orderNb == 4)
        {
            p->issueOrder(4);
            //[1. Store order to player's order list]
            //[2. Print out message] 
        }
        else if (orderNb == 5)
        {
            p->issueOrder(5); 
            //[1. Store order to player's order list]
            //[2. Print out message] 
        }
        else if (orderNb == 6)
        {
            p->issueOrder(6);
            //[1. Store order to player's order list]
            //[2. Print out message]
        }
        else
        {
            cout << "There is no such option. Please wait for the next round";
            break;
        }
        // [issue order]
        // This method will ask the player which order they would like to issue
        // The order the player issue will then be placed inside the "_orderList" list of that player


        // [toAttack]
        std::cout << "Please select Territory to attack: ";
        int count = 1;
        for (int i = 0; i < map->size(); i++)
        {
            std::cout << "Press \"" << count << "\" to select " << map->getTerritory(i) << "\n";
            count++;
        }
        int user_input;
        std::cin >> user_input;

        if (std::count(p->getTerritories().begin(), p->getTerritories().end(), map->getTerritory(user_input - 1))) //check if player have the territory already
        {
            std::cout << "You have owned the territory already";
            std::cout << "Please wait for the next round";
        }
        else
        {
            p->toAttack(map->getTerritory(user_input - 1)); //add the territory to attack to the arbitraryTerritoriesToAttack list
        }
        // [toAttack]
        // This method will ask the player to choose a territory to attack
        // After checking that the territory can be attacked, the territory will be placed into "arbitraryTerritoriesToAttack" list of that player

        // [toDefend]
        p->toDefend();
        // [toDefend]
        // The method will ask the player to choose a territory it owns to defend
        // The territory will be placed into "_territoriesToDefend_priority" list of that player

    }
    
}
// after this method, there will be 3 lists to use
// player's order list from "issueOrder()"
// player's arbitraryTerritoriesToAttack list from toAttack()
// player's _territoriesToDefend_priority list from toDefend()
// we have to match the orders with the two list in the next phase
// e.g. bomb, blockade and airlift should only be used with toDefend


void GameEngine::ordersExectionPhase()
{
    //this is a 2-way vector to wrap the order and the territory
    std::vector<Orders*, Territory*> orderIssuedAndTerritoryMerged;

    Orders* orders;

    for (Player* p : playersVector)
    {
        //[get the order type]
        // [Deploy]
        if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Deploy") == 0)
        {
            orders = new Deploy();

            // [Deploy is for defense, so get the land from "p->_territoriesToDefend_priority"]
            cout << "Deploy armies to " << p->_territoriesToDefend_priority.front()->getName() << "\n";

            // exceute()

            // [pop the begin() of p->_territoriesToDefend_priority]
            p->_territoriesToDefend_priority.erase(p->_territoriesToDefend_priority.begin());
            // [pop the begin() of p->_territoriesToDefend_priority]
            
            // The order will be pop at the end
        }
        // [Deploy]

        // [Advance]
        else if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Advance") == 0)
        {
            int user_choice; // Let the player choose whether the player wanna send army for offense or defense

            // [Advance is for both offense and defense]
            // [Ask the user to choose between offense and defense]
            cout << "Select a choice between the followings: " << "\n";
            cout << "Press 1 to Attack " << p->arbitraryTerritoriesToAttack.front()->getName() << "\n";
            cout << "OR" << "\n";
            cout << "Press 2 to Defend " << p->_territoriesToDefend_priority.front()->getName() << "\n";
            cin >> user_choice;
            // [Ask the user to choose between offense and defense]
            
            // [Depends on the choice]
            if (user_choice == 1)
            {
                // [Send army for Offense]
                cout << "Advance: Deploy army to attack " << p->arbitraryTerritoriesToAttack.front()->getName() << "\n";

                // exceute()

                // [pop the items from p->arbitraryTerritoriesToAttack]
                p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
                // [pop the items from p->arbitraryTerritoriesToAttack]


                // [Send army for Offense]
            }
            else if (user_choice == 2)
            {
                // [Deploy army for Defense]
                cout << "Advance: Deploy army to defend " << p->_territoriesToDefend_priority.front()->getName() << "\n";

                // [Deploy armies to the targeted player's territory]
                // how to do it?
                // get the source army?
                // [Deploy armies to the targeted player's territory]

                // exceute()

                // [pop the items from p->_territoriesToDefend_priority]
                p->_territoriesToDefend_priority.erase(p->_territoriesToDefend_priority.begin());
                // [pop the items from p->_territoriesToDefend_priority]

                // [Deploy army for Defense]
            }
            else
            {
                cout << "The selection is not recognized. See you next round. " << "\n";
            }
            // [Depends on the choice]

            // The order will be pop at the end
        }
        // [Advance]

        // [Bomb]
        else if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Bomb") == 0)
        {
            // Bomb is for offense
            cout << "Bomb " << p->arbitraryTerritoriesToAttack.front()->getName() << "\n";
            cout << "Half of the armies on will be removed. " << "\n";

            // Half of the armies of the opponents' territory will be gone
            // exceute()

            // [pop the items from p->arbitraryTerritoriesToAttack]
            p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
            // [pop the items from p->arbitraryTerritoriesToAttack]

        }
        // [Bomb]

        // [Blockade]
        else if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Blockade") == 0)
        {
            // Blockade is target the player's own land (Territory from p->_territoriesToDefend_priority)
            // The number of armies on the territory is doubled
            // The ownership of the territory is transferred to the Neutral player.
            cout << "Blockade order is excuded. " << "\n";
            cout << "Targeting " << p->_territoriesToDefend_priority.front()->getName();
            cout << "The number of armies on the territory is doubled" << "\n";
            cout << "The ownership of the territory is transferred to the Neutral player." << "\n";

            // exceute()

            // [pop the items from p->_territoriesToDefend_priority]
            p->_territoriesToDefend_priority.erase(p->_territoriesToDefend_priority.begin());
            // [pop the items from p->_territoriesToDefend_priority]

        }
        // [Blockade]

        // [Airlift]
        else if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Airlift") == 0)
        {
            // Airlift is for offense
            // The selected number of armies is attacking that territory
            // Armies will be taken from the player's territory to the targeted territory
            cout << "The selected number of armies is attacking "<< p->arbitraryTerritoriesToAttack.front()->getName() << "\n";

            // exceute()

            // [pop the items from p->arbitraryTerritoriesToAttack]
            p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
            // [pop the items from p->arbitraryTerritoriesToAttack]

        }
        // [Airlift]

        // [Negotiate]
        else if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Negotiate") == 0)
        {
            // Negotiate targets opponents' territory
            // The effect is that any attack that may be declared between territories of the player issuing the negotiate orderand the target player will result in an invalid order.

            cout << "Negotiate with " << p->arbitraryTerritoriesToAttack.front()->getName() << "'s Owner: " << p->arbitraryTerritoriesToAttack.front()->getOwner()->getName() << "\n";

            // exceute()

            // [pop the items from p->arbitraryTerritoriesToAttack]
            p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
            // [pop the items from p->arbitraryTerritoriesToAttack]

        }
        // [Negotiate]

        else
        {
        cout << "Error" << "\n";
        }
        //[get the order type]

        //[Pop the order out from the orderslist vector]
        p->getOrdersList()->getListOfOrders().erase(p->getOrdersList()->getListOfOrders().begin());
        //[Pop the order out from the orderslist vector]

    }
}

bool GameEngine::ownsContinent()
{
    return true;
}
