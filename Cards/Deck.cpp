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
	delete availableCards;
	availableCards = NULL;
}

Card* Deck::draw(Hand* hand) {
	if (availableCards->size() != 0) {
		int randIndex = rand() % getAvailableCards()->size();
		cout << "The player starts to draw a card from deck..." << endl;
		Card* card = &(availableCards->at(randIndex));
		cout << "The random number is " << randIndex << ", " << *card << endl;
		cout << "This round of draw finished" << endl;
		hand->add(*card);
	//	cout << "Erased card is :" << *(getAvailableCards()->begin() + randIndex) << endl;
		availableCards->erase(getAvailableCards()->begin() + randIndex);
		cout << "The deck infomation is : " << *this << endl;
		return card;
	}

	else {
		cout << "no more cards available,please try later";
	}

}

/*

void Deck::insertCard(Card& card) {

	if (card.getType() == "Spy") availableCards->insert(availableCards->begin() + 0, card);
	else if (card.getType() == "Bomb") availableCards->insert(availableCards->begin() + 1, card);
	else if (card.getType() == "Reinforcement") availableCards->insert(availableCards->begin() + 2, card);
	else if (card.getType() == "Blockade") availableCards->insert(availableCards->begin() + 3, card);
	else if (card.getType() == "Airlift") availableCards->insert(availableCards->begin() + 4, card);
	else if (card.getType() == "Diplomacy") availableCards->insert(availableCards->begin() + 5, card);

}*/

void Deck::insertCard(Card& card) {
	
	/*if (card->getType() == "Spy") availableCards->insert(availableCards->begin()+ 0,*card);
	else if (card->getType() == "Bomb") availableCards->insert(availableCards->begin() + 1, *card);
	else if (card->getType() == "Reinforcement") availableCards->insert(availableCards->begin() + 2, *card);
	else if (card->getType() == "Blockade") availableCards->insert(availableCards->begin() + 3, *card);
	else if (card->getType() == "Airlift") availableCards->insert(availableCards->begin() + 4, *card);
	else if (card->getType() == "Diplomacy") availableCards->insert(availableCards->begin() + 5, *card);*/
	cout << "Card: " << &card << endl;
	availableCards->push_back(card);
	
}
