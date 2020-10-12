#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include"Card.h"

using namespace std;

class Card;
class Deck;

class Hand {
public:
	Hand();
	Hand(const Hand& hand);
	~Hand();
	vector<Card>* getHand();
	void setHand(vector<Card>* toSet);
	void add(Card& card);
private:
	vector<Card>* hand;
	friend std::ostream& operator<<(ostream&, const Hand&);
};