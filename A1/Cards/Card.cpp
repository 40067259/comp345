#include<vector>
#include<string>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"


Card::Card() {
	type = "Bomb";
}

Card::Card(std::string c) {
	type = c;
}

Card::Card(const Card& card) {
	type = card.type;
}

std::string Card::getType() {
	return type;
}

std::ostream& operator<<(std::ostream& ostream, const Card& card)
{
	return ostream << "Card is of type: " << card.type;
}


void Card::play(Deck* deck, Hand* hand) {
	std::vector<Card>* temp = hand->getHand();// get hand pointer to manage hand vector
	int size = temp->size(); // obtain the size to traverse the vector
	for (int i = size - 1; i >= 0; i--) {// back to front so that to pop-back
		Card* current = &(temp->at(i)); //obtain current pointer
		std::cout << "A card is played and " << *current << std::endl;// display the shown card
		std::vector<Card>* loss = hand->getHand();// obtain hand
		std::vector<Card>* obtain = deck->getAvailableCards();// obtain deck cards
		deck->insertCard(temp->at(i));//deck pile gets one card
		loss->pop_back();//hand loses one card

	}


}
