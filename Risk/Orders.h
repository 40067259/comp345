#pragma once

#include <string>

class Orders
{
public:
	std::string orderType = " none"; //deploy, advance, bomb, blockade, airlift, or negotiate
	
	Orders();
	Orders(std::string);
	~Orders();
	virtual void validate(); // verifies if the order is valid.
	virtual void execute(); // method that will result in some game action being implemented
	virtual void printOrder();

};

class Deploy : public Orders
{
private:
	std::string orderType = "deploy"; 

public:

	Deploy();
	~Deploy();
	void validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Advance : public Orders
{
private:
	std::string orderType = "advance"; 

public:

	Advance();
	~Advance();
	void validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Bomb : public Orders
{
private:
	std::string orderType = "bomb"; 
public:

	Bomb();
	~Bomb();
	void validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Blockade : public Orders
{
private:
	std::string orderType = "blockade"; // airlift, or negotiate

public:

	Blockade();
	~Blockade();
	void validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};

class Airlift : public Orders
{
private:
	std::string orderType = "airlift"; // negotiate

public:

	Airlift();
	~Airlift();
	void validate(); // verifies if the order is valid.
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
	void validate(); // verifies if the order is valid.
	void execute(); // method that will result in some game action being implemented
	void printOrder();

};