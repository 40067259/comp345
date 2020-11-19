#include <iostream>
#include "GameEngine.h"

int main() {
	//This is a test driver that demonstrates 
	// Part 1
	//1) different valid maps can be loaded and their validity is verified and invalid maps are gracefully rejected; 
	//2) the right number of players is created, a deck with the right number of cards is created; 
	//3) the observers can be turned on / off during the game start phase.

	GameEngine *game = new GameEngine();
	game->GameStart();

	// Part 2
	// 1) all territories in the map have been assigned to one and only one player
	game->startupPhase();
	game->myMap->printMapInfo();
	// 2) Players are given a number of armies;
	int num = game->getNbOfPlayers();
	for (int i = 0; i < num; i++){
		std::cout<<"Player "<<game->players.at(i)->getName()<<" owns ";
		std::cout << game->playersVector.at(i)->getReinforcements() <<" armies."<<std::endl;
	}
	// 3) all players have all the orders for playing in a turn.
	std::cout << "The order of players in game:" << std::endl;
	for (int i = 0; i < game->playersVector.size(); i++) {
		std::cout << " Player " << game->playersVector.at(i)->getName() << " : "<< i << std::endl;
	}
	int a;
	cin >> a;

	return 0;

}
