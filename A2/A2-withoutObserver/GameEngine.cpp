#include "GameEngine.h"
#include "Maploader.h"
#include "Player.h"
#include "Territory.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <time.h>
#include <typeinfo>
#include <random>
#include <stdlib.h>
#include <cmath>

namespace fs = std::filesystem;
//std::filesystem::current_path(std::filesystem::temp_directory_path());
using std::cout;
using std::cin;
using std::string;
using std::vector;

GameEngine::GameEngine() {
}

GameEngine::~GameEngine() {
	delete gameMap;
	delete mapLoader;
	delete deckCards;
	gameMap = NULL;
	mapLoader = NULL;
	deckCards = NULL;
}

//method that starts the game
void GameEngine::GameStart() {
	cout << "=======================================" << endl;
	cout << "          LET'S PLAY RISK              " << endl;
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
	deckCards = new Deck(nbOfPlayers);
	cout << "A deck of cards created." << endl;
}

// select a map to load and check map validation
void GameEngine::mapSelection() {

	// get a list of maps from "/path/to/directory";
	string path1 = "test_maps";
	// print a list of maps
	cout << "Choose a map from the list below by entering the map's name (e.g. canada.map)" << std::endl;

	for (auto& entry : std::experimental::filesystem::directory_iterator(path1))
	{
		cout << entry.path().filename() << endl;
	}

	selectedMap = "";
	//Get input from the user for the map name
	cin >> selectedMap;

	// check if the file exists
	bool exists = false;

	for (auto& entry : std::experimental::filesystem::directory_iterator(path1))
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
		for (auto& entry : std::experimental::filesystem::directory_iterator(path1))
		{
			if (entry.path().filename() == selectedMap) {
				exists = true;
			}
		}
	}

	// try to load a map and check map validity
	gameMap = new Map();
	mapLoader = new MapLoader();
	string path2 = path1 + "\\" + selectedMap;
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
	gameMap = &mapLoader->map;
	cout << "Map is valide. Map is loaded." << endl;
}

void GameEngine::playerSelection() {
	cout << "How many players will play? Choose between 2 to 5." << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin >> nbOfPlayers;
	while (nbOfPlayers < 1 || nbOfPlayers > 6) {
		cout << "Invalid. Select between 2 to 5";
		cin >> nbOfPlayers;
	}

	for (int i = 0; i < nbOfPlayers; i++) {
		string name;
		cout << "Enter the name of player " << i + 1 << endl;
		cin >> name;
		Player* player = new Player(name);
		players.push_back(player);
	}

}

int GameEngine::getNbOfPlayers() {
	return nbOfPlayers;
}

Deck* GameEngine::getDeckCards() {
	return deckCards;
}

vector<Player*> GameEngine::getPlayersList() {
	return players;
}

bool GameEngine::getObserverStatus() {
	return activateObservers;
}



//---------------------------------part 2: game play: game startup phase----------------------------
void GameEngine::gameStartupPhase() {

	cout << "this is the game play: game startup phase..." << endl;

	// 1. the order of play of the players in the game is determined randomly.
	randomOrderOfPlayers();

	// 2. all territories in the map are randomly assigned to players one by one in a round-robin fashion.
	territoriesAssignment();

	// 3. players are given a number of initial armies.
	armiesInitialization();
}

// 1. the order of play of the players in the game is determined randomly.
void GameEngine::randomOrderOfPlayers() {

	cout << "\nthe order of play of the players in the game is determined randomly: \n" << endl;

	std::random_device device;
	std::mt19937 generator(device());

	shuffle(playersVector.begin(), playersVector.end(), generator);

	for (int i = 0; i < playersVector.size(); i++) {
		cout << "the name of player number " << i << " is: " << playersVector[i]->getname() << "." << endl;
	}
}

// 2. all territories in the map are randomly assigned to players one by one in a round-robin fashion.
void GameEngine::territoriesAssignment() {

	cout << "\nall territories in the map are randomly assigned to players one by one in a round-robin fashion: \n" << endl;

	// create a mapvector of size gamemap->size() and it stores value between 0 and gamemap->size()-1.
	vector<int> mapvactor(gameMap->size());
	std::random_device device;
	std::mt19937 generator(device());
	for (int i = 0; i < gameMap->size(); i++) {
		mapVector[i] = i;
	}

	// shuffle the mapvector and each value is used to randomly assign a territory to a player.
	shuffle(mapVector.begin(), mapVector.end(), generator);

	int index = 0;
	for (int i = 0; i < gameMap->size(); i++) {

		if (index == playersVector.size()) {
			index = 0;
		}

		playersVector[index % playersVector.size()]->addterritory(gameMap->getTerritory(mapVector[i]));
		index++;

		cout << "\nplayer " << playersVector[index]->getname() << " is assigned to territory: "
			<< gameMap->getTerritory(mapVector[i])->getname() << "." << endl;
	}
	

}

// 3. players are given a number of initial armies.
void GameEngine::armiesInitialization() {

	cout << "\nplayers are given a number of initial armies: \n" << endl;

	if (playersVector.size() == 2) {
		for (int i = 0; i < playersVector.size(); i++) {
			playersVector[i]->setreinforcements(40);
		}
	}
	else if (playersVector.size() == 3) {
		for (int i = 0; i < playersVector.size(); i++) {
			playersVector[i]->setreinforcements(35);
		}
	}
	else if (playersVector.size() == 4) {
		for (int i = 0; i < playersVector.size(); i++) {
			playersVector[i]->setreinforcements(30);
		}
	}
	else if (playersVector.size() == 5) {
		for (int i = 0; i < playersVector.size(); i++) {
			playersVector[i]->setreinforcements(25);
		}
	}

	cout << "there are " << playersVector.size() << " players and each of them is given "
		<< playersVector[0]->getreinforcements() << " number of initial armies." << endl;
}