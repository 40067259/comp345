#pragma once

#include <string>
#include"Player.h"
#include"Map.h"
#include"Deck.h"

class Map;
class Orders
{
public:
	Orders();
	Orders(Player* inputPlayer, int inputNumber, std::string inputName);
	~Orders();
	int getNumber() { return number; }
	Player* getPlayer() { return player; }
	std::string getTerName() { return terName;}
	void setNumber(int number);
	void setPlayer(Player* player);
	void setTerName(std::string name);
	void setType(std::string type);
	virtual bool validate(); // verifies if the order is valid.
	virtual void execute(Map* map, Deck* deck) = 0; // pure virtual to be inheritanced
	virtual void printOrder();
protected:
	std::string orderType = " none"; //deploy, advance, bomb, blockade, airlift, or negotiate
	Player* player;
	int number;
	std::string terName;
};

class Deploy : public Orders
{
public:
	Deploy();
	Deploy(Player *player,int number,std::string terName);
	~Deploy();
	bool validate(); // verifies if the order is valid.
	void execute(Map* map, Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};

class Advance : public Orders
{
private:
	std::string desName; //need an extra variable to know the target territory

public:

	Advance();
	Advance(Player* player, int number, std::string terName,std::string desName);
	~Advance();
	int fight(int attack, int defend);
	bool validate(); // verifies if the order is valid.
	void execute(Map* map,Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};
class Airlift : public Orders
{
private:
	std::string desName;

public:
	Airlift(Player* player, int number, std::string terName, std::string desName);
	~Airlift();
	bool validate(); // verifies if the order is valid.
	void execute(Map* map, Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};


class Bomb : public Orders
{

public:
	Bomb(Player* player,std::string terName);
	~Bomb();
	bool validate(); // verifies if the order is valid.
	void execute(Map *map,Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};

class Blockade : public Orders
{
private:
	
public:
	Blockade(Player* player, std::string terName);
	~Blockade();
	bool validate(); // verifies if the order is valid.
	void execute(Map* map, Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};


class Negotiate : public Orders
{
private:
	Player* targetplayer;
public:
	Negotiate(Player* player,Player* targetPlayer);
	~Negotiate();
	bool validate(); // verifies if the order is valid.
	void execute(Map* map, Deck* deck); // method that will result in some game action being implemented
	void printOrder();

};