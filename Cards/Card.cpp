
#include<vector>
#include<string>
#include<cstdlib>
#include<iostream>
#include<map>
#include "Hand.h"
#include"Card.h"
#include"Deck.h"

using namespace std;


Card::Card() {
	type = "Bomb";
}

 Card::Card(string c) {
	type = c;
}

string Card::getType() {
	return type;
}

ostream& operator<<(ostream& ostream, const Card& card)
{
	return ostream << "Card is of type: " << card.type;
}


void Card::play(Deck *deck,Hand *hand) {
	vector<Card> *temp = hand->getHand();// get hand pointer to manage hand vector
	int size = temp->size(); // obtain the size to traverse the vector
	for (int i = size - 1; i >= 0; i--) {// back to front so that to pop-back
		Card *current = &(temp->at(i)); //obtain current pointer
		cout << "A card is played and " << *current << endl;// display the shown card
		vector<Card>* loss = hand->getHand();// obtain hand
		vector<Card>* obtain = deck->getAvailableCards();// obtain deck cards
		deck->insertCard(temp->at(i));//deck pile gets one card
		loss->pop_back();//hand loses one card
		
	}
	
		
}
