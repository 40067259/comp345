#include <iostream>
#include "Orders.h"

using std::cout;
using std::endl;

//---------------------------------Abstract class--------------------------------------------
Orders::Orders() {
	this->orderType = "none";
	this->terName = NULL;
	this->number = 0;
	this->player = nullptr;
}

Orders::Orders(Player* inputPlayer) {
	orderType = "";
	this->player = inputPlayer;
	cout << "An order is created" << endl;
}

Orders::Orders(Player* inputPlayer, int n, Territory* inputName) {
	orderType = "";
	this->player = inputPlayer;
	this->terName = inputName;
	this->number = n;
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
//void Orders::setTerName(std::string name) { this->terName = name; }
void Orders::setType(std::string type) { this->orderType = type; }
// for now, no need to implement the execute() and validate() 

bool Orders::validate() {
	cout << "From Order: varifing the order..." << endl;
	return false;
}

void Orders::printOrder() {
	cout << "The order type is " << orderType << endl;
}

//========================================================
//added to get the orderType, 
//and the child class is able to use it, right?
std::string Orders::getOrderType()
{
	return orderType;
}
//========================================================


//-----------------------------------Deploy--------------------------------------

// Deploy class function declaration
Deploy::Deploy() :Orders() {}
Deploy::Deploy(Player* inputPlayer, int inputNumber, Territory* inputName) : Orders(inputPlayer, inputNumber,  inputName) {
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
		if (vec[i] == terName && player->getArmies() >= number) {
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
		Territory* ter = player->findTerritory(terName->getName());
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
Advance::Advance() :Orders() {
}
Advance::Advance(Player* player, int number, Territory* terName, Territory* desName) : Orders(player, number, terName) {
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

	double ration = (double)(attScore - defScore) / (attScore + defScore);

	return ration * (attack + defend);
}
// for now, no need to implement the execute() and validate() 
bool Advance::validate() {
	Territory* ter = player->findTerritory(terName->getName());
	if (ter != nullptr && ter->getArmies() >= number) {
		return true;
	}
	return false;
}
void Advance::execute() {
	if (Advance::validate()) {
		Territory* souTer = player->findTerritory(terName->getName());
		Player* targetPlayer = souTer->getOwner();

		cout << "desName-->" << desName->getName() << endl;
		Territory* desTer = desName;

		if (player->getName() == desTer->getOwner()->getName()) {
			desTer->setArmies(desTer->getArmies() + number);
			souTer->setArmies(souTer->getArmies() - number);
			cout << "After Advance, the armies of " << souTer->getName() << " decreased to " << souTer->getArmies() << " ";
			cout << "The armies of " << desTer->getName() << " increased to " << desTer->getArmies() << endl;
		}
		else {
			cout << player->getName() << " gathered " << number << " armies from " << souTer->getName() << " to " << desTer->getName();
			cout << " , the remaining armies in " << souTer->getName() << " is " << souTer->getArmies() - number << endl;
			souTer->setArmies(souTer->getArmies() - number);
			int res = this->fight(number, desTer->getArmies());
			if (res > 0) {
				cout << "After a fight, " << player->getName() << " defeated " << desTer->getOwner()->getName() << " in ";
				cout << desTer->getName() << ". The owner is " << player->getName();
				cout << " " << ",and the remaining armies is " << res << endl;
				desTer->setOwner(player);
				desTer->setArmies(res);
			}
			else if (res < 0) {
				desTer->setArmies(-res);
				cout << "After the war " << player->getName() << " lost the war. ";
				cout << desTer->getOwner()->getName() << " has defended his territory " << desTer->getName();
				cout << " ,the remaining armies is " << -res << endl;
			}
			else {
				desTer->setArmies(res);
				cout << "The war that happened in " << desTer->getName() << " was a tie," << player->getName() << " couldn't conquer it." << endl;

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
Airlift::Airlift(Player* player, int number, Territory* terName, Territory* desName) : Orders(player, number, terName) {
	this->desName = desName;
	this->orderType = "airlift";
	cout << "An airlift is created" << endl;
}
Airlift::~Airlift()
{
}
// for now, no need to implement the execute() and validate() 
bool Airlift::validate() {
	cout << player->getHand()->getACard("airlift")->getType() << "<-----------------" << endl;
	cout << player->findTerritory(terName->getName()) << "<--------------" << endl;
	if (player->getHand()->getACard("airlift") != nullptr && player->findTerritory(terName->getName()) != nullptr) {
		return true;
	}
	return false;
}
void Airlift::execute() {
	if (Airlift::validate()) {
		if (player->findTerritory(terName->getName())->getArmies() < number) {
			cout << "You don't have enough armies to airlift, I will assign all the armies in the source territory, it is ";
			cout << player->findTerritory(terName->getName())->getArmies() << endl;
			number = player->findTerritory(terName->getName())->getArmies();
			this->setNumber(number);
		}

		Advance* ad = new Advance(player, number, terName, desName);
		ad->execute();
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
Bomb::Bomb(Player* player, Territory* terName) :Orders(player, -1, terName) {
	this->orderType = "bomb";
	cout << "A bomb is created" << endl;
}
Bomb::~Bomb()
{
}
// for now, no need to implement the execute() and validate() 
bool Bomb::validate() {
	if (player->getHand()->getACard("bomb") != nullptr && player->findTerritory(terName->getName()) == nullptr) {
		return true;
	}
	return false;
}
void Bomb::execute() {
	if (Bomb::validate()) {
		Territory* ter = terName;
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
Blockade::Blockade(Player* player, Territory* terName) :Orders(player,0, terName) {
	this->orderType = "blockade";
	cout << "A blockade order is created" << endl;
}
Blockade::~Blockade()
{
}
// for now, no need to implement the execute() and validate() 
bool Blockade::validate() {
	if (this->player->getHand()->getACard("blockade") != nullptr && player->findTerritory(terName->getName()) != nullptr) {
		return true;
	}
	return false;
}
void Blockade::execute() {
	if (Blockade::validate()) {
		Territory* ter = player->findTerritory(terName->getName());
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
Negotiate::Negotiate(Player* player1, Player* player2) :Orders(player1) {
	p2 = player2;
}
Negotiate::~Negotiate()
{
	p2 = NULL;
}
// for now, no need to implement the execute() and validate() 
bool Negotiate::validate() {
	cout << "varifing the Negotiate order..." << endl;
	if (p2 = getPlayer())
	{
		cout << "Error, you can only negotiate with enemy!" << endl;
		return false;
	}
	return true;
}
void Negotiate::execute() {
	if (validate())
	{
		cout << "Successful negotiation. "<< endl;
	}
}
void Negotiate::printOrder() {
	cout << "The order type is " << orderType << endl;
}

