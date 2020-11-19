#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <utility>
#include <random>
#include <cmath>
// If you use the latest version of c++ (c++17), please replace the lines commented as "for c++14" by the ones marked as "for c++17"
#include <experimental/filesystem>  // for c++ 14 
namespace fs = std::experimental::filesystem; // for c++ 14
//#include <filesystem>  // for c++ 17
//namespace fs = std::filesystem; // for c++ 17
//fs::current_path(fs::temp_directory_path());// for c++ 17


using std::cout;
using std::cin;
using std::string;
using std::shuffle;

GameEngine::GameEngine() {
}

GameEngine::~GameEngine() {
	delete myMap;
	delete mapLoader;
	delete deckCards;
	myMap = NULL;
	mapLoader = NULL;
	deckCards = NULL;
}

//method that starts the game
void GameEngine::GameStart() {
	cout << "=======================================" << endl;
	cout << "          LET'S PLAY WARZONE           " << endl;
	cout << "=======================================" << endl;

	// Step 1: turn on/off Observer
	cout << "Please choose to turn on or off Observers." << endl;
	cout << "Enter 1 to turn on or turn 2 to turn off." << endl;
	int option;
	cin >> option;
	while (option != 1 && option != 2) {
		cout << "Wrong option. Enter 1 to turn on or enter 2 to turn off." << endl;
		cin >> option;
	}

	if (option == 1) {
		cout << "Observer is on." << endl;
	}
	else {
		cout << "Observer turned off." << endl;
	}

	// Select the map and check the validation
	mapSelection();
	

	// Select the amount of players
	// when each player is created, an empty hand of cards and an empty order list is assigned.
	playerSelection();

	// create a deck of cards, the number of cards = number of players x 5 kinds of cards x 10 cards of each type
	deckCards = new Deck(numberOfPlayers);
	cout << "A deck of cards created." << endl;
}

	// select a map to load and check map validation
void GameEngine::mapSelection() {

	// get a list of maps from "/path/to/directory";
   string path1 = "test_maps";
	// print a list of maps
   cout << "Choose a map from the list below by entering the map's name (e.g. canada.map)" << std::endl;
	for (auto& entry : std::experimental::filesystem::directory_iterator(path1))  // for c++14
	//for (auto& entry : std::filesystem::directory_iterator(path1))  // for c++17	
	{
		cout << entry.path().filename() << endl;
	}

	selectedMap = "";
	//Get input from the user for the map name
	cin >> selectedMap;

	// check if the file exists
	bool exists = false;

	for (auto& entry : std::experimental::filesystem::directory_iterator(path1)) // for c++14
	//for (auto& entry : std::filesystem::directory_iterator(path1)) // for c++17
	{
		if (entry.path().filename() == selectedMap) {
			exists = true;
		}
	}
	while(!exists)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please enter a valid map name" << endl;
		cin >> selectedMap;
		for (auto& entry : std::experimental::filesystem::directory_iterator(path1)) // for c++14
		//for (auto& entry : std::filesystem::directory_iterator(path1)) // for c++17	
		{
			if (entry.path().filename() == selectedMap) {
				exists = true;
			}
		}
	}

	// try to load a map and check map validity
    myMap = new Map();
        mapLoader = new MapLoader();
        string path2 = path1 +"\\"+ selectedMap;
        cout << path2;
        mapLoader->loadMap(path2);

	// map validation test
	while (!mapLoader->map.validate()) {
		
		cout << "Invalide map." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please enter a valid map name" << endl;
		cin >> selectedMap;
		//Delete the bad map object and create a new one
		delete mapLoader;
		mapLoader = new MapLoader();
		mapLoader->loadMap(selectedMap);
		}
	myMap = & mapLoader->map;
	cout << "Map is valide. Map is loaded." << endl;
	}

