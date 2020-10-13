#pragma once

#include<vector>
#include<iostream>
#include<map>
#include"Hand.h"
#include"Deck.h"
#include "Card.h"


int main() {
	// get a object of deck. with the deck constructor, all types of card are stored to the deck
	Deck *deck = new Deck();
   
	//get the card vector which stores all cards on deck
	std::vector<Card> *cards = deck->getAvailableCards();
	//get cards number and use it to traverse
	int size = cards->size();

	// get a hand object, and no cards in hand
	Hand* hand = new Hand();
	std::cout << std::endl;

	//hand draw all cards from deck and store them in the hand
	for (int i = 0; i < size; i++) {
		deck->draw(hand); // a random card is drawed, and show the remainding cards on deck
		std::cout << "Now the hand info is: ";
		std::cout << *hand <<std::endl;// dispaly all cards in hand after draw
		std::cout << std::endl;
	}

	//obtain a card object
	Card* card = new Card();

	// play all cards in hand to deck and deck gets all played cards
	card->play(deck, hand);

	std::cout << std::endl;
	std::cout << "After play action: " << std::endl;// after played all cards in hand, show the info of hand and deck
	std::cout << "Hand information is: " << *hand << std::endl;
	std::cout << "Deck information is: " << *deck << std::endl;

	//free the momery
	delete(deck);
	delete(card);
	delete(hand);
   
	return 0;
}