#pragma once

#include "Map.h"
#include "Subject.h"
#include "Deck.h"
#include "Territory.h"
#include <vector>

class Player;

class Game : public Subject {

private:
	Deck deck;
	static Map map;
	std::vector<Player> players;
	static std::vector<Player> turns;
	int numPlayers;
    int currentPhase;
	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);
	void assignTurns();
	void startUp();
	void assignArmies();
	void assignObservers();

public:
	Game(const std::string& mapName, int nPlayers);
	std::vector<Player>& getTurns();
	std::vector<Player> getUnorderedPlayers() { return players;}
	void reinforcementPhase(Player& player);
	void fortificationPhase(Player& player);
	Map getMap() const;
	static Player& getOwner(const Territory& territory);
	static int getArmiesToAdd(const Player& player);
	static std::vector<Territory> checkAvailableSourceTerritoriesToFortify(Player& player);
	static std::vector<Territory> checkAvailableTargetTerritoriesToFortify(Player& player, Territory source);
	static std::vector<Territory> checkAvailableAttackingTerritoriesToAttack(Player& player);
	static std::vector<Territory> checkAvailableDefendingTerritoriesToAttack(Player& player, Territory source);
	void attackPhase(Player& player);
	void removeDeadPlayers();
	Deck getDeck();
};
