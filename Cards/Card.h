#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Deck.h"
#include"Hand.h"

using namespace std;
//predefine the classes
class Hand;
class Deck;

class Card {
public:
	Card();//no parameter constructor
    Card(string cardType); //pass a string as a card's type
	string getType(); //obtain card's type
	void play(Deck* deck, Hand* hand); // a specific hand(player's) to display the order on the deck
private:
	string type; //instance variable
	friend ostream& operator<<(ostream&, const Card&);//overwrite << operator
};
