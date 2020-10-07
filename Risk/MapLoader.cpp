#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main()
{
    //string filePath = "../map/france.map"; TODO: dont know why it doesn't work
    std::string fileInput = "estonia.map";

    return 0;
}

Map MapLoader::loadMap(std::string fileInput)
{

    Map map;

    std::string line;
    std::ifstream fileToRead;

    fileToRead.open(fileInput);

    if (fileToRead.is_open())
    {
        //[Continents]
        // [to get the continents section]
        while (std::getline(fileToRead, line))
        {
            if (line == "[continents]")
            {
                break;
            }
        }
        // [to get the continents section]
        while (std::getline(fileToRead, line) && line != "")
        {

            const int equalsIndex = line.find(" ");
            const std::string continent = line.substr(0, equalsIndex);
            const int value = std::stoi(line.substr(equalsIndex + 1));

            // add continentName and nativeArmy
            map.addContinent(continent, value);
            cout << "Continent: " << continent << " Value: " << value << "\n";
        }
        cout << "\n";
        //[Continents]

        //[Territories]
        // [to get the countries section]
        while (std::getline(fileToRead, line))
        {
            if (line == "[countries]")
            {
                break;
            }
        }
        // [to get the countries section]
        int count = 1;
        while (std::getline(fileToRead, line) && line != "")
        {
            if (count < 10)
            {
                // [Remove the index]
                std::string country = line.substr(2, line.length());
                // [Remove the index]

                // [country]
                std::string country = line.substr(2, line.length());
                const int equalsIndex = country.find(" ");
                country = country.substr(0, equalsIndex);
                // [country]

                // [continent number]
                std::string continentNbStr = line.substr(3, line.length());
                continentNbStr = continentNbStr.substr(equalsIndex, continentNbStr.length());
                continentNbStr = continentNbStr.substr(0, 1);

                //convert string to integer
                int continentNb = std::stoi(continentNbStr);

                std::string continentName;

                // [continent number]

                // [armies]
                std::string armiesNbStr = line.substr(2, line.length());
                const int emptySpace_armiesNb = armiesNbStr.find(" ");
                armiesNbStr = armiesNbStr.substr(emptySpace_armiesNb, armiesNbStr.length());
                armiesNbStr = armiesNbStr.substr(3, armiesNbStr.length());
                const int emptySpace_armiesNb2 = armiesNbStr.find(" ");
                armiesNbStr = armiesNbStr.substr(0, emptySpace_armiesNb2);

                //convert string to integer
                int armiesNb = std::stoi(armiesNbStr);
                // [armies]

                // [index]
                std::string indexNbStr = line.substr(2, line.length()); //"Hiiumaa 1 167 172"
                indexNbStr = indexNbStr.substr(indexNbStr.length() - 3, indexNbStr.length());
                if (indexNbStr[0] == ' ')
                {
                    indexNbStr = indexNbStr.substr(0, indexNbStr.length());
                }

                //convert string to integer
                int indexNb = std::stoi(indexNbStr);
                // [index]

                // [add country to unordered map]
                map.addTerritory(country, continentNbStr, armiesNb, indexNb); //change continentNbStr to real continent name
                // [add country to unordered map]
            }
            else if (count > 9)
            {
                //country
                std::string country = line.substr(3, line.length());
                const int equalsIndex = country.find(" ");
                country = country.substr(0, equalsIndex);
                //country

                // [continent number]
                std::string continentNbStr = line.substr(4, line.length());
                continentNbStr = continentNbStr.substr(equalsIndex, continentNbStr.length());
                continentNbStr = continentNbStr.substr(0, 1);

                //convert string to integer
                int continentNb = std::stoi(continentNbStr);
                // [continent number]

                // [armies]
                std::string armiesNbStr = line.substr(3, line.length());
                const int emptySpace_armiesNb = armiesNbStr.find(" ");
                armiesNbStr = armiesNbStr.substr(emptySpace_armiesNb, armiesNbStr.length());
                armiesNbStr = armiesNbStr.substr(3, armiesNbStr.length());
                const int emptySpace_armiesNb2 = armiesNbStr.find(" ");
                armiesNbStr = armiesNbStr.substr(0, emptySpace_armiesNb2);

                //convert string to integer
                int armiesNb = std::stoi(armiesNbStr);
                // [armies]

                // [index]
                std::string indexNbStr = line.substr(2, line.length()); //"Hiiumaa 1 167 172"
                indexNbStr = indexNbStr.substr(indexNbStr.length() - 3, indexNbStr.length());
                if (indexNbStr[0] == ' ')
                {
                    indexNbStr = indexNbStr.substr(0, indexNbStr.length());
                }

                //convert string to integer
                int indexNb = std::stoi(indexNbStr);
                // [index]

                // [add country to unordered map]
                map.addTerritory(country, continentNbStr, armiesNb, indexNb); //change continentNbStr to real continent name
                // [add country to unordered map]
            }
            count++;
        }
        //[Territories]
    }
    else
    {
        cout << "No such file";
    }

    //[Re-read file]
    fileToRead.clear();

    return map;

}