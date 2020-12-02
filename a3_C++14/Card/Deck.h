#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Card.h"
#include"Hand.h"

//predefine the classes
class Hand;
class Card;

class Deck {
public:
	Deck(int numberOfPlayers);
	Deck(const Deck& deck);
	~Deck();//deconstructor because of its object instace variable
	Card* draw(Hand* hand); // draw a card from deck randomly and add it to a hand
	void insertCard(Card& card);// insert a card to deck pile
	std::vector<Card>* getAvailableCards();// get instance variable
private:
	std::vector<Card>* availableCards;
	friend std::ostream& operator<<(std::ostream&, const Deck&);//overwrite the operator <<
};
//