void GameEngine::playerSelection() {
	cout << "How many players will play? Choose between 2 to 5."<<endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin >> numberOfPlayers;
	while ( numberOfPlayers < 1 ||  numberOfPlayers > 6) {
		cout << "Invalid. Select between 2 to 5";
		cin >>  numberOfPlayers;
	}

	for (int i = 0; i < numberOfPlayers; i++) {
		string name;
		cout << "Enter the name of player " << i + 1 << endl;
		cin >> name;
		Player *player = new Player(name);
		playersVector.push_back(player);
	}

}
/*
//---------------------------Part 2: Game play: game startup phase----------------------------------
void GameEngine::gameStartupPhase() {

    cout << "GAME PLAY: initializing game startup phase..." << endl;

    // 1. The order of play of the players in the game is determined randomly.
    randomOrderOfPlayers();

    // 2. All territories in the map are randomly assigned to players one by one in a round-robin fashion.
    territoriesAssignment();

    // 3. Players are given a number of initial armies.
    armiesInitialization();
}


// 1. The order of play of the players in the game is determined randomly.
void GameEngine::randomOrderOfPlayers() {

    cout << "\nThe order of play of the players in the game is determined randomly..." << endl;

    std::random_device device;
    std::mt19937 generator(device());

    shuffle(playersVector.begin(), playersVector.end(), generator);

    for (int i = 0; i < playersVector.size(); i++) {
        cout << "\nThe order of play for player  " << playersVector[i]->getName() << " is: " << i << "." << endl;
    }
}


// 2. All territories in the map are randomly assigned to players one by one in a round-robin fashion.
void GameEngine::territoriesAssignment() {

    cout << "\nRandomly assign all territories in the map to players one by one in a round-robin fashion..." << endl;

    // Create a mapVector of size myMap->size() and it stores value between 0 and myMap->size()-1.
    vector<int> mapVector(myMap->size());
    std::random_device device;
    std::mt19937 generator(device());

    for (int i = 0; i < myMap->size(); i++) {
        mapVector[i] = i;
    }

    // Shuffle the mapVector and each value is used to randomly assign a territory to a player.
    shuffle(mapVector.begin(), mapVector.end(), generator);

    int index = 0;
    for (int i = 0; i < myMap->size(); i++) {

        if (index == playersVector.size()) {
            index = 0;
        }

        playersVector[index % playersVector.size()]->addTerritory(myMap->getTerritory(mapVector[i]));
        index++;

        cout << "\nTerritory \"" << myMap->getTerritory(mapVector[i])->getName() << "\" is assigned to player: "
             << playersVector[index]->getName() << "." << endl;
    }
}

// 3. Players are given a number of initial armies.
void GameEngine::armiesInitialization() {

    cout << "\nPlayers are given a number of initial armies..." << endl;

    if (playersVector.size() == 2) {
        for (int i = 0; i < playersVector.size(); i++) {
            playersVector[i]->setReinforcements(40);
        }
    }
    else if (playersVector.size() == 3) {
        for (int i = 0; i < playersVector.size(); i++) {
            playersVector[i]->setReinforcements(35);
        }
    }
    else if (playersVector.size() == 4) {
        for (int i = 0; i < playersVector.size(); i++) {
            playersVector[i]->setReinforcements(30);
        }
    }
    else if (playersVector.size() == 5) {
        for (int i = 0; i < playersVector.size(); i++) {
            playersVector[i]->setReinforcements(25);
        }
    }

    cout << "\nThere are " << playersVector.size() << " players and each of them is given "
         << playersVector[0]->getReinforcements() << " number of initial armies." << endl;

    for(int i = 0; i < playersVector.size(); i++){
        cout << playersVector[i]->getName() << " has " << playersVector[i]->getReinforcements()
        << " initialized armies placed in the reinforcement pool." << endl;
    }
}

*/
bool GameEngine::getObserverStatus() {
	return activateObservers;
}

int GameEngine::getNbOfPlayers() {
	return numberOfPlayers;
}

==============================================   Part 2 =====================================================
void GameEngine::startupPhase()
{
	//Shuffle the order of the players, order is determined randomly.
	random_shuffle(playersVector.begin(), playersVector.end());

	//Create a vector of not distributed territories
	vector<int> remaining;
	for (int i = 0; i < myMap->size(); i++)
	{
		remaining.push_back(i);
	}

	//Assign a remaining territory to each currentPlayerTurn, one by one
	for (int i = 0; i < myMap->size(); i++)
	{
		//Get random member of remaining, obtain it's index value, then remove it
		int j = rand() % remaining.size();
		int index = remaining[j];
		remaining.erase(remaining.begin() + j);
		//Find the territory at the given index and set it's new owner
		Territory* territory = myMap->getTerritory(index);
		Player* p = playersVector.at(i % numberOfPlayers);

		territory->setOwner(p);
		p->addTerritory(territory);
	}

	//Players are given a number of initial armies (A), where A is:			
	// 2 players, A = 40
	// 3 players, A = 35
	// 4 players, A = 30
	// 5 players, A = 25
	int armies = 40 - (numberOfPlayers - 2) * 5;

		// Players are given a number of armies;
	for (int j = 0; j < nbOfPlayers; j++){
			playersVector.at(j)->addReinforcements(armies);
		}

}
=============================================================================================================
vector<Player*> GameEngine::getPlayersVector() {
    return playersVector;
}

