
#include <iostream>
#include <vector>
#include "Territory.h"
#include "Continent.h"
#include "Player.h"



int main() {
    
    int orderNumber;
    Hand hand;
    std::vector<Territory> territories;
    
    
    //Creating some territories to test methods
    Continent asia("Asia",2);
    Territory india("India", asia, 5, 21);
    Territory pakistan("Pakistan", asia, 4, 22);
    Territory bangladesh("Bangladesh", asia, 2, 23);
    Territory sriLanka("Sri-Lanka", asia, 2, 24);
    Territory iran("Iran", asia, 3, 25);
    
    //Putting 2 territories in the vector
    territories.push_back(india);
    territories.push_back(pakistan);
    
    //Initializing Player constructor (player owns 2 territories in this case)
    Player player1(territories, hand);
    
    //Pushing arbitrary territories to attack (as per A1 instructions)
    player1.arbitraryTerritoriesToAttack.push_back(sriLanka);
    player1.arbitraryTerritoriesToAttack.push_back(bangladesh);
    player1.arbitraryTerritoriesToAttack.push_back(iran);
    
    
    //Testing .toDefend() method
    std::cout<< "Player needs to defend: ";
    for (const Territory &t : player1.toDefend())
         std::cout << t.getName() << " ";
    
    //Testing .toAttack() method
    std::cout<< "\nPlayer needs to attack: ";
    for (const Territory &t : player1.toAttack())
         std::cout << t.getName() << " ";
    
    
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
