#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

using namespace std;

class Card {

public:
	enum cardType {
		Spy, Bomb, Reinforcement, Blockade, Airlift, Diplomacy
	};
	cardType type;
	Card();
	Card(cardType cardType);
	cardType getType();
	void play(Deck &deck,Hand &hand);
};

	
class Deck {
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	Card draw(Hand &hand);
	void insertCard(Card &card);
	vector<Card> getAvailableCards();
private:
	vector<Card> *availableCards;
	int deckSize;
};

class Hand {
public:
	Hand();
	Hand(const Hand& hand);
	~Hand();
	vector<Card>* getHand();
	void setHand(vector<Card>* toSet);
	void add(Card &card);
private:
	vector<Card>* hand;
};