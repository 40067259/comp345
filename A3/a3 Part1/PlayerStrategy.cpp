#include"PlayerStrategy.h"
using namespace std;
PlayerStrategy::PlayerStrategy() {
	
}

PlayerStrategy::~PlayerStrategy(){

}
//----------------------------------------Human----------------------------
HumanPlayerStrategy::HumanPlayerStrategy():PlayerStrategy() {
}

HumanPlayerStrategy::~HumanPlayerStrategy(){
	PlayerStrategy::~PlayerStrategy();
}

vector<Territory*>* HumanPlayerStrategy::toDefend(Player *p) {
    cout << "You have the following territories, please choose some to add Todefend" << endl;
	for (int i = 0; i < p->getTerritories().size(); i++) {
		cout << "index: " + i << " is " << p->getTerritories().at(i)->getName() << endl;
		cout << "You want to add this territory to defend list? 1 means yes, 2 means no:----> ";
		int ans = 0;
		cin >> ans;
		if(ans == 1)
		p->getTodefend()->push_back(p->getTerritories().at(i));
	}
	return p->getTodefend();
}
vector<Territory*>* HumanPlayerStrategy::toAttack(Player* p, Map* map) {
    cout << "You have the following hostile territories, please choose some to add ToAttack" << endl;
    for (set<Territory*>::iterator it = map->getTerriSet()->begin(); it != map->getTerriSet()->end(); it++)
    {
        Territory* temp = *it;
       
        string name = temp->getName();
        if (p->findTerritory(name) == nullptr) {
            cout << name << endl;
            cout << "Want to add to attack list? 1 means add, 0 means no-----> ";
            int num = 0;
            cin >> num;
            if (num == 1) p->getToAttack()->push_back(temp);
        } 
    }
   
	return p->getToAttack();
}

void HumanPlayerStrategy::issueOrder(Player* p) {
	cout << "Please issue some order: (1)Deploy (2)Advance (3)Bobm (4)Blockade (5)Airlift (6)Negotiate" << endl;
	int order = 1;
	cin >> order;
    switch (order) {
    case 1: {
        cout << "Your current total armies is: " << p->getArmies() << endl;
        p->printToDefend();
        cout << "Please input your number of armies and territory name" << endl;
        int number = 0; std::string name = "User";
        cin >> number >> name;
        Deploy* deploy = new Deploy(p, number, name);
        deploy->execute(p->getMap(),p->getDeck());
        //_orderList->addOrders(deploy);
        std::cout << "Troops deployed!\n";
        break;
    }

    case 2: {
        p->printToAttack();
        p->printToDefend();
        p->printPlayerTerritories();
        cout << "Please type number, source, and destination" << endl;
        int number = 0; std::string sourceName = "sourceTer", targetName = "targetTer";
        cin >> number >> sourceName >> targetName;
        Advance* advance = new Advance(p, number, sourceName, targetName);
        advance->execute(p->getMap(), p->getDeck());
        //_orderList->addOrders(advance);
        std::cout << "Troops advanced!\n";
        break;
    }

    case 3: {
        p->printToAttack();
        cout << "Please input a territory to bomb" << endl;
        std::string target = "Japan";
        cin >> target;
        Bomb* bomb = new Bomb(p, target);
        bomb->execute(p->getMap(), p->getDeck());
       // _orderList->addOrders(bomb);
        std::cout << "Bombed!\n";
        break;
    }


    case 4: {
        p->printToDefend();
        cout << "Please input a territory to blockade" << endl;
        std::string target = "Japan";
        cin >> target;
        Blockade* blockade = new Blockade(p, target);
        blockade->execute(p->getMap(), p->getDeck());
       // p->addOrders(blockade);
        std::cout << "Blockade!\n";
        break;
    }

    case 5: {
        cout << "Please choose your source territory, input your number of armies from source territory, and input target territory" << endl;
        int number = 0; std::string sourceName = "sourceTer", targetName = "targetTer";
        cin >> number >> sourceName >> targetName;
        Airlift* airlift = new Airlift(p, number, sourceName, targetName);
        airlift->execute(p->getMap(), p->getDeck());
        //_orderList->addOrders(airlift);
        std::cout << "Calling Airlift!\n";
        break;
    }


    case 6: {
        cout << "please input a player name who you want to negotiate" << endl;
        std::string name = "";
        cin >> name;
        Player* pl = new Player(name);
        Negotiate* negotiate = new Negotiate(p, pl);
        negotiate->execute(p->getMap(), p->getDeck());
        //_orderList->addOrders(negotiate);
        std::cout << "Negotiated!\n";
        break;
    }

    }
	
}

