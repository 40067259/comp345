#include "HumanPlayer.h"
#include "Territory.h"
#include "UserInterface.h"
#include "Game.h"
#include <iostream>
#include <vector>

void HumanPlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	// Get number of armies to use for reinforcement.
	int armiesFromCardExchange = UserInterface::exchangeCards(player);
	int armiesToAdd = armiesFromCardExchange + Game::getArmiesToAdd(player);
	int x = 0;
	while (armiesToAdd > 0) {
		// Select territory to reinforce
		std::cout << "\nYou have " << armiesToAdd << " remaining soldiers to add. ";
		std::cout << "Please select the territory you would like to add soldiers to.\n";
		Territory territory = UserInterface::selectTerritory(player.getTerritories());

		//// Select number of armies to reinforce for the selected territory
		int armies = UserInterface::selectArmiesToReinforce(territory, armiesToAdd);
		for (auto& c : player.getTerritories()) {
			if (c.getName() == territory.getName()) {
				c.increaseArmiesBy(armies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
			}
		}
		armiesToAdd -= armies;
	}
}

void HumanPlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	bool toAttack;

	do {
		toAttack = UserInterface::toAttackOrNot();

		if (toAttack) {
			std::vector<Territory> attackingTerritories = Game::checkAvailableAttackingTerritoriesToAttack(attacker);

			if (attackingTerritories.size() > 0) {
				// Select attacking and defending territories
				Territory attackingTerritory = UserInterface::selectTerritory(attackingTerritories);
				std::vector <Territory> defendingTerritories = Game::checkAvailableDefendingTerritoriesToAttack(attacker, attackingTerritory);
				Territory defendingTerritory = UserInterface::selectAdjacentTerritory(defendingTerritories);
				Player& defender = Game::getOwner(defendingTerritory);

				// Select number of dice to roll
				int nDiceAttacker;
				for (auto& c : attacker.getTerritories()) {
					if (c.getName() == attackingTerritory.getName()) {
						nDiceAttacker = UserInterface::selectAttackerDice(c);
						break;
					}
				}

				int nDiceDefender;
				for (auto& c : defender.getTerritories()) {
					if (c.getName() == defendingTerritory.getName()) {
						nDiceDefender = UserInterface::selectDefenderDice(c);
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
									std::cout << c.getName() << " has been defeated. Attacker must now move armies to the newly conquered territory." << std::endl;

									// Moving armies from attacking territory to defending territory
									// Giving defeated territory to attacker
									int nArmiesToMove = UserInterface::selectArmiesToMove(attackingTerritory);
									c.increaseArmiesBy(nArmiesToMove);
									attacker.getTerritories().push_back(Territory(c));

									// Removing defeated territory from defender
									const auto pos = std::find(defender.getTerritories().begin(), defender.getTerritories().end(), c);
									defender.getTerritories().erase(pos);
								}
								break;
							}
						}
					}
					else {
						// Defenders wins
						std::cout << "The defender has rolled " << defDiceResults[i] << " and the attacker has rolled " << attDiceResults[i] << "." << std::endl;
						std::cout << "The attacker loses 1 army on " << attackingTerritory.getName() << "." << std::endl;

						for (auto& c : attacker.getTerritories()) {
							if (c.getName() == attackingTerritory.getName()) {
								c.decreaseArmiesBy(1);
								if (c.getArmies() == 0) {
									std::cout << attackingTerritory.getName() << " has been defeated. Defender must now move armies to the newly conquered territory." << std::endl;

									// Moving armies from defending territory to attacking territory
									// Giving defeated territory to defender
									int nArmiesToMove = UserInterface::selectArmiesToMove(defendingTerritory);
									c.increaseArmiesBy(nArmiesToMove);
									defender.getTerritories().push_back(Territory(c));

									// Removing defeated territory from attacker
									const auto pos = std::find(attacker.getTerritories().begin(), attacker.getTerritories().end(), c);
									attacker.getTerritories().erase(pos);
								}
								break;
							}
						}
					}
				}
			}
			else {
				std::cout << "No available territory found for Human Player attack." << std::endl;
			}
		}

	} while (toAttack);
}

void HumanPlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Territory> territories = Game::checkAvailableSourceTerritoriesToFortify(player);

	if (territories.size() > 0) {
		// Select source and target territory to move armies to
		Territory source = UserInterface::selectTerritory(territories);
		std::vector<Territory> adjacentTerritories = Game::checkAvailableTargetTerritoriesToFortify(player, source);
		Territory target = UserInterface::selectAdjacentTerritory(adjacentTerritories);
		int nArmies = UserInterface::selectArmiesToMove(source);

		for (auto& c : player.getTerritories()) {
			if (c.getName() == source.getName()) {
				c.decreaseArmiesBy(nArmies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}

		for (auto& c : player.getTerritories()) {
			if (c.getName() == target.getName()) {
				c.increaseArmiesBy(nArmies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}

		std::cout << nArmies << " have been moved from " << source.getName() << " to " << target.getName() << std::endl;
	}
	else {
		std::cout << "No available territory found to fortify." << std::endl;
	}
}
