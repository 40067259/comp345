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
	cout << endl;
	cout << "**************************************A2**********************************" << endl;

	/*
	//create a continent
	Continent conti("Asia", 12);
	//add continent and territory to map
	Map map;
	map.addContinent("Asia", 800);
	map.addTerritory("Korea", "Asia", 80, 3);
	map.addTerritory("china", "Asia", 20, 0);
	map.addTerritory("Japan", "Asia", 60, 2);
	map.addTerritory("Iran", "Asia", 70, 1);
	map.addTerritory("Malisia", "Asia", 50, 4);
	//create 3 players to play
	Player* ply = new Player("Lee");
	ply->giveNewArmy(100);
	Player* pl2 = new Player("Simida");
	pl2->giveNewArmy(60);
	Player* pl3 = new Player("Ali");
	pl3->giveNewArmy(70);
	Player* pl4 = new Player("Tom");
	pl4->giveNewArmy(100);
	//create 4 territories and related to territories in the map
	Territory* ter = new Territory("china", conti, 20, 0);
	Territory* ter2 = new Territory("Japan", conti, 60, 2);
	Territory* ter3 = new Territory("Korea", conti, 80, 3);
	Territory* ter1 = new Territory("Iran", conti, 70, 1);
	Territory* ter4 = new Territory("Malisia", conti, 50, 4);

	// players connect to territories
	ply->addTerritory(ter);//china
	pl3->addTerritory(ter1);//Iran
	pl3->addTerritory(ter2);//Japan
	pl2->addTerritory(ter3);//Korea
	pl4->addTerritory(ter4);//Malisia
	//

	map.getTerritory("Korea")->setOwner(pl2);
	map.getTerritory("Japan")->setOwner(pl3);
	map.getTerritory("china")->setOwner(ply);
	map.getTerritory("Iran")->setOwner(pl3);
	map.getTerritory("Malisia")->setOwner(pl4);

	*/


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
	map.addTerritory("Malisia", "Asia", 50, 4);
	Player* pl2 = new Player("Simida");
	pl2->giveNewArmy(60);
	//attack
	map.getTerritory("Korea")->setOwner(pl2);
	map.getTerritory("Japan")->setOwner(ply);
	map.getTerritory("china")->setOwner(ply);
	Territory* ter3 = new Territory("china", conti, 20, 2);
	Territory* ter2 = new Territory("Japan", conti, 60, 1);
	ply->addTerritory(ter3);
	
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
	pl3->addTerritory(ter2);
	/*
	pl3->issueOrder(5);
	std::vector<Orders*> orders = pl3->getOrdersList()->getOrders();
	for (int i = 0; i < orders.size(); i++) {
		orders.at(i)->execute();
	}*/
	Airlift* airlift = new Airlift(pl3, 80, "Iran", "Korea");
	airlift->execute(map);
	
	//---------------------------------Bomb----------------------------------------
	cout<<endl;
	cout << "--------------------------------------bomb---------------------------" << endl;
	//bomb enimy
	pl2->getHand()->setAcard("bomb");
	Bomb* bomb = new Bomb(pl2, "Japan");
	bomb->execute(map);
	//bomb self
	ply->getHand()->setAcard("bomb");
	Bomb* bomb1 = new Bomb(ply, "china");
	bomb1->execute(map);

	cout << "------------------------------Blockade------------------------------------------" << endl;

	Player* pl4 = new Player("Tom");
	pl4->giveNewArmy(100);
	Territory* ter4 = new Territory("Malisia", conti, 50, 4);
	pl4->addTerritory(ter4);
	pl4->getHand()->setAcard("blockade");
	Blockade* bl = new Blockade(pl4,"Malisia");
	bl->execute();


	cout << "//--------------------------------------memory free------------------------------------" << endl;


	//free the momery
	delete(dep);
	//delete(ply);  ??? if this uncommoned, ~hand will throw error
	delete(deck);
	delete(card);
	delete(hand1);
	
    
	return 0;
}