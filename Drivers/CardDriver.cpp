#include "Warzone/Deck.h"
#include "Warzone/Card.h"
#include "Warzone/Map.h"
#include "Warzone/MapLoader.h"
#include <iostream>
#include <sstream>

namespace {
	std::vector<int> split(const std::string &input, char delim) {
		std::stringstream ss(input);
		std::string segment;
		std::vector<int> contents;
		while (std::getline(ss, segment, delim)) {
			contents.push_back(std::stoi(segment));
		}
		return contents;
	}
}

int main() {
	Map map = MapLoader::loadMap("World.map");

	Deck deck;
	deck.loadDeck(map.getTerritories());

	std::cout << "The deck contains " << deck.nCards() << " cards which matches the " << map.getTerritories().size() << " countries!" << std::endl;
	std::cout << std::endl;

	Player player;
	int nInfantry = 0, nArtillery = 0, nCavalry = 0;
	std::cout << "Player will now draw seven cards." << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < 7; ++i) {
		Card card = deck.draw(player);

		if (card.getCardType() == INFANTRY) ++nInfantry;
		else if (card.getCardType() == ARTILLERY) ++nArtillery;
		else if (card.getCardType() == CAVALRY) ++nCavalry;
	}

	std::cout << "Here are your cards: \n";
	for (int i = 0; i < player.getHand().getCards().size(); ++i) {
		Card card = player.getHand().getCards()[i];
		std::cout << i << ": " << card.getCardTypeAsString() << " in " << card.getTerritory().getName() << std::endl;
	}

	std::string input;
	std::cout << std::endl;
	std::cout << "Enter the cards you want to exchange by entering 3 indices as a comma separated list: ";
	std::cin >> input;
	auto indices = split(input, ',');

	Card card0 = player.getHand().getCards()[indices[0]];
	Card card1 = player.getHand().getCards()[indices[1]];
	Card card2 = player.getHand().getCards()[indices[2]];

	int numExchanged = player.getHand().exchange(card0, card1, card2);
	if (numExchanged > 0) {
		std::cout << "You exchanged cards for " << numExchanged << " soldiers.\n";
	}
	else {
		std::cout << "You have attempted to exchange an invalid set of cards.\n";
	}

	std::cout << "\nDrawing the remaining cards...\n";

	while (deck.nCards() > 0) {
		Card card = deck.draw(player);

		if (card.getCardType() == INFANTRY) ++nInfantry;
		else if (card.getCardType() == ARTILLERY) ++nArtillery;
		else if (card.getCardType() == CAVALRY) ++nCavalry;
	}

	std::cout << "Number of infantry: " << nInfantry << std::endl;
	std::cout << "Number of artillery: " << nArtillery << std::endl;
	std::cout << "Number of cavalry: " << nCavalry << std::endl;
	system("pause");
	return 0;
}

