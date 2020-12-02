#pragma once
#include<iostream>
#include <vector>
#include "..\Map\Territory.h"
#include "..\Orders\OrdersList.h"
#include "..\Orders\Orders.h"
#include "..\Map\Map.h"
#include "..\Card\Card.h"
#include "..\Card\Card.h"
//added
#include "..\Player\PlayerStrategy.h"
#include "..\GameEngine.h"

class Hand;
class Cards;
class OrdersList;
class Orders;
class PlayerStrategy;

class Player {
private:
	
	Hand* _cards;
	OrdersList* _orderList;
	std::string _name;
	int _playerNumber;
	int _armies = 0;
	int reinforcementPool;
	static int numberOfPlayers;

	//added for a3
	PlayerStrategy* playerStrat;
	Map* map;
	//added for a3

public:
	Player();
	Player(std::string name);
	Player(std::string name, std::vector<Territory*> territories, Hand* cards, OrdersList* orderlist);
	~Player();
	std::vector<Territory*> arbitraryTerritoriesToAttack; //TEMPORARY: For the first assignement
	void toDefend();
	void toAttack();
	//std::vector<Territory*> toAttack(/*//===removed the argument===//  Territory* territoryToAttack*/);
	Territory* findTerritory(std::string terName);
	void issueOrder(int orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies);
	void printPlayerOrders();
	//void printPlayerTerritories();
	void giveNewArmy(int num);
	void addTerritory(Territory* terr);
	void addReinforcements(int r);

	std::vector<Territory*> getTerritories();
	Hand* getHand();
	OrdersList* getOrdersList();
	std::string getName();
	int getArmies();
	int getReinforcements();

	//added
	std::vector<Territory*> _territoriesToDefend_priority;
	std::vector<Territory*> _territoriesToAttack_priority;
	//added

	//added for a3
	Player(const Player* p);    // copy constructor
	void setStrategy(std::string strategy);
	void toSkip();
	Map* getMap();
	std::vector<Territory*> _territories;
	//added for a3
	void appendOrder(Orders *newOrder);
};
