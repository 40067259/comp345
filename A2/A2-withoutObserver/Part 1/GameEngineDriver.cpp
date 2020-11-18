#include <iostream>
#include "GameEngine.h"

int main() {
	//This is a test driver that demonstrates 
	//1) different valid maps can be loaded and their validity is verified and invalid maps are gracefully rejected; 
	//2) the right number of players is created, a deck with the right number of cards is created; 
	//3) the observers can be turned on / off during the game start phase.

	GameEngine game;
	game.GameStart();

	int a;
	std::cin>>a;

	return 0;

}