//-------------------------------Aggressive--------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy():PlayerStrategy() {
	
}

AggressivePlayerStrategy::~AggressivePlayerStrategy(){
	PlayerStrategy::~PlayerStrategy();
}

vector<Territory*>* AggressivePlayerStrategy::toDefend(Player* p) {
    cout << "As a aggressivePlayer, my destiny is attack not defend. So I have no Todefendlist" << endl;
    return p->getTodefend();
}
vector<Territory*>* AggressivePlayerStrategy::toAttack(Player* p, Map* map) {
    cout << "As an aggressivePlayer, I will add all Hostile countries Toattack list" << endl;
    for (set<Territory*>::iterator it = map->getTerriSet()->begin(); it != map->getTerriSet()->end(); it++)
    {
        Territory* temp = *it;
        string name = temp->getName();
        if (p->findTerritory(name) == nullptr) {
            p->getToAttack()->push_back(temp);
        }
    }

    return p->getToAttack();
}


void  AggressivePlayerStrategy::issueOrder(Player* p) {
    cout << "I have no order except attack(Advance)" << endl;
    string bigName = "";
    int max = -1;
    for (int i = 0; i < p->getTerritories().size(); i++) {
        Territory* temp = p->getTerritories().at(i);
        if (temp->getArmies() > max) {
            max = temp->getArmies();
            bigName = temp->getName();
        }
    }

    Deploy* deploy = new Deploy(p, p->getArmies(), bigName);
    deploy->execute(p->getMap(), p->getDeck());
    Territory* targetTerr = p->getToAttack()->at(0);
    string targetName = targetTerr->getName();
    Territory* strongest = p->findTerritory(bigName);
    Advance* advance = new Advance(p, strongest->getArmies(), bigName, targetName);
    advance->execute(p->getMap(), p->getDeck());
    
}

//------------------------------Benevolent-----------------------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy():PlayerStrategy() {
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy(){
	PlayerStrategy::~PlayerStrategy();
}

vector<Territory*>* BenevolentPlayerStrategy::toDefend(Player* p) {
    cout << "As a BenevolentPlayer, I take care of all of my territories. So I put all to Todefend list" << endl;
    for (int i = 0; i < p->getTerritories().size(); i++) {
        p->getTodefend()->push_back(p->getTerritories().at(i));
    }
    return p->getTodefend();
}
vector<Territory*>* BenevolentPlayerStrategy::toAttack(Player* p, Map* map) {
    cout << "As a BenevolentPlayer, I will not attack anyone.So I have no ToAttacklist" << endl;
   
    return p->getToAttack();
}

void  BenevolentPlayerStrategy::issueOrder(Player* p) {
    cout << "I have no order except deploy(defend). ";
    string smallName = "";
    int min = 1000000;
    for (int i = 0; i < p->getTerritories().size(); i++) {
        Territory* temp = p->getTerritories().at(i);
        if (temp->getArmies() < min) {
            min = temp->getArmies();
            smallName = temp->getName();
        }
    }
    cout << "My weakest country is " << smallName << " and I have to enforce my weakest country with all enforcement "+p->getArmies()<<endl;
    Deploy* deploy = new Deploy(p, p->getArmies(), smallName);
    deploy->execute(p->getMap(), p->getDeck());
}

//-----------------------------Neutral-------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy():PlayerStrategy() {
}

NeutralPlayerStrategy::~NeutralPlayerStrategy(){
	PlayerStrategy::~PlayerStrategy();
}
vector<Territory*>* NeutralPlayerStrategy::toDefend(Player* p) {
    cout << "As a NeutralPlayerStrategy, I take care of all of my territories. So I put all to Todefend list" << endl;
    return p->getTodefend();
}
vector<Territory*>* NeutralPlayerStrategy::toAttack(Player* p, Map* map) {
    cout << "As a NeutralPlayerStrategy, I will not attack anyone.So I have no ToAttacklist" << endl;

    return p->getToAttack();
}

void  NeutralPlayerStrategy::issueOrder(Player* p) {
    cout << "I am a NeutralPlayerStrategy, I have no order to issue" << endl;
   
}