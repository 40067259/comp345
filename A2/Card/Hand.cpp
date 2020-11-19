
#include<vector>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"

Hand::Hand()
{
	pile = new std::vector<Card>;
}

//copy constructor
Hand::Hand(const Hand& h)
{
	pile = new std::vector<Card>();
	for (int i = 0; i < h.pile->size(); i++)
	{
		pile->emplace(pile->begin() + i, h.pile->at(i).getType()); //Creating a deep copy the vector
	}
}

Hand::~Hand()
{
	delete this->pile; // free the memory
	pile = NULL; // assign pointer to null
	std::cout << "a Hand is destroyed" << std::endl;
}

Card* Hand::getACard(std::string name) {
	for (int i = 0; i < this->pile->size(); i++) {
		if (pile->at(i).getType() == name) {
			return &pile->at(i);
		}
		return nullptr;
	}
}

std::vector<Card>* Hand::getCards() // get cards of deck
{
	return pile;
}

void Hand::setCards(std::vector<Card>* toSet)// assign a vector to cards of deck
{
	pile = toSet;
}

void Hand::add(Card &card) // add a card to hand
{
	pile->emplace_back(card); 
}
void Hand::setAcard(std::string name) // add a card to hand
{
	Card card(name);
	pile->emplace_back(card);
}

std::ostream& operator<<(std::ostream& ostream, const Hand& h)// print all cards in deck
{
	std::string cards = "";
	for (int i = 0; i < h.pile->size(); i++)
	{
		cards += h.pile->at(i).getType() + "; ";
	}
	return ostream << "Hand contains the following cards: " << cards;
}
