#include "Deck.h"
#include "Hand.h"

int Hand::getArmies() {
	return Deck::getNExchanges() * 5;
}

std::vector<Card> Hand::getCards() const {
	return cards;
}

void Hand::add(const Card& card) {
	cards.push_back(card);
}

int Hand::exchange(const Card& card0, const Card& card1, const Card& card2) {
	if (card0.getCardType() == card1.getCardType() &&
	    card1.getCardType() == card2.getCardType()) {
		Deck::incNExchanges();
		int armies = Hand::getArmies();
		return armies;
	}
	else if (card0.getCardType() != card1.getCardType() &&
	         card1.getCardType() != card2.getCardType() &&
	         card0.getCardType() != card2.getCardType()) {
		Deck::incNExchanges();
		int armies = Hand::getArmies();
		return armies;
	}
	return 0;
}
