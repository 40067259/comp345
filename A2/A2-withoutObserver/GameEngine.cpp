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

void GameEngine::reinforcementPhase() {
    for (Player* p : playersVector) {
        int armiesGiven = 3;

        int territoriesowned = p->getTerritories().size();
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

}
