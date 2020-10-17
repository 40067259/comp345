
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

//copy constructor
Hand::Hand(const Hand& h)
{
	hand = new std::vector<Card>();
	for (int i = 0; i < h.hand->size(); i++)
	{
		hand->emplace(hand->begin() + i, h.hand->at(i).getType()); //Creating a deep copy the vector
	}
}

Hand::~Hand()
{
	delete hand; // free the memory
	hand = NULL; // assign pointer to null
}

std::vector<Card>* Hand::getHand() // get cards of deck
{
	return hand;
}

void Hand::setHand(std::vector<Card>* toSet)// assign a vector to cards of deck
{
	hand = toSet;
}

void Hand::add(Card& card) // add a card to hand
{
	hand->emplace_back(card); 
}

std::ostream& operator<<(std::ostream& ostream, const Hand& h)// print all cards in deck
{
	std::string cards = "";
	for (int i = 0; i < h.hand->size(); i++)
	{
		cards += h.hand->at(i).getType() + "; ";
	}
	return ostream << "Hand contains the following cards: " << cards;
}
