#include <iostream>
#include "Orders.h"

using std::cout;
using std::endl;

//---------------------------------Abstract class--------------------------------------------
Orders::Orders() {// default constructor
	this->orderType = "none";
	this->terName = " none";
	this->number = 0;
	this->player = nullptr;
}
Orders::Orders(Player* inputPlayer, int inputNumber, std::string inputName) {// pamameters to initilize data memeber
	orderType = "";
	this->player = inputPlayer;
	this->number = inputNumber;
	this->terName = inputName;
	cout << "An order is created" << endl;
}
// there will be constructor overload, depend on the type of orders


Orders::~Orders()// deconstructor to avoid memory leak
{
	delete this->player;
	player = nullptr;
}

void Orders::setNumber(int number) { this->number = number; }  //set army number
void Orders::setPlayer(Player* player) { this->player = player; }// set player
void Orders::setTerName(std::string name) { this->terName = name;}//set name method
void Orders::setType(std::string type) { this->orderType = type; }//set type method
// for now, no need to implement the execute() and validate() 

bool Orders::validate() {// initial false
	cout << "From Order: varifing the order..." << endl;
	return false;
}

void Orders::printOrder() {  // print type
	cout << "The order type is " << orderType << endl;
}

//-----------------------------------Deploy--------------------------------------

// Deploy class function defination
Deploy::Deploy():Orders(){}
Deploy::Deploy( Player* inputPlayer, int inputNumber, std::string inputName):Orders(inputPlayer,inputNumber,inputName) {
	this->orderType = "deploy";
	cout << "A Deploy is created" << endl;
}
//avoid memory leak
Deploy::~Deploy()
{
	Orders::~Orders();
	cout << "Deploy is destroied" << endl;
}
//  
bool Deploy::validate() {// if the territory belongs to player and player has enough armies, it is valid. otherwise not
	std::vector<Territory*> vec = (player->getTerritories());
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i]->getName() == terName && player->getArmies() >= number) {
			return true;
		}
	}
	return false;
}
void Deploy::execute(Map* map, Deck* deck) {// deploy arimes to territory.
	cout << "Issue order deployment" << endl;
	if (Deploy::validate()) {
		Territory* ter = player->findTerritory(terName);
		ter->setArmies(ter->getArmies() + number);//territory armies update +number
		player->giveNewArmy(-number);// enforement pool update -number
		cout << "Deploy is completed, the country " << ter->getName() << " has " << ter->getArmies() << " armies" << endl;
		cout << "After deployment, the player's armies now is " << player->getArmies() << endl;
	}
	else {// invalid prompt
		cout << "You are issuing a invalid depolyment order, order reversed " << endl;
	}
	
}
void Deploy::printOrder() {
	cout << "The order type is " << orderType << endl;
}

//------------------------------------------Advance-----------------------------------------------
// Advance class function declaration
Advance::Advance():Orders() {
}
Advance::Advance(Player* player, int number, std::string terName, std::string desName) : Orders(player, number, terName) {
	this->desName = desName;// need an extra instance variable to determin to target territory
	this->orderType = "advance";
	cout << "An advance is created" << endl;
}
Advance::~Advance()
{
	Orders::~Orders();
	cout << "An advance is destroyed" << endl;
}
int Advance::fight(int attack, int defend) {//Two troops fight in defenders' territory
	int attScore = 0, defScore = 0;
	int counter1 = 1, counter2 = 1;
	while (counter1 <= attack) {
		attScore += (rand() / 10);// each soilder has once chance to get a random number and sum them up
		counter1++;
	}
	while (counter2 <= defend) {
		defScore += (rand() / 10);// each soilder has once chance to get a random number and sum them up
		counter2++;
	}
	attScore = attScore * 0.6;//product factor
	defScore = defScore * 0.7;//product factor

	double ration =(double)(attScore - defScore) / (attScore + defScore);//positive attacker win

	return ration * (attack + defend);// winner's harvest
}

