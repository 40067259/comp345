
#include<vector>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"

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

void Hand::add(Card& card)
{
	hand->emplace_back(card); //creates a card in the back of the vector with the type provided
}

ostream& operator<<(ostream& ostream, const Hand& h)
{
	std::string cards = "";
	for (int i = 0; i < h.hand->size(); i++)
	{
		cards += h.hand->at(i).getType() + "; ";
	}
	return ostream << "Hand contains the following cards: " << cards;
}
