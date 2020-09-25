#include "Warzone/DiceFacility.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
	const int numOfDice = 3;
	int numOfDiceToRoll;

	cout << "Creating " << numOfDice << " dice..." << endl;	
	DiceFacility diceFacility;
	cout << numOfDice << " dice have been created." << endl;

	int reroll;

	do {
		cout << "How many dice would you like to roll? (Enter a number from 1 to 3): ";
		cin >> numOfDiceToRoll;

		cout << endl << "Rolling dice..." << endl;
		auto results = diceFacility.rollDice(numOfDiceToRoll);
		cout << "Dice have been rolled." << endl;

		for (int i = 0; i < results.size(); i++) {
			cout << "Dice " << i + 1 << ": " << results.at(i) << endl;
		}

		cout << endl << "Would you like to roll again? (Enter 0 for NO): ";
		cin >> reroll;
	} while (reroll);

	cout << endl;
	cout << "Here are the results of your " << numOfDice << " dice rolls:" << endl;
	
	for (int i = 0; i < numOfDice; i++) {
		auto diceStats = diceFacility.getDiceStats(i + 1);

		cout << "Stats for dice " << i + 1 << ":" << endl;
		for (int j = 0; j < 6; j++) {
			cout << "Percentage of value " << j + 1 << " rolled up to now: " << diceStats[j] * 100 << "%" << endl;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}