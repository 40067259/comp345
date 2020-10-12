#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Card.h"
#include"Hand.h"

using namespace std;

//predefine the classes
class Hand;
class Card;

class Deck {
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();//deconstructor because of its object instace variable
	Card* draw(Hand* hand); // draw a card from deck randomly and add it to a hand
	void insertCard(Card& card);// insert a card to deck pile
	vector<Card>* getAvailableCards();// get instance variable
private:
	vector<Card>* availableCards;
	friend ostream& operator<<(ostream&, const Deck&);//overwrite the operator <<
};
