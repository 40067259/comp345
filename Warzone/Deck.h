#pragma once

#include "Card.h"
#include "Player.h"
#include "Territory.h"
#include <vector>

class Deck {
	private:
		std::vector<Card> cards;

		static int nExchanges;

	public:
		Deck() = default;

		Deck(const std::vector<Card>& cards) : cards(cards) {}

		Card draw(Player& player);

		int nCards() const;

		void loadDeck(const std::vector<Territory>& territories);

		static int getNExchanges();

		static void incNExchanges();
};
