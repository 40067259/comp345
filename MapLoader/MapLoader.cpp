#include "MapLoader.h"
#include "Map.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using std::vector;
using std::cout;
using std::string;
using std::ifstream;
using std::map;


MapLoader::MapLoader()/* : Map()*/
{ 
}

vector<string> split(string str, string token) {
    vector<string>result;
    while (str.size()) {
        int index = str.find(token);
        if (index != string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)result.push_back(str);
        }
        else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


void MapLoader::loadMap(string fileInput)
{

    //MapLoader map;

    int count = 1;
    
    string line;

    ifstream fileToRead(fileInput);

    vector<string>continentsList; //to store continent for later use

    vector<string>countryList;

    if (fileToRead.is_open())
    {
        // [continents]

        // [to get the continents section]
        while (std::getline(fileToRead, line))
        {
            if (line == "[continents]")
            {
                break;
            }
        }
        // [to get the continents section]

        cout << "[Continent Section: ]" << "\n";
        while (std::getline(fileToRead, line) && line != "")
        {
            const int equalsIndex = line.find(" ");
            const std::string continent = line.substr(0, equalsIndex);
            const int value = std::stoi(line.substr(equalsIndex + 1));

            // add continentName and nativeArmy
            map.addContinent(continent, value);
            continentsList.push_back(continent);
            cout << "Continent: " << continent << " Value: " << value << "\n"; //TODO
        }
        cout << "[End of Continent Section]" << "\n";
        //cout << "\n"; //TODO

        // [continents]


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

        cout << "[Territory Section: ]" << "\n";
        while (std::getline(fileToRead, line) && line != "")
        {
            // [get the order]
            std::string indexOrderStr = line;
            int emptySpace_indexOrderStr = indexOrderStr.find(" ");
            indexOrderStr.substr(0, emptySpace_indexOrderStr);

            //convert string to integer for continentNb
            int indexOrder = 0;
            try {
                indexOrder = std::stoi(indexOrderStr);
                //cout << "index converted" << "\n";
            }
            catch (const std::exception& ex) {
                cout << "no order index";
            }
            catch (const std::string& ex) {
                cout << "no order index";
            }
            catch (...) {
                cout << "no order index";
            }
            //convert string to integer for index 

            // [get the order]

            // [country]
            std::string country = line;
            int emptySpace_country1 = country.find(" ");
            emptySpace_country1 = emptySpace_country1 + 1;
            country = country.substr(emptySpace_country1, country.length()-1);
            int emptySpace_country2 = country.find(" ");
            country = country.substr(0, emptySpace_country2);

            cout << country << "\n"; //TODO

            // [country]

            // [continent number]
            std::string continentNbStr = line;
            int emptySpace_continent1 = continentNbStr.find(" ");
            emptySpace_continent1 = emptySpace_continent1 + 1;
            continentNbStr = continentNbStr.substr(emptySpace_continent1, continentNbStr.length() - 1);
            int emptySpace_continent2 = continentNbStr.find(" ");
            emptySpace_continent2 = emptySpace_continent2 + 1;
            continentNbStr = continentNbStr.substr(emptySpace_continent2, continentNbStr.length() - 1);
            int emptySpace_continent3 = continentNbStr.find(" ");
            continentNbStr = continentNbStr.substr(0, emptySpace_continent3);

            //convert string to integer for continentNb
            int continentNb = 0;
            try {
                continentNb = std::stoi(continentNbStr);
                //cout << "index converted" << "\n";
            }
            catch (const std::exception& ex) {
                cout << "no index";
            }
            catch (const std::string& ex) {
                cout << "no index";
            }
            catch (...) {
                cout << "no index";
            }
            //convert string to integer for index 

            // [convert the number back to the name]
            string continenttoParse= continentsList[continentNb-1]; //continentNb
            cout << "Territory belongs to (continent): " << continenttoParse << "\n"; //TODO
            // [convert the number back to the name]

            // [continent number]


            // [armies]
            std::string armiesNbStr = line;
            int emptySpace_armiesNb1 = armiesNbStr.find(" ");
            emptySpace_armiesNb1 = emptySpace_armiesNb1 + 1;
            armiesNbStr = armiesNbStr.substr(emptySpace_armiesNb1, armiesNbStr.length() - 1);
            int emptySpace_armiesNb2 = armiesNbStr.find(" ");
            emptySpace_armiesNb2 = emptySpace_armiesNb2 + 1;
            armiesNbStr = armiesNbStr.substr(emptySpace_armiesNb2, armiesNbStr.length() - 1);
            int emptySpace_armiesNb3 = armiesNbStr.find(" ");
            emptySpace_armiesNb3 = emptySpace_armiesNb3 + 1;
            armiesNbStr = armiesNbStr.substr(emptySpace_armiesNb3, armiesNbStr.length() - 1);
            int emptySpace_armiesNb4 = armiesNbStr.find(" "); //the last empty space
            emptySpace_armiesNb4 = emptySpace_armiesNb4;
            armiesNbStr = armiesNbStr.substr(0, emptySpace_armiesNb4);

            //convert string to integer for armies
            int armiesNb = 0;
            try {
                armiesNb = std::stoi(armiesNbStr);
                //cout << "armies converted" << "\n";
            }
            catch (const std::exception& ex) {
                cout << "no armies";
            }
            catch (const std::string& ex) {
                cout << "no armies";
            }
            catch (...) {
                cout << "no armies";
            }
            //convert string to integer for armies

            cout << "Army: " << armiesNbStr << "\n"; //TODO

            // [armies]


            // [index]
            std::string indexNbStr = line;
            int emptySpace_indexNb1 = indexNbStr.find(" ");
            emptySpace_indexNb1 = emptySpace_indexNb1 + 1;
            indexNbStr = indexNbStr.substr(emptySpace_indexNb1, indexNbStr.length() - 1);
            int emptySpace_indexNb2 = indexNbStr.find(" ");
            emptySpace_indexNb2 = emptySpace_indexNb2 + 1;
            indexNbStr = indexNbStr.substr(emptySpace_indexNb2, indexNbStr.length() - 1);
            int emptySpace_indexNb3 = indexNbStr.find(" ");
            emptySpace_indexNb3 = emptySpace_indexNb3 + 1;
            indexNbStr = indexNbStr.substr(emptySpace_indexNb3, indexNbStr.length() - 1);
            int emptySpace_indexNb4 = indexNbStr.find(" ");
            emptySpace_indexNb4 = emptySpace_indexNb4 + 1;
            indexNbStr = indexNbStr.substr(emptySpace_indexNb4, indexNbStr.length() - 1);

            //convert string to integer for index
            int indexNb = 0;
            try {
                indexNb = std::stoi(indexNbStr);
                //cout << "index converted" << "\n";
            }
            catch (const std::exception& ex) {
                cout << "no index";
            }
            catch (const std::string& ex) {
                cout << "no index";
            }
            catch (...) {
                cout << "no index";
            }
            //convert string to integer for index 
            cout << "Index: " << indexNbStr << "\n"; //TODO

            // [index]


            // [add country to unordered map]
            map.addTerritory(country, continentsList[continentNb - 1], armiesNb, indexNb);
            countryList.push_back(country);//add country to the vector for later use
            // [Setup edges]
            //map.addEdge(country, *map.getTerritory(country)); //append in the border section
            // [Setup edges]
        }
        cout << "[End of Territory Section]" << "\n";
         //[Territories]

        // [Borders]
        //cout << "[Borders Section: ]" << "\n"; //TODO
        // [to get the borders section]
        while (std::getline(fileToRead, line))
        {
            if (line == "[borders]")
            {
                break;
            }
        }
        // [to get the borders section]
        while (std::getline(fileToRead, line) && line != "")
        {
            vector<string>edgesStrList = split(line, " ");
            vector<int>edgesList;

            string currentTerritory = edgesStrList[0];

            int currentTerritoryNb = 0;
            //convert string to integer for currentTerritoryNb
            try {
                currentTerritoryNb = std::stoi(currentTerritory);
                //cout << "index converted" << "\n";
            }
            catch (const std::exception& ex) {
                cout << "no conversion";
            }
            catch (const std::string& ex) {
                cout << "no conversion";
            }
            catch (...) {
                cout << "no conversion";
            }
            //convert string to integer for currentTerritoryNb
            currentTerritoryNb = currentTerritoryNb - 1; //everything starts from 0
            //cout << "Current: " << currentTerritoryNb << " "<< countryList[currentTerritoryNb] << "\n";//TODO

            for(int i=1; i< edgesStrList.size(); i++)
            {
                int edgeNb = 0;
                try {
                    edgeNb = std::stoi(edgesStrList[i]);
                    edgeNb = edgeNb - 1; //everything starts from 0
                    edgesList.push_back(edgeNb);
                    //cout << "index converted" << "\n";
                }
                catch (const std::exception& ex) {
                    cout << "no index";
                }
                catch (const std::string& ex) {
                    cout << "no index";
                }
                catch (...) {
                    cout << "no index";
                }

                //cout << "The edges numbers " << edgesStrList[i];//TODO
            }
            //convert string to integer for edges 
           
            
            for (int i = 0; i < edgesList.size(); i++)
            {
                map.addEdge(countryList[currentTerritoryNb], *map.getTerritory(countryList[edgesList[i]]));
                //cout << "Edges: " << countryList[edgesList[i]] << "\n"; //TODO
            }
        }
        
        //cout << "[End of Borders Section]" << "\n"; //TODO
        // [Borders]


    }
    else
    {
    cout << "No such file";
    }

 fileToRead.clear();
 fileToRead.seekg(0, fileToRead.beg);



 // [Setup continents]
 map.addTerritoriesToContinents();
 // [Setup continents]

// map.printMap();
//map.printMapInfo();

 fileToRead.close();

}

