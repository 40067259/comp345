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


int main() {/*
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
	std::cout << "Deck information is: " << *deck << std::endl;*/
	cout << endl;
	cout << "**************************************A2**********************************" << endl;
	Continent conti("Asia", 12);  // create a continent
	Map* map = new Map();         // a map that all orders share
	Deck* deck = new Deck();      // a winner can draw a card from deck

	map->addContinent("Asia", 800);// add continent and territories to map
	map->addTerritory("Korea", "Asia", 80, 3);
	map->addTerritory("china", "Asia", 20, 2);
	map->addTerritory("Japan", "Asia", 60, 1);
	map->addTerritory("Malisia", "Asia", 50, 5);
	map->addTerritory("Iran", "Asia", 70, 4);
	map->addTerritory("Vietnam", "Asia", 40, 6);


	Territory* ter = new Territory("china", conti, 20, 0);//create coresponing territories 
	Territory* ter1 = new Territory("Iran", conti, 70, 1);
	Territory* ter2 = new Territory("Japan", conti, 60, 2);
	Territory* ter3 = new Territory("Korea", conti, 80, 3);
	Territory* ter4 = new Territory("Malisia", conti, 50, 4);
	Territory* ter5 = new Territory("Vietnam", conti, 40, 6);

	Player* ply = new Player();// create a player and initialize armies, territories.
	ply->giveNewArmy(100);
	ply->addTerritory(ter);
	ply->addTerritory(ter3);
	map->getTerritory("Japan")->setOwner(ply);
	map->getTerritory("china")->setOwner(ply);

	Player* pl2 = new Player("Simida");//create a player and initialize it
	pl2->giveNewArmy(60);
	pl2->addTerritory(ter3);
	map->getTerritory("Korea")->setOwner(pl2);
	
	
	Player* pl3 = new Player("Ali");//create a player and initialize it
	pl3->giveNewArmy(100);
	map->getTerritory("Iran")->setOwner(pl3);
	pl3->addTerritory(ter1);
	pl3->addTerritory(ter2);
	
	
	Player* pl4 = new Player("Tom");//create a player and initialize it
	pl4->giveNewArmy(100);
	pl4->addTerritory(ter4);
	
	Player* pl5 = new Player("Huang");//create a player and initialize it
	pl5->giveNewArmy(60);
	pl4->addTerritory(ter5);
	map->getTerritory("Vietnam")->setOwner(pl5);
	
	cout << "--------------------------------Depoly Demo--------------------" << endl;

	   Deploy* dep = new Deploy(ply,54,"china");//player employ 54 armies to china
	   dep->execute(map,deck);
	
	cout << "----------------------------Advance Demo---------------------" << endl;
	//advand--->attack
	Advance* ad = new Advance(ply, 40, "china", "Korea");//ply 40 armies from china to atack korea
	ad->execute(map,deck);
	//move, move armies from one place to another one
	Advance* ad2 = new Advance(ply, 8, "china", "Japan");//beacause ply own china and Japan, no attack
	ad2->execute(map,deck);
	cout <<"----------------------------Airlift Demo---------------------"<< endl;
	pl3->getHand()->setAcard("airlift"); // give pl3 a card and he can issue airlift
	Airlift* airlift = new Airlift(pl3, 60, "Iran", "Korea");// airlift 60 from Iran to korea, attack
	airlift->execute(map,deck);
	cout<<endl;
	cout << "--------------------------------------bomb---------------------------" << endl;
	//bomb enimy
	pl2->getHand()->setAcard("bomb");//give pl2 a bomb card,so he can bomb
	Bomb* bomb = new Bomb(pl2, "Japan");// pl2 bomb Japan, half people die
	bomb->execute(map,deck);
	//bomb self
	ply->getHand()->setAcard("bomb");
	Bomb* bomb1 = new Bomb(ply, "china");// ply try to bomb his own territory, invalid order
	bomb1->execute(map,deck);

	cout << "------------------------------Blockade------------------------------------------" << endl;
	pl4->getHand()->setAcard("blockade");// offer a blockade card, so he can blockade
	Blockade* bl = new Blockade(pl4,"Malisia");// double the armies and transfer ownership to nobody
	bl->execute(map,deck);

	cout << "------------------------------Negotiate------------------------------------------" << endl;
	pl5->getHand()->setAcard("diplomacy");
	Negotiate* ng = new Negotiate(pl5, pl5);
	ng->execute(map,deck);//negotiate himself, invalid

	cout << "//--------------------------------------memory free------------------------------------" << endl;
	//free the momery
	delete(dep);
	delete(deck);
	delete(map);
	return 0;
}