bool Advance::validate() {//if the source territory belongs to player, it's valid
	Territory* ter = player->findTerritory(terName);
	if (ter != nullptr && ter->getArmies() >= number) {
		return true;
	}
	return false;
}
void Advance::execute(Map *map,Deck *deck) {
	if (Advance::validate()) {
		Territory* souTer = player->findTerritory(terName);
		Player* targetPlayer = souTer->getOwner();

		//cout << "desName-->" << desName << endl;
		Territory* desTer = map->getTerritory(desName);
		//if source territory and target territory belong same player, it is a deployment
		if (player->getName()== desTer->getOwner()->getName()) {
			desTer->setArmies(desTer->getArmies() + number);
			souTer->setArmies(souTer->getArmies() - number);
			cout << "After Advance, the armies of " << souTer->getName() << " decreased to " << souTer->getArmies()<<" ";
			cout << "The armies of " << desTer->getName() << " increased to " << desTer->getArmies() << endl;
		}
		else {
			cout << player->getName() << " gathered " << number << " armies from " << souTer->getName() << " to " << desTer->getName();
			cout << " , the remaining armies in " << souTer->getName() << " is " << souTer->getArmies() - number << endl;
			souTer->setArmies(souTer->getArmies() - number);//get the defender's number and attacker's number
			int res = this->fight(number, desTer->getArmies());//start to fight
			if (res > 0) {//attackers win
				cout << "After a fight, "<< player->getName() << " defeated " << desTer->getOwner()->getName()<<" in ";
				cout << desTer->getName() << ". The owner is " << player->getName();
				cout << " " << ",and the remaining armies is " << res<<endl;//battle information
				desTer->setOwner(player);//update info, the territory belongs to attacking side
				desTer->setArmies(res);//update the remaining armies
				Card* card = deck->draw(player->getHand());//draw a card as reward
				cout << player->getName() << " as a winner win this card." << endl;
			}
			else if (res < 0) {// defenders win
				desTer->setArmies(-res);
				cout << "After the war "<< player->getName() << " lost the war. ";
				cout << desTer->getOwner()->getName() << " has defended his territory " << desTer->getName();
				cout << " ,the remaining armies is " << -res << endl;//update remaining armies
			}
			else {
				desTer->setArmies(res);//it is tie, both sides left nobody
				cout << "The war that happened in " << desTer->getName() << " was a tie," << player->getName() << " couldn't conquer it."<<endl;

			}
		}
	}
	else {
		cout << "The advance order is invalid, because you tried to conduct other player's armies" << endl;
	}
}
void Advance::printOrder() {
	cout << "The order type is " << orderType << endl;
}
//------------------------------------------------Airlift--------------------------------------------------
// Airlift class function declaration
Airlift::Airlift(Player* player, int number, std::string terName, std::string desName) : Orders(player, number, terName) {
	this->desName = desName; //need to know the target territory
	this->orderType = "airlift";
	cout << "An airlift is created" << endl;
}
Airlift::~Airlift()
{
}
// for now, no need to implement the execute() and validate() 
bool Airlift::validate() {
	  //if player has a airlift card and source territory belons to player
	if (player->getHand()->getACard("airlift") != nullptr && player->findTerritory(this->terName) != nullptr) {
		return true;
	}
	return false;
}
void Airlift::execute(Map* map, Deck* deck) {
	if (Airlift::validate()) {
		if (player->findTerritory(terName)->getArmies() < number) {//if the requestd armies beyond the maximum, assign all
			cout << "You don't have enough armies to airlift, I will assign all the armies in the source territory, it is ";
			cout << player->findTerritory(terName)->getArmies() << endl;
			number = player->findTerritory(terName)->getArmies();
			this->setNumber(number);
		}
		   //it is exact a advance, call advance method
			Advance* ad = new Advance(player, number, terName, desName);
			ad->execute(map,deck);
			delete ad;  //avoid memory leak
			ad = nullptr;
		
	}
	else {
		cout << "Airlift order is invalid, order cancelled " << endl;
	}
	
}
void Airlift::printOrder() {
	cout << "The order type is " << orderType << endl;
}

// Bomb class function declaration
Bomb::Bomb(Player* player,std::string terName):Orders(player,-1,terName) {
	this->orderType = "bomb";
	cout << "A bomb is created" << endl;
}
Bomb::~Bomb()
{
}

bool Bomb::validate() {//if the target territory doesn't belong to player, it is valid
	if (player->getHand()->getACard("bomb") != nullptr && player->findTerritory(terName) == nullptr) {
		return true;
	}
	return false;
}
void Bomb::execute(Map *map, Deck* deck) {
	if (Bomb::validate()) {
		Territory* ter = map->getTerritory(terName);
		if (ter->getOwner() == nullptr) {// if it is a neatrue area, no bomb
			cout << "It is a neature area, order cancelled" << endl;
		}
		else {//release the war's information
			cout << ter->getOwner()->getName() << "'s " << ter->getName() << " territory is being bombed by " << player->getName();
			cout << ", half of its armies are lost, the remaining armies is " << ter->getArmies() / 2 << endl;
			ter->setArmies(ter->getArmies() / 2);//update the new armies after bomb
		}
		
	}
	else {// invalid order
		cout << "Bomb order is invalid, order cancelled " << endl;
	}
	
}
void Bomb::printOrder() {
	cout << "The order type is " << orderType << endl;
}

// Blockade class function declaration
Blockade::Blockade(Player* player, std::string terName) :Orders(player, -1, terName) {
	this->orderType = "blockade";
	cout << "A blockade order is created" << endl;
}
Blockade::~Blockade()
{
}

bool Blockade::validate() {//if player has a blockade card and source territory belongs to player,it's true
	if (this->player->getHand()->getACard("blockade") != nullptr && player->findTerritory(terName) != nullptr) {
		return true;
	}
	return false;
}
void Blockade::execute(Map* map, Deck* deck) {
	if (Blockade::validate()) {
		Territory* ter = player->findTerritory(terName);
		ter->setArmies(ter->getArmies() * 2);//double the number of armies
		ter->setOwner(nullptr);// set this area as neature territory
		cout << player->getName() << "'s territory " << ter->getName() << " is blockaded. ";
		cout << "the number of army is doubled to " << ter->getArmies() << ", but this territory belongs to nobody" << endl;
	}
	else {
		cout << "The blockade order is invalid, it will be cancelled " << endl;
	}
	
}
void Blockade::printOrder() {
	cout << "The order type is " << orderType << endl;
}


// Negotiate class function declaration
Negotiate::Negotiate(Player* player,Player* targetPlayer):Orders(player,-1,"") {
	this->orderType = "negotiate";
	this->targetplayer = targetPlayer;
	cout << "A negotiate order is created" << endl;
}
Negotiate::~Negotiate()
{ //deconstructor to avoid memory leak
	delete this->player;
	delete this->targetplayer;
}

bool Negotiate::validate() {//if a player tries to negotiate with himself, it's invalid, otherwise it's true
	if (player->getName() == targetplayer->getName()) return false;
	return true;
}
void Negotiate::execute(Map* map, Deck* deck) {
	if (Negotiate::validate()) {
		cout << "Now " << this->getPlayer()->getName() << "has made a peacefull deal with " << this->getTargetPlayer()->getName() << endl;
	}
	else {
		cout << "Negotiate order is invalid" << endl;
	}
}
void Negotiate::printOrder() {
	cout << "The order type is " << orderType << endl;
}

