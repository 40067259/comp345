#include "UserInterface.h"
#include "Game.h"
#include <stdlib.h>
#include <iostream>


int main() {
    std::cout << "********************************  STARTUP PHASE ******************************** " << std::endl;
    const auto mapName = UserInterface::selectMap();
    const auto nPlayers = UserInterface::selectNumPlayers();
    Game game = Game(mapName, nPlayers);
    std::vector<Player>& players = game.getTurns();

    std::vector<std::string> allContinents = game.getMap().getContinentNames();

    for (auto& continent : allContinents){
        std::cout << continent << " value is " << game.getMap().getContinentValue(continent) << std::endl;
    }
    Deck gameDeck = game.getDeck();
    std::cout << gameDeck.nCards() << " cards have been loaded into the game.";
    std::cout<< std::endl << "Player turn order: ";
    for (int i = 0; i < players.size(); i++) {
        std::cout << " " << players[i].getID();
    }
    std::cout << "\n\n";

    for (int i = 0; i < players.size(); i++) {
        std::cout << " ~ " << players[i].getID() << " has " << players[i].amtTerritories() << " territories and " << players[i].getPlayerArmies() << " armies." << std::endl;
        players[i].printTerritories();
        std::cout << std::endl;;
    }

    std::cout << "******************************** END STARTUP PHASE ********************************" << std::endl;

    while (game.getTurns().size() > 1) {
        for (auto& player : players) {
            std::cout << "\n******************************** Player "<< player.getIDAsInt() << " Turn: Reinforcement Phase ********************************" << std::endl;
            game.reinforcementPhase(player);
            std::cout << "\n******************************** Player "<< player.getIDAsInt() << " Turn: Attack Phase ********************************" << std::endl;
            game.attackPhase(player);
			std::cout << "\n******************************** Player " << player.getIDAsInt() << " Turn: Fortification Phase ********************************" << std::endl;
			game.fortificationPhase(player);
        }
    }

    std::cout << " The game is over and player " << players[0].getIDAsInt() << " has won.";
    return 0;
}
