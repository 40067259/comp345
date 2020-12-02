#include "GameEngine.h"
#include "..\part1\MapLoader\MapLoader.h"
#include "..\part1\Player\Player.h"
#include "..\part1\Map\Map.h"
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
	//deckCards = new Deck(numberOfPlayers);
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
	while (!exists)
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
	string path2 = path1 + "\\" + selectedMap;
	cout << path2;
	//mapLoader->loadMap(path2);
	mapLoader->loadMap("us.map");
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
		//mapLoader->loadMap(selectedMap);
		mapLoader->loadMap("us.map");
	}
	myMap = &mapLoader->map;
	cout << "Map is valide. Map is loaded." << endl;
}

void GameEngine::playerSelection() {
	cout << "How many players will play? Choose between 2 to 5." << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin >> numberOfPlayers;
	while (numberOfPlayers < 1 || numberOfPlayers > 6) {
		cout << "Invalid. Select between 2 to 5";
		cin >> numberOfPlayers;
	}

	for (int i = 0; i < numberOfPlayers; i++) {
		string name;
		cout << "Enter the name of player " << i + 1 << endl;
		cin >> name;
		Player* player = new Player(name);
		playersVector.push_back(player);
	}

}

bool GameEngine::getObserverStatus() {
	return activateObservers;
}

int GameEngine::getNbOfPlayers() {
	return numberOfPlayers;
}

