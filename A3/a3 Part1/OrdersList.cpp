#include <iostream>
#include "OrdersList.h"

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
	 Map* map = new Map();
	 Deck* deck = new Deck();
	for (int i = 0; i < size(); i++)
	{
		Orders* p = listOfOrders.at(i);
		p->printOrder();
		p->execute(map,deck);
		std::cout << std::endl;
	}
	delete map;
	delete deck;
}