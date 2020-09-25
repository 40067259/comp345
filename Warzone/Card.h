#pragma once

#include "Territory.h"
#include <iostream>
#include <string>

enum CardType {
	INFANTRY, ARTILLERY, CAVALRY
};

class Card {
private:
	Territory territory;
	CardType cardType;

public:
	Card(const Territory& territory, CardType cardType) :
			territory(territory), cardType(cardType) {}

	Territory getTerritory() const;

	void setTerritory(const Territory& territory);

	CardType getCardType() const;

	std::string getCardTypeAsString() const;

	void setCardType(CardType cardType);

	friend std::ostream& operator<<(std::ostream& os, const Card& card) {
		os << "territory: " << card.territory.getName() << ", type: ";
		switch (card.cardType) {
			case INFANTRY:
				os << "infantry";
				break;
			case ARTILLERY:
				os << "artillerty";
				break;
			case CAVALRY:
				os << "cavalry";
				break;
		}
		return os;
	}
};
