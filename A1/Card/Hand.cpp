
#include<vector>
#include<cstdlib>
#include<iostream>
#include<map>
#include"Hand.h"


Hand::Hand()
{
	hand = new vector<Card>;
}

//copy constructor
Hand::Hand(const Hand& h)
{
	hand = new vector<Card>();
	for (unsigned int i = 0; i < h.hand->size(); i++)
	{
		hand->emplace(hand->begin() + i, h.hand->at(i).getType()); //Creating a deep copy the vector
	}
}

Hand::~Hand()
{
}

vector<Card>* Hand::getHand() // get cards of deck
{
	return hand;
}

Card* Hand::getACard(std::string name) {
	for (int i = 0; i < hand->size(); i++) {

		if (hand->at(i).getType() == name) {
			Card *c = new Card();
			c = &hand->at(i);
			return c;
		}
	}
	return nullptr;

}

void Hand::setHand(vector<Card>* toSet)// assign a vector to cards of deck
{
	hand = toSet;
}

void Hand::add(Card& card) // add a card to hand
{
	hand->emplace_back(card);
}

ostream& operator<<(ostream& ostream, const Hand& h)// print all cards in deck
{
	std::string cards = "";
	for (unsigned int i = 0; i < h.hand->size(); i++)
	{
		cards += h.hand->at(i).getType() + "; ";
	}
	return ostream << "Hand contains the following cards: " << cards;
}

