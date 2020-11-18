#include <iostream>
#include "Orders.h"

using std::cout;
using std::endl;

//---------------------------------Abstract class--------------------------------------------
Orders::Orders() {
	this->orderType = "none";
	this->terName = " none";
	this->number = 0;
	this->player = nullptr;
}
Orders::Orders(Player* inputPlayer, int inputNumber, std::string inputName) {
	orderType = "";
	this->player = inputPlayer;
	this->number = inputNumber;
	this->terName = inputName;
	cout << "An order is created" << endl;
}
// there will be constructor overload, depend on the type of orders


Orders::~Orders()
{
	delete this->player;
	player = nullptr;
}

void Orders::setNumber(int number) { this->number = number; }
void Orders::setPlayer(Player* player) { this->player = player; }
void Orders::setTerName(std::string name) { this->terName = name;}
void Orders::setType(std::string type) { this->orderType = type; }
// for now, no need to implement the execute() and validate() 

bool Orders::validate() {
	cout << "From Order: varifing the order..." << endl;
	return false;
}
void Orders::execute() {
	Orders::validate();
	cout << "implementing the order... the order is invalide" << endl;
}
void Orders::printOrder() {
	cout << "The order type is " << orderType << endl;
}

//-----------------------------------Deploy--------------------------------------

