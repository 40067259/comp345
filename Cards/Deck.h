#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Card.h"
#include"Hand.h"

using namespace std;

class Hand;
class Card;

class Deck {
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	Card* draw(Hand* hand);
	void insertCard(Card& card);
	//void insertCard(Card* card);
	vector<Card>* getAvailableCards();
private:
	vector<Card>* availableCards;
	friend ostream& operator<<(ostream&, const Deck&);
};
