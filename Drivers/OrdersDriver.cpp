
#include <vector>
#include <string>
#include <iostream>
#include "Risk/OrdersList.h"

using std::cout;
using std::endl;

int main() {
	
		// create a list of orders
		OrdersList olist ;
		Orders* o = new Orders();
		Deploy* d = new Deploy();
		Advance* ad = new Advance();
		Bomb* bo = new Bomb();
		Blockade* bl = new Blockade();
		Airlift* ai = new Airlift();
		Negotiate* n = new Negotiate();
		
		// add orders to order list
		olist.addOrders(o);
		olist.addOrders(d);
		olist.addOrders(ad);
		olist.addOrders(bo);
		olist.addOrders(bl);
		olist.addOrders(ai);
		olist.addOrders(n);
		
		// print the order list
		olist.printOrders();
		cout << endl;
		
		// print the order list after move and delete
		cout <<"==========after move and delete==========="<< endl;
		olist.move(2);
		olist.deleteOrder(1);
		olist.printOrders();
		cout << endl;	
		
		system("pause");
}