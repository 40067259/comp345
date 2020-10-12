
#include<vector>
#include<string>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"

using namespace std;

//----------------------------------------Card----------------------------------

Card::Card() {
	type = "Bomb";
}

 Card::Card(string c) {
	type = c;
}

string Card::getType() {
	return type;
}

ostream& operator<<(std::ostream& ostream, const Card& card)
{
	return ostream << "Card is of type: " << card.type;
}


void Card::play(Deck *deck,Hand *hand) {
	vector<Card> *temp = hand->getHand();
	int size = temp->size();
	for (int i = size - 1; i >= 0; i--) {
		Card *current = &(temp->at(i));
		cout << "The card is played and " << *current << endl;
		vector<Card>* loss = hand->getHand();
		vector<Card>* obtain = deck->getAvailableCards();
		loss->pop_back();
		deck->insertCard(*current);
	}
	/*
	for (vector<Card>::iterator it = temp->begin(); it != temp->end(); it++) {
		cout << "The card is played and " << *it << endl;
		vector<Card> *loss = hand->getHand();
		vector<Card> *obtain = deck->getAvailableCards();
		if(it != temp->begin())
		loss->erase(it--);
		loss->erase(it);
		int index = -1;
		if (it->type == "Spy") index = 0;
		else if (it->type == "Bomb") index = 1;
		else if (it->type == "Reinforcement") index = 2;
		else if (it->type == "Blockade") index = 3;
		else if (it->type == "Airlift") index = 4;
		else if (it->type == "Diplomacy") index = 5;
		obtain->insert(obtain->begin() + index, *it);
	}
	temp->clear();*/
		
}
