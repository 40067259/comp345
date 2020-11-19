#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
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






