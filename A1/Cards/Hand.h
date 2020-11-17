#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include"Card.h"
#include"Deck.h"

using namespace std;
//predefine the classed
class Cards;
class Deck;

class Hand {
public:
	Hand();
	Hand(const Hand& hand);// a copy constructor
	~Hand(); //deconstructor because of vector instace variable
	vector<Card>* getHand();
	void setHand(vector<Card>* toSet);// set a vector to hand
	void add(Card& card); // add a card to hand
private:
	vector<Card>* hand; // instance varibale to store cards
	friend ostream& operator<<(ostream&, const Hand&);
};
