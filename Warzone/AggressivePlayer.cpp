#include "AggressivePlayer.h"
#include "Game.h"
#include "UserInterface.h"
#include <iostream>
#include <string>

void AggressivePlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	int armiesToAdd = Game::getArmiesToAdd(player);
	std::cout << "Aggressive Player has " << armiesToAdd << " armies for reinforcement." << std::endl;

	int maxArmies = 0;
	std::string strongestTerritory;
	
	for (auto& territory : player.getTerritories()) {
		if (territory.getArmies() > maxArmies) {
			maxArmies = territory.getArmies();
			strongestTerritory = territory.getName();
		}
	}

	for (auto& c : player.getTerritories()) {
		if (strongestTerritory == c.getName()) {
			c.increaseArmiesBy(armiesToAdd);
			std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
		}
	}
}

void AggressivePlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	std::vector<Territory> attackingTerritories = Game::checkAvailableAttackingTerritoriesToAttack(attacker);
	bool lostStrongestTerritory = false;

	if (attackingTerritories.size() > 0) {
		int maxArmies = 0;
		std::string strongestTerritory;

		for (auto& territory : attacker.getTerritories()) {
			if (territory.getArmies() > maxArmies) {
				maxArmies = territory.getArmies();
				strongestTerritory = territory.getName();
			}
		}

		for (auto& attackingTerritory : attacker.getTerritories()) {
			if (strongestTerritory == attackingTerritory.getName()) {
				std::vector <Territory> defendingTerritories = Game::checkAvailableDefendingTerritoriesToAttack(attacker, attackingTerritory);

				while (defendingTerritories.size() != 0) {
					Territory defendingTerritory = defendingTerritories[0];
					Player& defender = Game::getOwner(defendingTerritory);

					int nDiceAttacker = std::max(attackingTerritory.getArmies() - 1, 3);
					if (nDiceAttacker > 3) {
						nDiceAttacker = 3;
					}

					int nDiceDefender;
					for (auto& c : defender.getTerritories()) {
						if (c.getName() == defendingTerritory.getName()) {
							nDiceDefender = std::max(defendingTerritory.getArmies(), 2);
							if (nDiceDefender > 2) {
								nDiceDefender = 2;
							}
							break;
						}
					}

					std::cout << "Rolling dice..." << std::endl;
					std::vector<int> attDiceResults = attacker.getDice().rollDice(nDiceAttacker);
					std::vector<int> defDiceResults = defender.getDice().rollDice(nDiceDefender);

					std::cout << "Comparing dice..." << std::endl;
					std::cout << "Attacker rolled...";
					for (const auto& i : attDiceResults) {
						std::cout << " " << i;
					}
					std::cout << std::endl;
					std::cout << "Defender rolled...";
					for (const auto& i : defDiceResults) {
						std::cout << " " << i;
					}
					std::cout << std::endl;

					// Getting the minimum number of dice roll
					int min = std::min(attDiceResults.size(), defDiceResults.size());

					for (int i = 0; i < min; i++) {
						if (attDiceResults[i] > defDiceResults[i]) {
							// Attacker wins
							std::cout << "The attacker has rolled " << attDiceResults[i] << " and the defender has rolled " << defDiceResults[i] << "." << std::endl;
							std::cout << "The defender loses 1 army on " << defendingTerritory.getName() << "." << std::endl;

							for (auto& c : defender.getTerritories()) {
								if (c.getName() == defendingTerritory.getName()) {
									c.decreaseArmiesBy(1);
									if (c.getArmies() == 0) {
										// Moving ONE army from attacking territory to defending territory
										// Giving defeated territory to attacker
										c.increaseArmiesBy(1);
										attacker.getTerritories().push_back(Territory(c));

										std::cout << c.getName() << " has been defeated. Aggressive Player has moved 1 army to the newly conquered territory." << std::endl;

										// Removing defeated territory from defender
										const auto pos = std::find(defender.getTerritories().begin(), defender.getTerritories().end(), c);
										defender.getTerritories().erase(pos);
										defendingTerritories = Game::checkAvailableDefendingTerritoriesToAttack(attacker, attackingTerritory);
									}
									break;
								}
							}
						}
						else {
							// Defenders wins
							std::cout << "The defender has rolled " << defDiceResults[i] << " and the attacker has rolled " << attDiceResults[i] << "." << std::endl;
							std::cout << "The attacker loses 1 army on " << attackingTerritory.getName() << "." << std::endl;

							attackingTerritory.decreaseArmiesBy(1);
							if (attackingTerritory.getArmies() == 0) {
								// Moving ONE army from defending territory to attacking territory
								// Giving defeated territory to defender
								Territory conquered(attackingTerritory);
								conquered.increaseArmiesBy(1);
								defender.getTerritories().push_back(conquered);

								std::cout << attackingTerritory.getName() << " has been defeated. Defender has moved 1 army to the newly conquered territory." << std::endl;

								// Removing defeated territory from attacker
								const auto pos = std::find(attacker.getTerritories().begin(), attacker.getTerritories().end(), attackingTerritory);
								attacker.getTerritories().erase(pos);
								lostStrongestTerritory = true;
							}
						}
					}

					if (attackingTerritory.getArmies() < 2) {
						std::cout << "Aggressive Player does not have enough armies left on " << strongestTerritory << " to attack." << std::endl;
						break;
					}
					else if (lostStrongestTerritory) {
						std::cout << "Aggressive player has lost its strongest territory, " << strongestTerritory << "." << std::endl;
						break;
					}
				}
				break;
			}
		}

	}
	else {
		std::cout << "No available territory found for Aggressive Player to attack." << std::endl;
	}
}

void AggressivePlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Territory> territories = Game::checkAvailableSourceTerritoriesToFortify(player);

	int maxTargetArmies = 0;
	int maxSourceArmies = 0;
	std::string strongestSource;
	std::string strongestTarget;

	if (territories.size() > 0) {
		for (auto& actual : player.getTerritories()) {
			for (auto c : territories) {
				if (actual.getName() == c.getName()) {
					if (actual.getArmies() > maxTargetArmies) {
						maxTargetArmies = actual.getArmies();
						strongestTarget = actual.getName();
					}
					break;
				}
			}
		}

		std::vector<Territory> adjacentTerritories = Game::checkAvailableTargetTerritoriesToFortify(player, strongestTarget);
		for (auto& actual : player.getTerritories()) {
			for (auto c : adjacentTerritories) {
				if (actual.getName() == c.getName()) {
					if (actual.getArmies() > maxSourceArmies) {
						maxSourceArmies = actual.getArmies();
						strongestSource = actual.getName();
					}
					break;
				}
			}
		}
		
		// Player cannot move all armies from a territory to another
		maxSourceArmies -= 1;

		if (maxSourceArmies < 1) {
			std::cout << "No available territory found to fortify Aggressive Player's strongest territory, " << strongestTarget << "." << std::endl;
		}
		else {
			for (auto& territory : player.getTerritories()) {
				if (territory.getName() == strongestSource) {
					std::cout << "Aggressive Player has fortified " << strongestTarget << " with " << maxSourceArmies << " armies from " << strongestSource << "." << std::endl;
					territory.decreaseArmiesBy(maxSourceArmies);
					std::cout << territory.getName() << " now has " << territory.getArmies() << " armies." << std::endl;
				}
			}

			for (auto& territory : player.getTerritories()) {
				if (territory.getName() == strongestTarget) {
					territory.increaseArmiesBy(maxSourceArmies);
					std::cout << territory.getName() << " now has " << territory.getArmies() << " armies." << std::endl;
					break;
				}
			}
		}
	}
	else {
		std::cout << "No available territory found for Aggressive Player to fortify." << std::endl;
	}
};
