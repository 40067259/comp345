#include "Card.h"

Territory Card::getTerritory() const {
	return territory;
}

void Card::setTerritory(const Territory& territory) {
	this->territory = territory;
}

CardType Card::getCardType() const {
	return cardType;
}

std::string Card::getCardTypeAsString() const {
	if (cardType == INFANTRY) return "infantry";
	if (cardType == ARTILLERY) return "artillery";
	if (cardType == CAVALRY) return "cavalry";
}

void Card::setCardType(CardType cardType) {
	this->cardType = cardType;
}
