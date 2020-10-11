#pragma once

#include <vector>
#include "Orders.h"

class OrdersList
{
public:

	OrdersList();
	~OrdersList();
	int size() const;
	void addOrders(Orders* newOrder);
	void move(int orderNum);
	void deleteOrder(int orderNum);
	void printOrders();

private:
	std::vector<Orders*> listOfOrders;
	
};
