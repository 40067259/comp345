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

	// [Sort the List with priorities]
	// 1) Deploy
	// 2) Airlift
	// 3) Blockade
	// 4) Others

	int count = 0;

	// Put Blockade to the front
	for (Orders* o : listOfOrders)
	{
		if ((o->orderType).compare("Blockade"))
		{
			listOfOrders.erase((listOfOrders.begin())+count); //so it will remove the elements at position 0 + count
			//add it to the front of the vector
			listOfOrders.push_back(o);
			std::cout << "Moved Blockade";
		}
		count++;
	}

	//After that, put Airlift to the front
	for (Orders* o : listOfOrders)
	{
		if ((o->orderType).compare("Airlift"))
		{
			listOfOrders.erase((listOfOrders.begin()) + count); //so it will remove the elements at position 0 + count
			//add it to the front of the vector
			listOfOrders.push_back(o);
			std::cout << "Moved Airlift";
		}
		count++;
	}

	// Then, put Deploy to the front
	for (Orders* o : listOfOrders)
	{ 
		if ((o->orderType).compare("Deploy"))
		{
			listOfOrders.erase((listOfOrders.begin()) + count); //so it will remove the elements at position 0 + count
			//add it to the front of the vector
			listOfOrders.push_back(o);
			std::cout << "Moved Deploy";
		}
		count++;
	}
	// [Sort the List with priorities]
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

std::vector<Orders*> OrdersList::getListOfOrders()
{
	return listOfOrders;
}
