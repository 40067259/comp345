#include "MapLoader.h"
#include "Map.h"
#include <list>
#include <string>
using std::cout;
using std::string;
using std::ifstream;


MapLoader::MapLoader() : Map()
{ 
}

MapLoader MapLoader::loadMap(string fileInput)
{

    MapLoader map;

    string line;
    ifstream fileToRead(fileInput);
    
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

                // [country]
                std::string country = line.substr(2, line.length());
                const int equalsIndex = country.find(" ");
                country = country.substr(0, equalsIndex);
                // [country]

                // [continent number]
                string continentNbStr = line.substr(3, line.length());
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
                int armiesNb=0;
                try {
                    armiesNb = std::stoi(armiesNbStr);
                }
                catch (const std::exception& ex) {
                    cout << "";
                }
                catch (const std::string& ex) {
                    cout << "";
                }
                catch (...) {
                    cout << "";
                }
                //convert string to integer
                
                // [armies]

                // [index]
                std::string indexNbStr = line.substr(2, line.length()); //"Hiiumaa 1 167 172"
                indexNbStr = indexNbStr.substr(indexNbStr.length() - 3, indexNbStr.length());
                if (indexNbStr[0] == ' ')
                {
                    indexNbStr = indexNbStr.substr(0, indexNbStr.length());
                }

                //convert string to integer
                int indexNb=0;
                try {
                    indexNb = std::stoi(indexNbStr);
                }
                catch (const std::exception& ex) {
                    cout << "";
                }
                catch (const std::string& ex) {
                    cout << "";
                }
                catch (...) {
                    cout << "";
                }
                //convert string to integer

                // [index]

                // [add country to unordered map]
                map.addTerritory(country, continentNbStr, armiesNb, indexNb);
                // [add country to unordered map]

                // [Setup edges]
                map.addEdge(country, *map.getTerritory(country));
                // [Setup edges]
            }
            else if (count > 9)
            {
                //country
                std::string country = line.substr(3, line.length());
                const int equalsIndex = country.find(" ");
                country = country.substr(0, equalsIndex);
                //country

                // [continent number]
                string continentNbStr = line.substr(4, line.length());
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
                int armiesNb=0;
                try {
                    armiesNb = std::stoi(armiesNbStr);
                }
                catch (const std::exception& ex) {
                    cout << "";
                }
                catch (const std::string& ex) {
                    cout << "";
                }
                catch (...) {
                    cout << "";
                }
                // [armies]

                // [index]
                std::string indexNbStr = line.substr(2, line.length()); //"Hiiumaa 1 167 172"
                indexNbStr = indexNbStr.substr(indexNbStr.length() - 3, indexNbStr.length());
                if (indexNbStr[0] == ' ')
                {
                    indexNbStr = indexNbStr.substr(0, indexNbStr.length());
                }

                //convert string to integer
                int indexNb=0;
                try {
                    indexNb = std::stoi(indexNbStr);
                }
                catch (const std::exception& ex) {
                    cout << "";
                }
                catch (const std::string& ex) {
                    cout << "";
                }
                catch (...) {
                    cout << "";
                }
                //convert string to integer
                // [index]

                // [add country to unordered map]
                map.addTerritory(country, continentNbStr, armiesNb, indexNb);
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
    fileToRead.seekg(0, fileToRead.beg);

    // [Setup continents]
    map.addTerritoriesToContinents();
    // [Setup continents]

    fileToRead.close();

    return map;
}

MapLoader MapLoader::loadMapAlt(string fileInput)
{
    MapLoader map;

    string line;

    ifstream fileToRead(fileInput);

    if (fileToRead.is_open())
    {
        int count = 1;
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

        while (std::getline(fileToRead, line) && line != "")
        {

            const int equalsIndex = line.find(" ");
            const std::string continent = line.substr(0, equalsIndex);
            const int value = std::stoi(line.substr(equalsIndex + 1));

            // add continentName and nativeArmy
            map.addContinent(continent, value);
            cout << "Continent: " << continent << " Value: " << value << "\n"; //TODO
        }
        cout << "\n"; //TODO

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

        
        while (std::getline(fileToRead, line) && line != "")
        {
            // [country]
            std::string country = line;
            int emptySpace_country1 = country.find(" ");
            emptySpace_country1 = emptySpace_country1 + 1;
            country = country.substr(emptySpace_country1, country.length()-1);
            int emptySpace_country2 = country.find(" ");
            country = country.substr(0, emptySpace_country2);

            cout << country << "\n";

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

            cout << "continentNbStr: " << continentNbStr << "\n"; //TODO
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

            //convert string to integer for 
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
            //convert string to integer
            cout << "Index: " << indexNbStr << "\n"; //TODO

            // [index]


            // [add country to unordered map]
            map.addTerritory(/*country*/"Portugal", /*continentNbStr*/"continentTest", /*armiesNb*/1, /*indexNb*/2);

            // [Setup edges]
           // map.addEdge(country, *map.getTerritory(country));
            // [Setup edges]

        }
         //[Territories]
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

 fileToRead.close();

 return map;


}
