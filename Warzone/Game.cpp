#include "Game.h"
#include "MapLoader.h"
#include "UserInterface.h"
#include "HumanPlayer.h"
#include "AggressivePlayer.h"
#include "BenevolentPlayer.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <time.h>

Map Game::map = Map();
std::vector<Player> Game::turns = {};

int Game::getArmiesToAdd(const Player& player) {
    // Number of territories owned on the map, divided by 3 (rounded down), with a minimum of 3
    int armiesFromTerritories = std::max((int) player.getTerritories().size() / 3, 3);

    // Continent-control value of all continents totally controlled by that player
    const auto continentsOwned = map.continentsOwned(player);
    int armiesFromContinents = std::accumulate(continentsOwned.begin(), continentsOwned.end(), 0, [&](int i, const std::string& c) {
        return i + map.getContinentValue(c);
    });
    return armiesFromTerritories + armiesFromContinents;
}

Player& Game::getOwner(const Territory& territory) {
    for (auto& player : turns) {
        for (const auto& c : player.getTerritories()) {
            if (c == territory) {
                return player;
            }
        }
    }
}

void Game::setGameMap(const std::string& mapName) {
    Map map = MapLoader::loadMap(mapName);
    this->map = map;
}

void Game::createPlayers(int nPlayers) {
    for (int i = 0; i < nPlayers; i++) {
		if (i == 1) {
			players.push_back(Player(std::vector<Territory>(), Hand(), DiceFacility(), i + 1, new BenevolentPlayer()));
		}
		else if (i == 2) {
			players.push_back(Player(std::vector<Territory>(), Hand(), DiceFacility(), i + 1, new AggressivePlayer()));
		}
		else {
			players.push_back(Player(std::vector<Territory>(), Hand(), DiceFacility(), i + 1, new HumanPlayer()));
		}
    }
}

void Game::assignTurns() {
    int numplayers = players.size();
    for (int i = 0; i < numplayers; i++) {
        int r = rand() % players.size();
        turns.push_back(players.at(r));
        players.erase(players.begin() + r);
    }
}

void Game::assignArmies() {
    int nArmies;

    if (turns.size() == 2) {
        nArmies = 40;
    }
    else if (turns.size() == 3) {
        nArmies = 35;
    }
    else if (turns.size() == 4) {
        nArmies = 30;
    }
    else if (turns.size() == 5) {
        nArmies = 25;
    }
    else if (turns.size() == 6) {
        nArmies = 20;
    }

    for (int i = 0; i<turns.size(); i++) {
        turns[i].setArmies(nArmies);
        turns[i].initializeArmies();
    }
}

void Game::assignObservers() {
    for (auto& player : turns){
        attach(&player);
    }
    setTotalTerritories(map.getTerritories().size());
}

void Game::startUp() {
    int index = 0;
    for (int i = 0; i < map.getTerritories().size(); i++) {
        if (index == numPlayers)
            index = 0; //if index gets after last player,wrap around turns array to start again at player1
        turns[index++].assignTerritory(map.getTerritories()[i]);

    }
    assignArmies();
}

std::vector<Player>& Game::getTurns() {
    return turns;
}
Game::Game(const std::string& fileName, int nPlayers) {
    srand(time(NULL));
    numPlayers = nPlayers;
    setGameMap(fileName);
    deck.loadDeck(map.getTerritories());
    createPlayers(nPlayers);
    assignTurns();
    assignObservers();
    startUp();
}

void Game::reinforcementPhase(Player& player) {
    currentPhase = 1;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

    player.executeReinforcement(&player);
}

void Game::fortificationPhase(Player& player) {
    currentPhase = 3;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

	player.executeFortify(&player);
}

Map Game::getMap() const {
    return	this->map;
}

std::vector<Territory> Game::checkAvailableSourceTerritoriesToFortify(Player& player) {
    std::vector<Territory> territories = player.getTerritories();

    // Removing territories from the vector which do not have adjacent territories that the player owns
    territories.erase(std::remove_if(territories.begin(), territories.end(), [&](const Territory& c) {
        std::vector<Territory> adjacentTerritories = Game::map.adjacent(c);
        adjacentTerritories.erase(std::remove_if(adjacentTerritories.begin(), adjacentTerritories.end(), [&](const Territory& c) {
            for (auto& territory : territories) {
                if (territory.getName() == c.getName()) {
                    return false;
                }
            }
            return true;
        }), adjacentTerritories.end());

		// If the territory has no adjacent territories, remove from available source territories
        if (adjacentTerritories.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }), territories.end());

    return territories;
}

std::vector<Territory> Game::checkAvailableTargetTerritoriesToFortify(Player& player, Territory source) {
	std::vector<Territory> territories = player.getTerritories();
	std::vector<Territory> adjacentTerritories = map.adjacent(source);

	// Removing adjacent territories to the Source that the player does not own
	adjacentTerritories.erase(std::remove_if(adjacentTerritories.begin(), adjacentTerritories.end(), [&](const Territory& c) {
		for (auto& territory : territories) {
			if (territory.getName() == c.getName()) {
				return false;
			}
		}
		return true;
	}), adjacentTerritories.end());

	return adjacentTerritories;
}

std::vector<Territory> Game::checkAvailableAttackingTerritoriesToAttack(Player& player) {
    std::vector<Territory> territories = player.getTerritories();

    // Removing territories from the vector which have adjacent territories that the player owns
    territories.erase(std::remove_if(territories.begin(), territories.end(), [&](const Territory& c) {
        std::vector<Territory> adjacentTerritories = map.adjacent(c);
        adjacentTerritories.erase(std::remove_if(adjacentTerritories.begin(), adjacentTerritories.end(), [&](const Territory& c) {
            for (auto& territory : territories) {
                if (territory.getName() == c.getName()) {
                    return true;
                }
            }
            return false;
        }), adjacentTerritories.end());

        // Removing territories that have no adjacent enemy territories or that don't have at least 2 armies
        if (adjacentTerritories.size() == 0 || c.getArmies() < 2) {
            return true;
        }
        else {
            return false;
        }
    }), territories.end());

    return territories;
}

std::vector<Territory> Game::checkAvailableDefendingTerritoriesToAttack(Player& player, Territory source) {
	std::vector<Territory> territories = player.getTerritories();
	std::vector<Territory> adjacentTerritories = map.adjacent(source);

	// Removing adjacent territories to the Source that the player does not own
	adjacentTerritories.erase(std::remove_if(adjacentTerritories.begin(), adjacentTerritories.end(), [&](const Territory& c) {
		for (auto& territory : territories) {
			if (territory.getName() == c.getName()) {
				return true;
			}
		}
		return false;
	}), adjacentTerritories.end());

	return adjacentTerritories;
}

void Game::attackPhase(Player& attacker) {
    currentPhase = 2;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

	attacker.executeAttack(&attacker);

    removeDeadPlayers();
}

void Game::removeDeadPlayers() {
    std::vector<int> playersIndicesToDelete;
	std::vector<int> playersIndicesToDetach;
    for (int i = 0; i < players.size(); ++i) {
        const auto player = players[i];
        if (player.getTerritories().empty()) {
            playersIndicesToDelete.push_back(i);
        }
    }

	for (int i = 0; i < turns.size(); i++) {
		const auto player = turns[i];
		if (player.getTerritories().empty()) {
			playersIndicesToDetach.push_back(i);
		}
	}

    for (int i : playersIndicesToDelete) {
        players.erase(players.begin() + i);
    }

	for (int i : playersIndicesToDetach) {
		detach(&turns[i]);
	}
}

Deck Game::getDeck() {
    return deck;
}