//====================================================================added for Part 3 =====================================================================================

//==========PART 3: MAIN GAME LOOP==========//
void GameEngine::mainGameLoop() {

    reinforcementPhase();

    bool notAWinnerYet = true;

    while (notAWinnerYet)
    {

        //check if a player owns no land
        int count = 0;
        for (Player* p : playersVector) {
            if (p->getTerritories().size() == 0) {
                playersVector.erase(playersVector.begin() + count);
                cout << "Since you own no land, you are kicked out from the game. Bye." << "\n";
            }
            count++;
        }

        issuingOrderPhase();
        ordersExectionPhase();

        //check winner
        for (Player* p : playersVector) {
            if (p->getTerritories().size() == myMap->size())
            {
                notAWinnerYet = false;
                cout << p->getName() << " won. " << "\n";
                cout << "The game is ended" << "\n";
            }
        }
    }


}


//PART 3 - ReinforcementPhase
void GameEngine::reinforcementPhase() {
    //For each player playing the game, give them armies
    for (Player* p : playersVector) { 

        cout << "It is " << p->getName() << "'s Reinforcement Phase now!" << "\n";

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
        unordered_map<string, Continent> tableOfContinents = myMap->getContinents();
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
        cout << "It is " << p->getName() << "'s Issuing Orders Phase now!" << "\n";

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
        for (int i = 0; i < myMap->size(); i++) 
        {
            std::cout << "Press \"" << count << "\" to select " << myMap->getTerritory(i) << "\n"; 
            count++;
        }
        int user_input;
        std::cin >> user_input;

        if (std::count(p->getTerritories().begin(), p->getTerritories().end(), myMap->getTerritory(user_input - 1))) //check if player have the territory already 
        {
            std::cout << "You have owned the territory already";
            std::cout << "Please wait for the next round";
        }
        else
        {
            p->toAttack(myMap->getTerritory(user_input - 1)); //add the territory to attack to the arbitraryTerritoriesToAttack list
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

        cout << "It is " << p->getName() << "'s Orders Exection Phase now!" << "\n";

        //[get the order type]
        // [Deploy]
        if ((p->getOrdersList()->getListOfOrders().front()->orderType).compare("Deploy") == 0)
        {
            // [Deploy is for defense, so get the land from "p->_territoriesToDefend_priority"]
            cout << "Deploy armies to " << p->_territoriesToDefend_priority.front()->getName() << "\n";

            // [pop the begin() of p->_territoriesToDefend_priority]
            p->_territoriesToDefend_priority.erase(p->_territoriesToDefend_priority.begin());
            // [pop the begin() of p->_territoriesToDefend_priority]
            
            //[Execute Deploy]
            orders = new Deploy();
            orders->execute();
            //[Execute Deploy]

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

                // [pop the items from p->arbitraryTerritoriesToAttack]
                p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
                // [pop the items from p->arbitraryTerritoriesToAttack]

                // [Send army for Offense]
            }
            else if (user_choice == 2)
            {
                // [Deploy army for Defense]
                cout << "Advance: Deploy army to defend " << p->_territoriesToDefend_priority.front()->getName() << "\n";

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

            //[Execute Advance]
            orders = new Advance();
            orders->execute();
            //[Execute Advance]

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

            //[Execute Bomb]
            orders = new Advance();
            orders->execute();
            //[Execute Bomb]

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

            //[Execute Blockade]
            orders = new Blockade(p, p->_territoriesToDefend_priority.front());
            orders->execute();
            //[Execute Blockade]

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

            int userinput;
            cout << "How many army you are gonna send? " << "\n";
            cout << "You have " << p->getArmies() << "." << "\n";
            cout << "Please enter the number of armies you are gonna send" << "\n";
            cin >> userinput;
            while (userinput > p->getArmies())
            {
                cout << "Invalid numbers, please enter again.";
                cin >> userinput;
            }

            //TODO: i have no idea how to execute
            //[Execute Airlift]
            orders = new Airlift(p, userinput, p->_territoriesToDefend_priority.front(), p->_territoriesToDefend_priority.front()->getName());
            orders->execute();
            //[Execute Airlift]

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

            //[Execute Negotiate]
            orders = new Negotiate(p, p->arbitraryTerritoriesToAttack.front()->getOwner());
            orders->execute();
            //[Execute Negotiate]

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

//====================================================================added for Part 3 =====================================================================================



