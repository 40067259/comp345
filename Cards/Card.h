#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Deck.h"
#include"Hand.h"

using namespace std;

class Hand;
class Deck;

class Card {
public:
	/*enum cardType {
		Spy, Bomb, Reinforcement, Blockade, Airlift, Diplomacy
	};
	cardType type;*/
	Card();
    Card(string cardType);
	string getType();
	void play(Deck* deck, Hand* hand);
private:
	string type;
	friend std::ostream& operator<<(std::ostream&, const Card&);
};
