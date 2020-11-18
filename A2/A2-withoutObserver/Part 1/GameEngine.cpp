#include "GameEngine.h"
#include "Maploader.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using std::cout;
using std::cin;
using std::string;

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
	while(!exists)
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
	gameMap = & mapLoader->map;
	cout << "Map is valide. Map is loaded." << endl;
	}

void GameEngine::playerSelection() {
	cout << "How many players will play? Choose between 2 to 5."<<endl;
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
		Player *player = new Player(name);
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


