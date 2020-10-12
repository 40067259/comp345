#include "Deck.h"
#include<vector>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"


Deck::Deck() {
	availableCards = new vector<Card>();
	availableCards->emplace_back("Spy");
	availableCards->emplace_back("Bomb");
	availableCards->emplace_back("Reinforcement");
	availableCards->emplace_back("Blockade");
	availableCards->emplace_back("Airlift");
	availableCards->emplace_back("Diplomacy");
	cout << "Initialize Deck: " << endl;
	for (int i = 0; i < availableCards->size(); i++) {
		cout << availableCards->at(i)<<endl;
	}
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

ostream& operator<<(std::ostream& ostream, const Deck& deck)
{
	std::string cards = "";
	for (int i = 0; i < deck.availableCards->size(); i++)
	{
		cards += deck.availableCards->at(i).getType() + "; ";
	}
	return ostream << "Deck contains cards in the following order: " << cards;
}
vector<Card>* Deck::getAvailableCards() {
	return availableCards;
}

Deck::~Deck()
{
	delete availableCards;// delet the memory
	availableCards = NULL; // set the pointer to null 
}

Card* Deck::draw(Hand* hand) {
	if (availableCards->size() != 0) {
		int randIndex = rand() % getAvailableCards()->size();// get a random int
		cout << "The player starts to draw a card from deck..." << endl;
		Card* card = &(availableCards->at(randIndex));// obtain the card accroding the randomInt
		cout << "The random number is " << randIndex << ", " << *card << endl;
		cout << "This round of draw finished" << endl;
		hand->add(*card);//hand got a card
		availableCards->erase(getAvailableCards()->begin() + randIndex);//deck pile lost a card
		cout << "The deck infomation is : " << *this << endl;// after this draw round, the remaiding cards
		return card;
	}

	else {
		cout << "no more cards available,please try later";
	}

}
//got a card after it was played
void Deck::insertCard(Card& card) {

	availableCards->emplace_back(card);//this deck obtains a card 
	
}
