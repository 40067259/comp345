#include "Die.h"
#include <time.h>
#include <random>

Die::Die() {
	this->_totalRollCount = 0;
	for (int i = 0; i < 6; i++) {
		this->_occurenceCount[i] = 0;
	}
}

int Die::roll() {
	int randomNum = (rand() % 6) + 1;
	this->_totalRollCount++;
	this->_occurenceCount[randomNum - 1]++;

	return randomNum;
}

double Die::getPercentageOccurence(int value) {
	return (double) this->_occurenceCount[value - 1] / this->_totalRollCount;
}