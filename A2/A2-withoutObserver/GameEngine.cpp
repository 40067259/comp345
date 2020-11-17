#include "GameEngine.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;



GameEngine::GameEngine(){
}


//method that starts the game
void GameEngine::GameStart(){
    cout<< "======================================="<<endl;
    cout<< "          LET'S PLAY RISK              "<<endl;
    cout<< "======================================="<<endl;
    
    //Step 1: Select the map
    mapSelection();
    
    //Step 2: Select the amount of players
    playerSelection();
}



//TODO: CHECK HOW TO REJECT A MAP BASED ON THE FACT IF ITS A CONNECTED GRAPH OR NOT
void GameEngine::mapSelection(){
    int selectedMap;
        cout<< "Let's select a map: (1)USA (2)Canada (3)Europe" <<endl;
        cout<< "Enter an integer 1, 2, or 3"<<endl;
        cin >> selectedMap;
    while(selectedMap !=  1 || selectedMap != 2 || selectedMap != 3) {
        cout<< "You have made an invalid selection. Please choose from one of 3 options."<<endl;
        cin >> selectedMap;
    }
    
    MapLoader *mapLoader = new MapLoader();
    switch(selectedMap) {
        case 1:
            mapLoader->loadMap("us.map");
            break;
        case 2:
            mapLoader->loadMap("canada.map");
            break;
        case 3:
            mapLoader->loadMap("europe.map");
            break;
    }
}

void GameEngine::playerSelection(){
    int numberOfPlayersSelected;
    cout<<"How many players will play? Choose between 2 to 5.";
    cin >> numberOfPlayersSelected;
    if (numberOfPlayersSelected < 2 || numberOfPlayersSelected >5){
        cout<<"Invalid. Select between 2 to 5";
        cin >> numberOfPlayersSelected;
    }
    
    numberOfPlayers = numberOfPlayersSelected;
    
    for(int i=0; i<numberOfPlayers; i++) {
        string name;
        cout<<"Enter the name of player "<< i+1 <<endl;
        cin >> name;
        Player *player = new Player(name);
        playersVector.push_back(player);
    }
    
}



//==========PART 3: MAIN GAME LOOP==========//
void GameEngine::mainGameLoop() {
    reinforcementPhase();
    issuingOrderPhase();
    ordersExectionPhase();
}


//PART 3 - ReinforcementPhase
void GameEngine::reinforcementPhase(){
    //For each player playing the game, give them armies
    for(Player *p : playersVector) {
        int minimumArmy = 3; //minimum amount of armies
        int territorialArmies= 0; //armies depending on the amount of territories owned
        int bonusArmy = 0; //bonus army
        int totalArmy = 0; // total army, with everything added together
       
        
        
        //-----Condition 1:If player owns more than 3 territories, give them army-----//
        int territoriesowned  = p->getTerritories().size(); //territories owned
            if(territoriesowned>3) {
                territorialArmies = territoriesowned/3;
            }
            
        //-----Condition 2: If player owns all territories in a continent, give bonus armies-----//
        unordered_map<string, Continent> tableOfContinents =  map->getContinents();
        for(auto &continent : tableOfContinents){
            if(continent.second.owner(p) == true){
                bonusArmy = continent.second.getNativeArmy();
            };
        }
        
        totalArmy = minimumArmy + territorialArmies + bonusArmy + totalArmy;
        
        p->addReinforcements(totalArmy);
        
    }
}
