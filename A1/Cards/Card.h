#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include"Deck.h"
#include"Hand.h"

//predefine the classes
class Hand;
class Deck;

class Card {
public:
	Card();//no parameter constructor
	Card(const Card& card);//copy constructor
    Card(std::string cardType); //pass a string as a card's type
	std::string getType(); //obtain card's type
	void play(Deck* deck, Hand* hand); // a specific hand(player's) to display the order on the deck
private:
	std::string type; //instance variable
	friend std::ostream& operator<<(std::ostream&, const Card&);//overwrite << operator
};
