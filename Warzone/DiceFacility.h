#pragma once
#include "Die.h"
#include <vector>
#include <array>

class DiceFacility {
	private:
		std::array<Die, 3> _dice;

	public:
		DiceFacility();
		std::array<Die, 3> getDice() const;
		std::vector<int> rollDice(int numOfDice);
		std::array<double, 6> getDiceStats(int diceNum);
};