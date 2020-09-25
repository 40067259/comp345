#pragma once

class Die {
	private:
		int _totalRollCount;
		int _occurenceCount[6];

	public:
		Die();
		int roll();
		double getPercentageOccurence(int value);
};