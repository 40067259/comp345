#pragma once

#include <string>
#include"C:\Users\amadeus\source\repos\part1\part1\Player\Player.h"
#include"C:\Users\amadeus\source\repos\part1\part1\Map\Territory.h"

class Player;
class Territory;

class Orders
{
public:
	Orders();
	Orders(Player* inputPlayer);
	Orders(Player* inputPlayer, int n,Territory* terName);
	~Orders();
	int getNumber() { return number; }
	Player* getPlayer() { return player; }
	//std::string getTerName() { return terName; }
	void setNumber(int number);
	void setPlayer(Player* player);
	//void setTerName(std::string name);
	void setType(std::string type);
	virtual bool validate(); // verifies if the order is valid.
	virtual void execute() = 0; // method that will result in some game action being implemented
	virtual void printOrder();
protected:
	std::string orderType = " none"; //deploy, advance, bomb, blockade, airlift, or negotiate
	Player* player;
	int number;
	Territory* terName;

};

class Deploy : public Orders
{
public:
	Deploy();
	Deploy(Player *player, int number, Territory* terName);
	~Deploy();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Advance : public Orders
{
private:
	Territory* desName;

public:

	Advance();
	Advance(Player* player, int number, Territory* terName, Territory* desName);
	~Advance();
	int fight(int attack, int defend);
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();
	
};
class Airlift : public Orders
{
private:
	Territory* desName;

public:
	Airlift(Player* player, int number, Territory* terName, Territory* desName);
	~Airlift();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};


class Bomb : public Orders
{

public:
	Bomb(Player* player, Territory* terName);
	~Bomb();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Blockade : public Orders
{
private:
	std::string orderType = "blockade"; // airlift, or negotiate

public:

	Blockade(Player* player, Territory* terName);
	~Blockade();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};


class Negotiate : public Orders
{
private:
	std::string orderType = "negotiate";
	Player* p2;
public:

	Negotiate(Player* player1, Player* player2 );
	~Negotiate();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};