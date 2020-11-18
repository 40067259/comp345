#pragma once

#include <string>
#include"Player.h"
#include"Map.h"

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
	virtual void execute(); // method that will result in some game action being implemented
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
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Advance : public Orders
{
private:
	std::string desName;

public:

	Advance();
	Advance(Player* player, int number, std::string terName,std::string desName);
	~Advance();
	int fight(int attack, int defend);
	bool validate(); // verifies if the order is valid.
	void execute(Map map); // method that will result in some game action being implemented
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
	void execute(Map map); // method that will result in some game action being implemented
	void printOrder();

};


class Bomb : public Orders
{

public:
	Bomb(Player* player,std::string terName);
	~Bomb();
	bool validate(); // verifies if the order is valid.
	void execute(Map map); // method that will result in some game action being implemented
	void printOrder();

};

class Blockade : public Orders
{
private:
	std::string orderType = "blockade"; // airlift, or negotiate

public:

	Blockade();
	~Blockade();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};


class Negotiate : public Orders
{
private:
	std::string orderType = "negotiate";

public:

	Negotiate();
	~Negotiate();
	bool validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};