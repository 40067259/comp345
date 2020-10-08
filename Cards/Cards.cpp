#include "Cards.h"
#include<vector>
#include<cstdlib>
#include<iostream>
#include<map>

using namespace std;

Card::Card(){}

Card::Card(cardType c) {
	this->type = c;
}

Card::cardType Card::getType() {
	return this->type;
}

Deck::Deck(){
	availableCards = new vector<Card>();
	availableCards->emplace_back("Spy");
	availableCards->emplace_back("Bomb");
	availableCards->emplace_back("Reinforcement");
	availableCards->emplace_back("Blockade");
	availableCards->emplace_back("Airlift");
	availableCards->emplace_back("Diplomacy");
}

Deck::Deck(const Deck& deck)
{
	availableCards = new vector<Card>();
	for (int i = 0; i < deck.availableCards->size(); i++)
	{
		//deep copy
	availableCards->emplace(availableCards->begin() + i, deck.availableCards->at(i).getType()); 
	}
}
vector<Card> Deck::getAvailableCards() {
	return *availableCards;
}
Deck::~Deck()
{
	delete availableCards;
	availableCards = NULL;
}

 Card Deck::draw(Player &player) {
	 if (getAvailableCards().size() != 0) {
		 int randIndex = rand() % getAvailableCards().size();
		 Card card = getAvailableCards()[randIndex];
		 player.getHand().add(card);
		 availableCards->erase(getAvailableCards().begin() + randIndex);
		 return card;
	 }
	 else cout << "no more cards available,please try later";
}

 void Deck::insertCard(Card &card) {
	 if (card.getType() == Card::Spy) getAvailableCards()[0] = card;
	 else if (card.getType() == Card::Bomb) getAvailableCards()[1] = card;
	 else if (card.getType() == Card::Reinforcement) getAvailableCards()[2] = card;
	 else if (card.getType() == Card::Blockade) getAvailableCards()[3] = card;
	 else if (card.getType() == Card::Airlift) getAvailableCards()[4] = card;
	 else if (card.getType() == Card::Diplomacy) getAvailableCards()[5] = card;

 }

 Hand::Hand()
 {
	 hand = new std::vector<Card>;
 }

 Hand::Hand(const Hand& h)
 {
	 hand = new vector<Card>();
	 for (int i = 0; i < h.hand->size(); i++)
	 {
		 hand->emplace(hand->begin() + i, h.hand->at(i).getType()); //Creating a deep copy the vector
	 }
 }

 Hand::~Hand()
 {
	 delete hand;
	 hand = NULL;
 }

 std::vector<Card>* Hand::getHand()
 {
	 return hand;
 }

 void Hand::setHand(vector<Card>* toSet)
 {
	 hand = toSet;
 }

 void Hand::add(Card &card)
 {
	 hand->emplace_back(card); //creates a card in the back of the vector with the type provided
 }

