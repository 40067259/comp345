#pragma once

#include <vector>
#include "Orders.h"
class Orders;//why I need this to avoid errors????
class OrdersList
{
public:
	OrdersList();
	~OrdersList();
	int size() const;
	std::vector<Orders*> getOrders() { return listOfOrders; }
	void addOrders(Orders* newOrder);//if no add class Orders, errors
	void move(int orderNum);
	void deleteOrder(int orderNum);
	void printOrders();

private:
	std::vector<Orders*> listOfOrders;//if no class Orders, errors

};