// Deploy class function declaration
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
// for now, no need to implement the execute() and validate() 
bool Deploy::validate() {
	std::vector<Territory*> vec = (player->getTerritories());
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i]->getName() == terName && player->getArmies() >= number) {
			cout << "Deploy order is valid, start to deploy..." << endl;
			return true;
		}
	}
	cout << "varifing the deploy order..." << endl;
	return false;
}
void Deploy::execute() {
	cout << "Issue order deployment" << endl;
	if (Deploy::validate()) {
		Territory* ter = player->findTerritory(terName);
		ter->setArmies(ter->getArmies() + number);
		player->giveNewArmy(-number);
		cout << "Deploy is completed, the country " << ter->getName() << " has " << ter->getArmies() << " armies" << endl;
		cout << "After deployment, the player's armies now is " << player->getArmies() << endl;
	}
	else {
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
	this->desName = desName;
	this->orderType = "advance";
	cout << "An advance is created" << endl;
}
Advance::~Advance()
{
	Orders::~Orders();
	cout << "An advance is destroyed" << endl;
}
int Advance::fight(int attack, int defend) {
	int attScore = 0, defScore = 0;
	int counter1 = 1, counter2 = 1;
	while (counter1 <= attack) {
		attScore += (rand() / 10);
		counter1++;
	}
	while (counter2 <= defend) {
		defScore += (rand() / 10);
		counter2++;
	}
	attScore = attScore * 0.6;
	defScore = defScore * 0.7;

	double ration =(double)(attScore - defScore) / (attScore + defScore);

	return ration * (attack + defend);
}
// for now, no need to implement the execute() and validate() 
bool Advance::validate() {
	Territory* ter = player->findTerritory(terName);
	if (ter != nullptr && ter->getArmies() >= number) {
		return true;
	}
	return false;
}
void Advance::execute(Map map) {
	if (Advance::validate()) {
		Territory* souTer = player->findTerritory(terName);
		Player* targetPlayer = souTer->getOwner();

		cout << "desName-->" << desName << endl;
		Territory* desTer = map.getTerritory(desName);

		if (player->getName()== desTer->getOwner()->getName()) {
			desTer->setArmies(desTer->getArmies() + number);
			souTer->setArmies(souTer->getArmies() - number);
			cout << "After Advance, the armies of " << souTer->getName() << " decreased to " << souTer->getArmies()<<" ";
			cout << "The armies of " << desTer->getName() << " increased to " << desTer->getArmies() << endl;
		}
		else {
			cout << player->getName() << " gathered " << number << " armies from " << souTer->getName() << " to " << desTer->getName();
			cout << " , the remaining armies in " << souTer->getName() << " is " << souTer->getArmies() - number << endl;
			souTer->setArmies(souTer->getArmies() - number);
			int res = this->fight(number, desTer->getArmies());
			if (res > 0) {
				cout << "After a fight, "<< player->getName() << " defeated " << desTer->getOwner()->getName()<<" in ";
				cout << desTer->getName() << ". The owner is " << player->getName();
				cout << " " << ",and the remaining armies is " << res<<endl;
				desTer->setOwner(player);
				desTer->setArmies(res);
			}
			else if (res < 0) {
				desTer->setArmies(-res);
				cout << "After the war "<< player->getName() << " lost the war. ";
				cout << desTer->getOwner()->getName() << " has defended his territory " << desTer->getName();
				cout << " ,the remaining armies is " << -res << endl;
			}
			else {
				desTer->setArmies(res);
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
	this->desName = desName;
	this->orderType = "airlift";
	cout << "An airlift is created" << endl;
}
Airlift::~Airlift()
{
}
// for now, no need to implement the execute() and validate() 
bool Airlift::validate() {

	if (player->getHand()->getACard("airlift") != nullptr && player->findTerritory(this->terName) != nullptr) {
		return true;
	}
	return false;
}
void Airlift::execute(Map map) {
	if (Airlift::validate()) {
		if (player->findTerritory(terName)->getArmies() < number) {
			cout << "You don't have enough armies to airlift, I will assign all the armies in the source territory, it is ";
			cout << player->findTerritory(terName)->getArmies() << endl;
			number = player->findTerritory(terName)->getArmies();
			this->setNumber(number);
		}
		
			Advance* ad = new Advance(player, number, terName, desName);
			ad->execute(map);
			delete ad;
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
// for now, no need to implement the execute() and validate() 
bool Bomb::validate() {
	if (player->getHand()->getACard("bomb") != nullptr && player->findTerritory(terName) == nullptr) {
		return true;
	}
	return false;
}
void Bomb::execute(Map map) {
	if (Bomb::validate()) {
		Territory* ter = map.getTerritory(terName);
		if (ter->getOwner() == nullptr) {
			cout << "It is a neature area, order cancelled" << endl;
		}
		else {
			cout << ter->getOwner()->getName() << "'s " << ter->getName() << " territory is being bombed by " << player->getName();
			cout << ", half of its armies are lost, the remaining armies is " << ter->getArmies() / 2 << endl;
			ter->setArmies(ter->getArmies() / 2);
		}
		
	}
	else {
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
// for now, no need to implement the execute() and validate() 
bool Blockade::validate() {
	cout << player->findTerritory(terName)->getName() << "<--------************---" << endl;
	cout << this->player->getHand()->getACard("blockade")->getType() << "<-----------" << endl;
	if (this->player->getHand()->getACard("blockade") != nullptr && player->findTerritory(terName) != nullptr) {
		return true;
	}
	return false;
}
void Blockade::execute() {
	if (Blockade::validate()) {
		Territory* ter = player->findTerritory(terName);
		ter->setArmies(ter->getArmies() * 2);
		ter->setOwner(nullptr);
		cout << player->getName() << "'s territory " << ter->getName() << " is blockaded. ";
		cout << "the number of army is doubled to " << ter->getArmies() << ", but this territory belongs to nobody" << endl;
	}
	cout << "The blockade order is invalid, it will be cancelled " << endl;
}
void Blockade::printOrder() {
	cout << "The order type is " << orderType << endl;
}




// Negotiate class function declaration
Negotiate::Negotiate() {
}
Negotiate::~Negotiate()
{
}
// for now, no need to implement the execute() and validate() 
bool Negotiate::validate() {
	cout << "varifing the Negotiate order..." << endl;
	return false;
}
void Negotiate::execute() {
	Negotiate::validate();
	cout << "implementing the Negotiate order... " << endl;
}
void Negotiate::printOrder() {
	cout << "The order type is " << orderType << endl;
}

