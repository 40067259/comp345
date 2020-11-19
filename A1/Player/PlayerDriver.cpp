
#include <iostream>
#include <vector>
#include "Territory.h"
#include "Continent.h"
#include "Player.h"
#include "Orders.h"
#include "OrdersList.h"



int main() {
    
    int orderNumber;
    
    //Creating some territories to test methods
    Continent asia("Asia",2);
    Territory *india = new Territory("India", asia, 5, 1);
    Territory *pakistan = new Territory("Pakistan", asia, 4, 2);
    Territory *bangladesh = new Territory("Bangladesh", asia, 2, 3);
    Territory *sriLanka = new Territory("Sri-Lanka", asia, 2, 4);
    Territory *iran = new Territory("Iran", asia, 3, 5);
    
    
   
    
    //SETTING TERRITORIES
    std::vector<Territory*> territories;
    territories.push_back(india);
    territories.push_back(pakistan);
    
    //SETTING CARDS
    Card *c1 = new Card("Bomb");
    Card *c2 = new Card("Airlift");
    vector<Card *> cards;
    cards.push_back(c1);
    cards.push_back(c2);
    Hand *hand = new Hand();
    for (Card *card : cards)
        hand->add(*card);

    
    //SETTING ORDERS
    Deploy *deploy = new Deploy;
    Advance *advance = new Advance;
    vector<Orders*> orders;
    orders.push_back(deploy);
    orders.push_back(advance);
    OrdersList *ordersList = new OrdersList();
    for (Orders *order : orders)
        ordersList->addOrders(order);
    
    
    
    
    //Initializing Player constructor (player owns 2 territories in this case)
    Player player1("Eric", territories, hand, ordersList);
    
    //Pushing arbitrary territories to attack (as per A1 instructions)
    player1.arbitraryTerritoriesToAttack.push_back(sriLanka);
    player1.arbitraryTerritoriesToAttack.push_back(bangladesh);
    player1.arbitraryTerritoriesToAttack.push_back(iran);
    
    
    //Testing .issueOrder() method
    for(int i=0; ; i++) {
    std::cout<< "\n\nWhat types of orders do you want to send?\n";
    std::cout<< "Enter 1 for 'deploy'\n";
    std::cout<< "Enter 2 for 'advance'\n";
    std::cout<< "Enter 3 for 'bomb'\n";
    std::cout<< "Enter 4 for 'blockade'\n";
    std::cout<< "Enter 5 for 'airlift'\n";
    std::cout<< "Enter 6 for 'negotiate'\n";
    std::cout<< "ENTER 0 TO EXIT\n";
    std::cout<< ">>";
    std::cin >> orderNumber;
        if(orderNumber==0){
            break;
        }
    player1.issueOrder(orderNumber);
    }
    
    
    //print all of the orders that the player has issues
    //(Testing if the players are succesfully added into the orderList vector)
    player1.printPlayerOrders();
    
    
    return 0;
}




//IGNORE THIS FOR ASSIGNEMENT 1
//    myMap.addContinent("Asia", 2);
//    myMap.addTerritory("India", "Asia", 5, 21);
//    myMap.addTerritory("Pakistan", "Asia", 4, 22);
//    myMap.addTerritory("Sri-Lanka", "Asia", 2, 23);
//    myMap.addTerritory("Iran", "Asia", 6, 24);
//
//    myMap.addEdge("India", *myMap.getTerritory("Pakistan"));
//    myMap.addEdge("India", *myMap.getTerritory("Sri-Lanka"));
//    myMap.addEdge("Pakistan", *myMap.getTerritory("India"));
//    myMap.addEdge("Pakistan", *myMap.getTerritory("Iran"));
//    myMap.addEdge("Sri-Lanka", *myMap.getTerritory("India"));
//   
