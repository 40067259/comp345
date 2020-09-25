#pragma once

#include <string>
#include "Player.h"
#include "Map.h"

class UserInterface {
public:
	static std::string selectMap();
	static int selectNumPlayers();

	static Territory selectTerritory(std::vector<Territory> territories);
	static int selectArmiesToReinforce(const Territory& territory, int armiesRemaining);
	static int exchangeCards(Player& player);
	static Territory selectAdjacentTerritory(std::vector<Territory> adjacentCountries); // TODO: Updating armies issue
	static int selectArmiesToMove(const Territory& territory);
	static bool toAttackOrNot();
	static int selectAttackerDice(const Territory& attackingTerritory);
	static int selectDefenderDice(const Territory& defendingTerritory);
};
