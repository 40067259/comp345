#pragma once

#include<vector>
#include<iostream>
#include<map>
#include"Hand.h"
#include"Deck.h"
#include"Card.h"
#include"Continent.h"
#include"Map.h"
#include"MapLoader.h"
#include"Orders.h"
#include"OrdersList.h"
#include"Player.h"
#include"Territory.h"


int main() {
	// get a object of deck. with the deck constructor, all types of card are stored to the deck
	Deck *deck = new Deck();
   
	//get the card vector which stores all cards on deck
	std::vector<Card> *cards = deck->getAvailableCards();
	//get cards number and use it to traverse
	int size = cards->size();

	// get a hand object, and no cards in hand
	Hand* hand1 = new Hand();
	std::cout << std::endl;

	//hand draw all cards from deck and store them in the hand
	for (int i = 0; i < size; i++) {
		deck->draw(hand1); // a random card is drawed, and show the remainding cards on deck
		std::cout << "Now the hand info is: ";
		std::cout << *hand1 <<std::endl;// dispaly all cards in hand after draw
		std::cout << std::endl;
	}

	//obtain a card object
	Card* card = new Card();

	// play all cards in hand to deck and deck gets all played cards
	card->play(deck, hand1);

	std::cout << std::endl;
	std::cout << "After play action: " << std::endl;// after played all cards in hand, show the info of hand and deck
	std::cout << "Hand information is: " << *hand1 << std::endl;
	std::cout << "Deck information is: " << *deck << std::endl;
	
	cout << "--------------------------------Depoly Demo--------------------" << endl;
	Player* ply = new Player();
	ply->giveNewArmy(100);

	Deploy* dep = new Deploy(ply,54,"china");
	std::string name = "china";
	Continent conti("Asia",12);
	Territory *ter = new Territory(name, conti,20, 2);
	ply->addTerritory(ter);
	dep->execute();
	OrdersList list;
	list.addOrders(dep);
	//-------------------------Advance----------
	cout << "----------------------------Advance Demo---------------------" << endl;
	Map map;
	map.addContinent("Asia",800);
	map.addTerritory("Korea","Asia",80,3);
	map.addTerritory("china", "Asia", 20, 2);
	map.addTerritory("Japan", "Asia", 60, 1);
	Player* pl2 = new Player("Simida");
	pl2->giveNewArmy(60);
	//attack
	map.getTerritory("Korea")->setOwner(pl2);
	map.getTerritory("Japan")->setOwner(ply);
	//advand--->attack
	Advance* ad = new Advance(ply, 40, "china", "Korea");
	ad->execute(map);
	//move, move armies from one place to another one
	Advance* ad2 = new Advance(ply, 8, "china", "Japan");
	ad2->execute(map);
	//-----------------------Airlift-----------------------
	cout <<"----------------------------Airlift Demo---------------------"<< endl;
	map.addTerritory("Iran", "Asia", 70, 4);
	Player* pl3 = new Player("Ali");
	pl3->giveNewArmy(100);
	map.getTerritory("Iran")->setOwner(pl3);
	pl3->getHand()->setAcard("airlift");
	Territory* ter1 = new Territory("Iran", conti, 70, 4);
	pl3->addTerritory(ter1);
	pl3->issueOrder(5);
	//OrdersList *list = pl3->getOrdersList();
	std::vector<Orders*> orders = pl3->getOrdersList()->getOrders();
	//std::vector<Orders*> orders = list.getOrders();
	for (int i = 0; i < orders.size(); i++) {
		orders.at(i)->execute();
	}
	//Airlift* airlift = new Airlift(pl3, 80, "Iran", "Korea");
	//airlift->execute(map);
	
	//-------------------------------------------------------------------------


	//--------------------------------------memory free------------------------------------











	//free the momery
	delete(dep);
	//delete(ply);  ??? if this uncommoned, ~hand will throw error
	delete(deck);
	delete(card);
	delete(hand1);
	
    
	return 0;
}