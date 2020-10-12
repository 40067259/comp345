#pragma once

#include<vector>
#include<iostream>
#include<map>
#include"Hand.h"
#include"Deck.h"
#include "Card.h"

using namespace std;

int main() {
	Deck *deck = new Deck();

	vector<Card> *cards = deck->getAvailableCards();
	int size = cards->size();
	Hand* hand = new Hand();
	//cout << "Cards size:"<<cards->size() << endl;
	cout << endl;
	for (int i = 0; i < size; i++) {
		deck->draw(hand);
		cout << "Now the hand info is: ";
		cout << *hand << endl;
		cout << endl;
	}

	Card* card = new Card();

	card->play(deck, hand);

	cout << "After play action: " << endl;
	cout << "Hand information is: " << *hand << endl;
	cout << "Deck information is: " << *deck << endl;

	
   

}