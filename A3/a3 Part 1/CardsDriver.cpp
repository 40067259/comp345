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

using namespace std;

int main() {
	cout << endl;
	cout << "**************************************A3**********************************" << endl;
	Continent conti("Asia", 12);  // create a continent
	Map* map = new Map();         // a map that all orders share
	Deck* deck = new Deck();      // a winner can draw a card from deck

	map->addContinent("Asia", 1000);// add continent and territories to map
	map->addTerritory("Korea", "Asia", 80, 3);
	map->addTerritory("china", "Asia", 20, 0);
	map->addTerritory("Japan", "Asia", 60, 2);
	map->addTerritory("Malisia", "Asia", 50, 4);
	map->addTerritory("Iran", "Asia", 70, 1);
	map->addTerritory("Vietnam", "Asia", 40, 5);
	map->addTerritory("Singpore","Asia",38,6);
	map->addTerritory("Saudi Arabia","Asia",66,7);
	map->addTerritory("India","Asia",76,8);


	Territory* ter = new Territory("china", conti, 20, 0);//create coresponing territories 
	Territory* ter1 = new Territory("Iran", conti, 70, 1);
	Territory* ter2 = new Territory("Japan", conti, 60, 2);
	Territory* ter3 = new Territory("Korea", conti, 80, 3);
	Territory* ter4 = new Territory("Malisia", conti, 50, 4);
	Territory* ter5 = new Territory("Vietnam", conti, 40, 5);
	Territory* ter6 = new Territory("Singpore", conti, 38, 6);
	Territory* ter7 = new Territory("Saudi Arabia", conti, 66, 7);
	Territory* ter8 = new Territory("India", conti, 76, 8);


	PlayerStrategy* humanstr = new HumanPlayerStrategy();
	Player* ply = new Player("Fred",humanstr,map,deck);// create a player and initialize armies, territories.
	ply->giveNewArmy(100);
	ply->addTerritory(ter);
	ply->addTerritory(ter2);
	ply->addTerritory(ter6);
	map->getTerritory("Japan")->setOwner(ply);
	map->getTerritory("china")->setOwner(ply);
	map->getTerritory("Singpore")->setOwner(ply);


	PlayerStrategy* benestr = new BenevolentPlayerStrategy();
	Player* pl2 = new Player("Simida",benestr,map,deck);//create a player and initialize it
	pl2->giveNewArmy(80);
	pl2->addTerritory(ter3);
	pl2->addTerritory(ter7);
	map->getTerritory("Korea")->setOwner(pl2);
	map->getTerritory("Saudi Arabia")->setOwner(pl2);

	PlayerStrategy* aggresiveStr = new AggressivePlayerStrategy();
	Player* pl3 = new Player("Ali", aggresiveStr, map, deck);//create a player and initialize it
	pl3->giveNewArmy(100);
	map->getTerritory("Iran")->setOwner(pl3);
	map->getTerritory("Malisia")->setOwner(pl3);
	pl3->addTerritory(ter1);
	pl3->addTerritory(ter4);


	PlayerStrategy* neuStr = new NeutralPlayerStrategy();
	Player* pl4 = new Player("Tom",neuStr, map, deck);//create a player and initialize it
	pl4->giveNewArmy(100);
	pl4->addTerritory(ter5);
	pl4->addTerritory(ter8);
	map->getTerritory("Vietnam")->setOwner(pl4);
	map->getTerritory("India")->setOwner(pl4);

	cout << "*******************demo1 humanPlayer todefend list******************" << endl;
	
	ply->printPlayerTerritories();
	ply->toDefend();
	ply->printToDefend();
	cout << endl;
	cout << "*******************demo2 humanPlayer toAttack list******************" << endl;
	ply->toAttack();
	ply->printToAttack();
	cout << endl;
	cout << "***************** demo3 humanPlayer deploy: 40 arimes from china to attack Korea *******************" << endl;
	ply->issueOrder();
	cout << endl;
	cout << "**************** demo4 ply 50 arimes from china to attack Korea **************" << endl;
	ply->issueOrder();
	cout << endl;
	cout << "**************** demo5 ply to  blockade Singpore**************" << endl;
	ply->issueOrder();
	cout << endl;
	cout << "***************** demo6 agrressivePlayer: toDefend *******************" << endl;
	pl3->toDefend();
	pl3->printToDefend();
	cout << endl;
	cout << "***************** demo7 agrressivePlayer: toAttack *******************" << endl;
	pl3->toAttack();
	pl3->printToAttack();
	cout << endl;
	cout << "***************** demo8 agrressivePlayer: issueOrder*******************" << endl;
	pl3->issueOrder();
	cout << endl;

	cout << "***************** demo9 BenevolentPlayerStrategy: toDefend*******************" << endl;
	pl2->toDefend();
	pl2->printToDefend();
	cout << endl;
	cout << "***************** demo10 BenevolentPlayerStrategy: toAttack*******************" << endl;
	pl2->toAttack();
	pl2->printToAttack();
	cout << endl;
	cout << "***************** demo10 BenevolentPlayerStrategy: issueOrder*******************" << endl;
	pl2->issueOrder();
	cout << endl;
	
	cout << "***************** demo12 NeutralPlayerStrategy: toDefend*******************" << endl;
	pl4->toDefend();
	pl4->printToDefend();
	cout << endl;

	cout << "***************** demo13 NeutralPlayerStrategy: toAttack*******************" << endl;
	pl4->toAttack();
	pl4->printToAttack();
	cout << endl;
	cout << "***************** demo14 NeutralPlayerStrategy: issueOrder*******************" << endl;
	pl4->issueOrder();
	cout << endl;
	
	cout << "***************** demo15 NeutralPlayerStrategy: issueOrder*******************" << endl;
	pl4->setStrategy(humanstr);
	cout << endl;

	cout << "***************** demo16 Convert a NeutralPlayerStrategy to humanPlayer : toDefend*******************" << endl;
	pl4->toDefend();
	pl4->printToDefend();
	cout << endl;

	cout << "***************** demo17 Convert a NeutralPlayerStrategy to humanPlayer :: toAttack*******************" << endl;
	pl4->toAttack();
	pl4->printToAttack();
	cout << endl;
	cout << "***************** demo18  Convert a NeutralPlayerStrategy to humanPlayer :: issueOrder*******************" << endl;
	pl4->issueOrder();
	cout << endl;

	cout << "//--------------------------------------memory free------------------------------------" << endl;
	//free the momery
	delete(deck);
	delete(map);
	return 0;
}