//==============================================   Part 2 ==================================================== =
void GameEngine::startupPhase() {
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
	for (int j = 0; j < numberOfPlayers; j++) {
		playersVector.at(j)->addReinforcements(armies);
	}

}

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

	// [should also load the map to the each player]
	for (Player* p : playersVector)
	{
		//load map into the map var of each player
	}
	// [should also load the map to the each player]

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


		//This part should be changed to ask player which strategy they would like to use
		int strategySelection = 0;
		std::cout << "Select Strategy: " << "\n";
		std::cout << "Enter 1 for 'Human Player Strategy'\n";
		std::cout << "Enter 2 for 'Aggressive Player Strategy'\n";
		std::cout << "Enter 3 for 'Benevolent Player Strategy'\n";
		std::cout << "Enter 4 for 'Neutral Player Strategyade'\n";
		std::cout << "ENTER 0 TO EXIT\n";
		std::cout << ">>";
		cin >> strategySelection;
		if (strategySelection == 0)
		{
			break;
		}
		else if (strategySelection == 1)
		{
			p->setStrategy("HumanPlayerStrategy");
			std::cout << p->getName() << " selected 1. Human Player Strategy (Printed From GameEngine.cpp)" << "\n";
		}
		else if (strategySelection == 2)
		{
			p->setStrategy("AggressivePlayerStrategy");
			std::cout << p->getName() << " selected 2. Aggressive Player Strategy (Printed From GameEngine.cpp)" << "\n";
		}
		else if (strategySelection == 3)
		{
			p->setStrategy("BenevolentPlayerStrategy");
			std::cout << p->getName() << " selected 3. Benevolent Player Strategy (Printed From GameEngine.cpp)" << "\n";
		}
		else if (strategySelection == 4)
		{
			p->setStrategy("NeutralPlayerStrategy");
			std::cout << p->getName() << " selected 4. Neutral Player Strategy (Printed From GameEngine.cpp)" << "\n";
		}


		if (strategySelection == 1) {

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
			else if (orderNb == 1)
			{
				int numberOfArmies;
				cout << "Enter number of armies you want to deploy:" << endl;
				cin >> numberOfArmies;
				string sourceTerritory;

				cout << "Your territories: " << "\n";
				for (Territory* t : p->getTerritories())
				{
					cout << t->getName() << "\n";
				}
				cout << "\n";

				cout << "Enter name of territory that you want deploy from:" << endl;
				cin >> sourceTerritory;
				string targetTerritory;

				cout << "Enter name of territory that you want deploy to:" << endl;
				cin >> targetTerritory;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(1, p, NULL, myMap->getTerritory(sourceTerritory), myMap->getTerritory(targetTerritory), numberOfArmies);
				//[1. Store order to player's order list]
				//[2. Print out message]           
			}
			else if (orderNb == 2)
			{
				int numberOfArmies2;
				cout << "Enter number of armies you want to advance:" << endl;
				cin >> numberOfArmies2;
				string sourceTerritory2;
				cout << "Enter name of territory that you want advance from:" << endl;
				cin >> sourceTerritory2;
				string targetTerritory2;
				cout << "Enter name of territory that you want advance to:" << endl;
				cin >> targetTerritory2;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(2, p, NULL, myMap->getTerritory(sourceTerritory2), myMap->getTerritory(targetTerritory2), numberOfArmies2);
				//[1. Store order to player's order list]
				//[2. Print out message] 
			}
			else if (orderNb == 3)
			{
				string sourceTerritory3;
				cout << "Enter name of territory that you want to place a bomb:" << endl;
				cin >> sourceTerritory3;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(3, p, NULL, NULL, myMap->getTerritory(sourceTerritory3), 0);
				//[1. Store order to player's order list]
				//[2. Print out message] 
			}
			else if (orderNb == 4)
			{
				string targetTerritory4;
				cout << "Enter name of territory that you want doubling the number of armies on the territory and transferring the ownership of the territory to the Neutral player.:" << endl;
				cin >> targetTerritory4;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(4, p, NULL, NULL, myMap->getTerritory(targetTerritory4), 0);
				//[1. Store order to player's order list]
				//[2. Print out message] 
			}
			else if (orderNb == 5)
			{
				int numberOfArmies5;
				cout << "Enter number of armies you want to airlift:" << endl;
				cin >> numberOfArmies5;
				string sourceTerritory5;
				cout << "Enter name of territory that you want airlift from:" << endl;
				cin >> sourceTerritory5;
				string targetTerritory5;
				cout << "Enter name of territory that you want airlift to:" << endl;
				cin >> targetTerritory5;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(5, p, NULL, myMap->getTerritory(sourceTerritory5), myMap->getTerritory(targetTerritory5), numberOfArmies5);
				//[1. Store order to player's order list]
				//[2. Print out message] 
			}
			else if (orderNb == 6)
			{
				string p2name;
				cout << "Enter name of player that you want negotiate with:" << endl;
				cin >> p2name;
				//issueOrder(1, p, Player* p2, Territory* source, Territory* target, int numberOfArmies);
				p->issueOrder(6, p, getPlayer(p2name), NULL, NULL, 0);
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
			std::cout << "Please select Territory to attack: " << "\n";

			//only print out the land the user does not own
			std::vector<string> temp_territory_vector;
			for (int i = 0; i < myMap->size(); i++)
			{
				for (int j = 0; p->_territories.size(); j++)
				{
					if (((myMap->getTerritory(i)->getName()).compare(p->_territories[j]->getName())) == 0)
					{
						continue;
					}
					else
					{
						//add the territory name to the tamp_territory
						temp_territory_vector.push_back(myMap->getTerritory(i)->getName());
						//add the territory name to the tamp_territory
					}
				}
			}
			int count = 0;
			for (int i = 0; i < temp_territory_vector.size(); i++)
			{
				std::cout << "Press \"" << count << "\" to select " << temp_territory_vector[i] << "\n";
				count++;
			}
			//only print out the land the user does not own

			int user_input;
			std::cin >> user_input;

			for (Territory* t : p->getTerritories())
			{
				if ((myMap->getTerritory(user_input)->getName()).compare(t->getName()))
				{
					std::cout << "You have owned the territory already. You cannot attack your own land. " << "\n";
					std::cout << "Please wait for the next round" << "\n";
					break;
				}
				else
				{
					//problem is in here
					p->toAttack(); //add the territory to attack to the arbitraryTerritoriesToAttack list
					break;
				}
			}
			// [toAttack]

			// [toDefend]
			p->toDefend();
			// [toDefend]

			//problem is in here
			// The method will ask the player to choose a territory it owns to defend
			// The territory will be placed into "_territoriesToDefend_priority" list of that player

		}
		// if the player use AggressivePlayerStrategy, BenevolentPlayerStrategy, and NeutralPlayerStrategy AIs
       else {
	   // none of the AIs can issue order
       p->toAttack();
	   p->toDefend();
	   
        }
	}

}
Player* GameEngine::getPlayer(string name) {
	for (int i = 0; i < playersVector.size(); i++)
	{
		if (playersVector.at(i)->getName() == name) {
			Player* p2 = playersVector.at(i);
			return p2;
		}
		else {
			cout << "cannot find the player." << endl;
		}
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

	/*A new order execution phase*/
	for (Player* p : playersVector)
	{
		//a netral player
		if (p->arbitraryTerritoriesToAttack.size() == 0)
		{
			std::cout << "Player is taking NeutralPlayerStrategy, there is not territory the player would like to attack" << "\n";
		}
		//a neutral player

		//other strategy
		else
		{
			//aggresive player
			if (p->arbitraryTerritoriesToAttack.size() != 0)
			{
				std::cout << "Player is taking AggresivePlayerStrategy. " << "\n";
				std::cout << "Player is attacking. " << "\n";

				//get the territory to attack
				//pop from the arbitraryTerritoriesToAttack vector
				string territoryToAttack = p->arbitraryTerritoriesToAttack.front()->getName(); // store the name of the territory to atack temporily for every round
				std::cout << "Player is going to attack " << p->arbitraryTerritoriesToAttack.front()->getName() << "\n";
				//pop from the arbitraryTerritoriesToAttack vector
				//get the territory to attack

				//get the order
				string order = p->getOrdersList()->getListOfOrders().front()->getOrderType();
				std::cout << "Player is executing " << order << " order. " << "\n";
				//get the order

				//execute the attacking order
				//...
				//execute the attacking order

			}
			//aggresive player



		}
		//pther strategy

	}



	/*A new order execution phase*/




	//this is a 2-way vector to wrap the order and the territory
	//std::vector<Orders*, Territory*> orderIssuedAndTerritoryMerged;

	Orders* orders;

	for (Player* p : playersVector)
	{

		cout << "It is " << p->getName() << "'s Orders Exection Phase now!" << "\n";

		//[get the order type]
		// [Deploy]
		if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("Deploy") == 0)
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
		else if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("advance") == 0)
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
		else if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("bomb") == 0)
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
		else if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("blockade") == 0)
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
		else if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("airlift") == 0)
		{
			// Airlift is for offense
			// The selected number of armies is attacking that territory
			// Armies will be taken from the player's territory to the targeted territory
			cout << "The selected number of armies is attacking " << p->arbitraryTerritoriesToAttack.front()->getName() << "\n";

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

			int count = 0;
			int userinput_armySource;
			cout << "Which Territory you would like to take the army from?" << "\n";
			for (Territory* t : p->getTerritories())
			{
				cout << "Press " << count << " for " << t->getName() << "\n";
				count++;
			}
			cin >> userinput_armySource;

			//[Execute Airlift]
			orders = new Airlift(p, userinput, p->getTerritories()[userinput_armySource], p->arbitraryTerritoriesToAttack.front());
			orders->execute();
			//[Execute Airlift]

			// [pop the items from p->arbitraryTerritoriesToAttack]
			p->arbitraryTerritoriesToAttack.erase(p->arbitraryTerritoriesToAttack.begin());
			// [pop the items from p->arbitraryTerritoriesToAttack]
		}
		// [Airlift]

		// [Negotiate]
		else if ((p->getOrdersList()->getListOfOrders().front()->getOrderType()).compare("negotiate") == 0)
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
		//Problem is in here
		//p->getOrdersList()->getListOfOrders().erase(p->getOrdersList()->getListOfOrders().begin());
		//[Pop the order out from the orderslist vector]

	}
}

//====================================================================added for Part 3 =====================================================================================
