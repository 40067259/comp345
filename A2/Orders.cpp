
#include <iostream>
#include "Orders.h"

using std::cout;
using std::endl;

Orders::Orders(std::string s) {
	orderType = s;
}
// there will be constructor overload, depend on the type of orders
Orders::Orders()
{
}

Orders::~Orders()
{
}
// for now, no need to implement the execute() and validate() 
void Orders::validate() {
	cout << "varifing the order...the order is invalide" << endl;
}
void Orders::execute() {
	Orders::validate();
	cout << "implementing the order... the order is invalide" << endl;
}
void Orders::printOrder() {
	cout << "The order type is " << orderType << endl;
}


// Deploy class function declaration
Deploy::Deploy() {
}
Deploy::~Deploy()
{
}
// for now, no need to implement the execute() and validate() 
void Deploy::validate() {
	cout << "varifing the deploy order..." << endl;
}
void Deploy::execute() {
	Deploy::validate();
	cout << "implementing the deploy order... " << endl;
}
void Deploy::printOrder() {
	cout << "The order type is " << orderType << endl;
}


// Advance class function declaration
Advance::Advance() {
}
Advance::~Advance()
{
}
// for now, no need to implement the execute() and validate() 
void Advance::validate() {
	cout << "varifing the Advance order..." << endl;
}
void Advance::execute() {
	Advance::validate();
	cout << "implementing the Advance order... " << endl;
}
void Advance::printOrder() {
	cout << "The order type is " << orderType << endl;
}


// Bomb class function declaration
Bomb::Bomb() {
}
Bomb::~Bomb()
{
}
// for now, no need to implement the execute() and validate() 
void Bomb::validate() {
	cout << "varifing the Bomb order..." << endl;
}
void Bomb::execute() {
	Bomb::validate();
	cout << "implementing the Bomb order... " << endl;
}
void Bomb::printOrder() {
	cout << "The order type is " << orderType << endl;
}

// Blockade class function declaration
Blockade::Blockade() {
}
Blockade::~Blockade()
{
}
// for now, no need to implement the execute() and validate() 
void Blockade::validate() {
	cout << "varifing the Blockade order..." << endl;
}
void Blockade::execute() {
	Blockade::validate();
	cout << "implementing the Blockade order... " << endl;
}
void Blockade::printOrder() {
	cout << "The order type is " << orderType << endl;
}

// Airlift class function declaration
Airlift::Airlift() {
}
Airlift::~Airlift()
{
}
// for now, no need to implement the execute() and validate() 
void Airlift::validate() {
	cout << "varifing the Airlift order..." << endl;
}
void Airlift::execute() {
	Airlift::validate();
	cout << "implementing the Airlift order... " << endl;
}
void Airlift::printOrder() {
	cout << "The order type is " << orderType << endl;
}


// Negotiate class function declaration
Negotiate::Negotiate() {
}
Negotiate::~Negotiate()
{
}
// for now, no need to implement the execute() and validate() 
void Negotiate::validate() {
	cout << "varifing the Negotiate order..." << endl;
}
void Negotiate::execute() {
	Negotiate::validate();
	cout << "implementing the Negotiate order... " << endl;
}
void Negotiate::printOrder() {
	cout << "The order type is " << orderType << endl;
}


OrdersList::OrdersList()
{
}

OrdersList::~OrdersList()
{
}

int OrdersList::size() const
{
	return listOfOrders.size();
}

void OrdersList::addOrders(Orders* newOrder) {
	listOfOrders.emplace_back(newOrder);
}

// move a certain element to the end of oder list only
void OrdersList::move(int orderNum) {
	Orders* p = listOfOrders.at(orderNum);
	listOfOrders.erase(listOfOrders.begin() + orderNum - 1);
	listOfOrders.push_back(p);
}

void OrdersList::deleteOrder(int orderNum) {
	listOfOrders.erase(listOfOrders.begin() + orderNum - 1);
}

void OrdersList::printOrders() {
	for (int i = 0; i < size(); i++)
	{
		Orders* p = listOfOrders.at(i);
		p->printOrder();
		p->execute();
		std::cout << std::endl;
	}
}