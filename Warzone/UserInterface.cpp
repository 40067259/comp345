#include "Territory.h"
#include "UserInterface.h"
#include "Map.h"
#include "MapLoader.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif


std::vector<std::string> listFiles(const std::string& directory) {
#ifdef _WIN32
    // windows implementation
	std::vector<std::string> files;
	std::string pattern(directory);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	return files;
#else
    // Linux + Mac implementation
    std::vector<std::string> files;
    DIR* dirp = opendir(directory.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        files.push_back(dp->d_name);
    }
    closedir(dirp);
    return files;
#endif
}

std::string removeExtension(const std::string& file) {
    int i;
    for (i = 0; i < file.size(); ++i) {
        if (file[i] == '.') break;
    }

    return file.substr(0, i);
}

std::vector<int> split(const std::string &input, char delim) {
    std::stringstream ss(input);
    std::string segment;
    std::vector<int> contents;
    while (std::getline(ss, segment, delim)) {
        contents.push_back(std::stoi(segment));
    }
    return contents;
}

void tryAgain() {
    std::cerr << "Invalid choice. Try again.\n" << std::endl;
    std::cout << ">>> ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string UserInterface::selectMap() {
    const auto files = listFiles("Resources");
    bool validMap = false;
    int mapChoice;
    std::string mapName;

    std::cout << "Please select a map to use.\n";

    for (int i = 2; i < files.size(); ++i) {
        std::cout << i - 1 << ". " << removeExtension(files[i]) << std::endl;
    }

    do {
        std::cout << std::endl;
        std::cout << ">>> ";
        std::cin >> mapChoice;
        while (mapChoice < 1 || mapChoice >= files.size() - 1) {
            tryAgain();
            std::cin >> mapChoice;
        }

        mapName = "Resources/" + files[mapChoice + 1];

        Map map = MapLoader::loadMap(mapName);

        if (map.getTerritories().size() == 0) {
            std::cout << "Invalid map file. Choose again." << std::endl;
            validMap = false;
        }
        else {
            validMap = true;
        }
    } while (!validMap);

    return mapName;
}

int UserInterface::selectNumPlayers() {
    std::cout << "\n";

    std::cout << "Select the number of players (2-6):\n";
    int nPlayers;

    std::cout << ">>> ";
    std::cin >> nPlayers;
    while (nPlayers < 2 || nPlayers > 6) {
        tryAgain();
        std::cin >> nPlayers;
    }

    return nPlayers;
}

Territory UserInterface::selectTerritory(std::vector<Territory> Territories) {
    int sourceChoice;

    std::cout << "Source territories with available target territories:" << std::endl;

    for (int i = 0; i < territories.size(); i++) {
        std::cout << i + 1 << ". " << territories[i].getName() << std::endl;
    }

    std::cout << std::endl;
    std::cout << ">>> ";
    std::cin >> sourceChoice;

    while ((sourceChoice < 1) || (sourceChoice > territories.size())) {
        tryAgain();
        std::cin >> sourceChoice;
    }

    return territories[sourceChoice - 1];
}

Territory UserInterface::selectAdjacentTerritory(std::vector<Territory> adjacentTerritories) {
    int targetChoice;

    std::cout << "Available target/adjacent territories:" << std::endl;
    for (int i = 0; i < adjacentTerritories.size(); i++) {

        std::cout << i + 1 << ". " << adjacentTerritories[i].getName() << std::endl;
    }

    std::cout << std::endl;
    std::cout << ">>> ";
    std::cin >> targetChoice;

    while ((targetChoice < 1) || (targetChoice > adjacentTerritories.size())) {
        tryAgain();
        std::cin >> targetChoice;
    }

    return adjacentTerritories[targetChoice - 1];
}

int UserInterface::selectArmiesToMove(const Territory& source) {
    int nArmies;

    std::cout << source.getName() << " has " << source.getArmies() << " armies." << std::endl;
    std::cout << "Enter the number of armies you want to move to your target territory." << std::endl;

    std::cout << ">>> ";
    std::cin >> nArmies;

    while ((nArmies < 1) || (nArmies > source.getArmies() - 1)) {
        tryAgain();
        std::cin >> nArmies;
    }

    return nArmies;
}

int UserInterface::selectArmiesToReinforce(const Territory& source, int remainingArmies) {
    int nArmies;

    std::cout << source.getName() << " has " << source.getArmies() << " armies." << std::endl;
    std::cout << "Enter the number of armies you want to move to your target territory." << std::endl;

    std::cout << ">>> ";
    std::cin >> nArmies;

    while ((nArmies < 1) || nArmies > remainingArmies) {
        tryAgain();
        std::cin >> nArmies;
    }

    return nArmies;
}

int UserInterface::exchangeCards(Player& player) {
    if (player.getHand().empty() || player.getHand().size() < 3) {
        std::cout << "You don't have enough cards to exchange.\n";
        return 0;
    }
    else {
        std::cout << "Here are your cards:\n";
        for (int i = 0; i < player.getHand().size(); ++i) {
            const auto card = player.getHand().getCards()[i];
            std::cout << i + 1 << ". " << card << std::endl;
        }
    }

    std::string input;

    if (player.getHand().size() > 5){
        std::cout << "You have more than 5 cards, you need to exchange.\n";
        std::cout << ">>> ";
        std::cin >> input;
    }
	else{
        std::cout << "Select cards you would like to exchange, or 0 to skip.\n";
        std::cout << ">>> ";
        std::cin >> input;
        if (input == "0"){
            return 0;
        }
    }

    auto indices = split(input, ',');

    auto card0 = player.getHand().getCards()[indices[0] - 1];
    auto card1 = player.getHand().getCards()[indices[1] - 1];
    auto card2 = player.getHand().getCards()[indices[2] - 1];

    int numExchanged = player.getHand().exchange(card0, card1, card2);
    if (numExchanged > 0) {
        std::cout << "You exchanged cards for " << numExchanged << " soldiers.\n";
    }
    else {
        std::cout << "You have attempted to exchange an invalid set of cards.\n";
    }

    return numExchanged;
}

bool UserInterface::toAttackOrNot() {
    int input;

    std::cout << "Do you want to attack? 1 = yes, 0 = no" << std::endl;

    std::cout << ">>> ";
    std::cin >> input;

    while ((input > 1)  || (input < 0)) {
        tryAgain();
        std::cin >> input;
    }

    if (input == 1) {
        return true;
    }
    else {
        return false;
    }
}

int UserInterface::selectAttackerDice(const Territory& territory) {
    int max = std::min(territory.getArmies() - 1, 3);
    int input;

    std::cout << "Attacker: Enter the number of dice to roll." << std::endl;

    std::cout << ">>> ";
    std::cin >> input;

    while ((input > max) || (input < 1)) {
        tryAgain();
        std::cin >> input;
    }

    return input;
}

int UserInterface::selectDefenderDice(const Territory& territory) {
    int max = std::min(territory.getArmies(), 2);
    int input;

    std::cout << "Defender: Enter the number of dice to roll. " << std::endl;

    std::cout << ">>> ";
    std::cin >> input;

    while ((input > max) || (input < 1)) {
        tryAgain();
        std::cin >> input;
    }

    return input;
}
