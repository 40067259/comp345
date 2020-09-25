#include "Player.h"
#include <vector>
#include <iostream>
#include <iomanip>

Player::Player(std::vector<Territory> territories, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy) : _territories(territories), _hand(hand), _dice(dice), player(playerNumber) {
        this->setStrategy(strategy);
}

Player::Player(int playerNumber) : player(playerNumber) {}

Hand& Player::getHand() {
    return this->_hand;
}

const Hand& Player::getHand() const {
    return this->_hand;
}

std::vector<Territory>& Player::getTerritories() {
    return this->_territories;
}

const std::vector<Territory>& Player::getTerritories() const {
    return this->_territories;
}

DiceFacility Player::getDice() const {
    return this->_dice;
}

void Player::setTerritories(std::vector<Territory> territories) {
    this->_territories = territories;
}

void Player::setHand(Hand hand) {
    this->_hand = hand;
}

void Player::setDice(DiceFacility dice) {
    this->_dice = dice;
}

std::string Player::getID() {
    return "Player " + std::to_string(player);
}

int Player::getIDAsInt(){
    return player;
}

void Player::assignTerritory(Territory c) {
    _territories.push_back(c);
}

void Player::printTerritories() {
    for (int i = 0; i<_territories.size(); i++) {
        std::cout << "Territory: " << _territories[i].getName() << " with " << _territories[i].getArmies() << " armies." << std::endl;
    }
}

int Player::amtTerritories() {
    return _territories.size();
}

int Player::getPlayerArmies() {
    return armies;
}

void Player::initializeArmies(){
    int number = armies;
    int index = 0;
    while (number>0)
    {
        if (index>_territories.size() - 1) { index = 0; }
        _territories[index++].increaseArmies();
        number--;
    }
}

void Player::setArmies(int nArmies) {
    armies = nArmies;
}

void Player::notifyPhase(int phase) {
    // reinforcement
    if (phase == 1) {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "Armies: " << getPlayerArmies() << ", Cards: " << getHand().size() << ", Territories Owned: " << getTerritories().size() << std::endl;
        std::cout << "\nTerritories                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _territories.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }

    // attack
    else if (phase == 2) {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "\nTerritories                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _territories.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }

    // fortification
    else {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "\nTerritories                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _territories.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _territories[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }
}

void Player::notifyGame(int totalTerritories) {
    int currentTerritories = _territories.size();
    double percent = (double)currentTerritories / totalTerritories;
	std::cout << getID() << ": " << currentTerritories << "/" << totalTerritories << ", " << percent * 100 << "% " << "of territories owned." << std::endl;
}

void Player::setStrategy(Strategy *strategy){
    this->strategy = strategy;
}

void Player::executeReinforcement(Player* player){
    this->strategy->reinforcement(player);
}

void Player::executeAttack(Player* player){
    this->strategy->attack(player);
}

void Player::executeFortify(Player* player){
    this->strategy->fortify(player);
}
