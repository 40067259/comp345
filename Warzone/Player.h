#pragma once
#include <vector>
#include <string>
#include "DiceFacility.h"
#include "Territory.h"
#include "Hand.h"
#include "Observer.h"
#include "HumanPlayer.h"

class Strategy;

class Player : public Observer {
private:
	Strategy *strategy;
	std::vector<Territory> _territories;
	Hand _hand;
	DiceFacility _dice;
	int player = 0;
	int armies = 0;

public:
	Player() = default;
	Player(std::vector<Territory> territories, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy);
	Player(int playerNumber);
	std::vector<Territory>& getTerritories();
	const std::vector<Territory>& getTerritories() const;
	Hand& getHand();
	const Hand& getHand() const;
	DiceFacility getDice() const;
	std::string getID();
	int getIDAsInt();
	void assignTerritory(Territory c);
	int amtTerritories();
	void initializeArmies();
	int getPlayerArmies();
	void setArmies(int nArmies);
	void printTerritories();

    // Strategy pattern
    void setStrategy(Strategy *strategy);
	void executeReinforcement(Player* player);
	void executeAttack(Player* player);
	void executeFortify(Player* player);

	// Observer pattern
	void notifyPhase(int);
    void notifyGame(int totalTerritories);

private:
	void setTerritories(std::vector<Territory> territories);
	void setHand(Hand hand);
	void setDice(DiceFacility dice);
};
