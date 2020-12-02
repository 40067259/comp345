#include<iostream>
#include<string>
#include"MapLoader.h"
#include"ConquestFileReader.h"
#include"..\GameEngine.h"
#include"..\Map\Map.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {

	cout << "Please choose to use the original reader to read map files, or use the reader Adapter." << endl;
	cout << "Enter 1 to use the original reader or enter 2 to use the reader Adapter." << endl;
	cout << "Enter 0 to exist." << endl;
	int option;
	cin >> option;
	while (option != 1 && option != 2 && option != 0) {
		cout << "Wrong option. Enter 0, 1 or 2 ." << endl;
		cin >> option;
	}
	if (option == 0) { return 0; }

	while (option!=0) {

		if (option == 1) {
			cout << "Use original maploader to load a map." << endl;
			// The GameEngine use the origianl maploader to load a map
			GameEngine *game = new GameEngine();
			game->mapSelection();
		}
		else {
			cout << "Use reader Adapter to load a conquest map." << endl;
			// get a list of maps from "/path/to/directory";
			string path1 = "test_maps";
			// print a list of maps
			cout << "Choose a map from the list below by entering the map's name (e.g. Aden.map)" << std::endl;
			for (auto& entry : std::experimental::filesystem::directory_iterator(path1))  // for c++14
			//for (auto& entry : std::filesystem::directory_iterator(path1))  // for c++17	
			{
				cout << entry.path().filename() << endl;
			}

			string selectedMap = "";
			//Get input from the user for the map name
			cin >> selectedMap;

			// check if the file exists
			bool exists = false;

			for (auto& entry : std::experimental::filesystem::directory_iterator(path1)) // for c++14
			//for (auto& entry : std::filesystem::directory_iterator(path1)) // for c++17
			{
				if (entry.path().filename() == selectedMap) {
					exists = true;
				}
			}
			while (!exists)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Please enter a valid map name" << endl;
				cin >> selectedMap;
				for (auto& entry : std::experimental::filesystem::directory_iterator(path1)) // for c++14
				//for (auto& entry : std::filesystem::directory_iterator(path1)) // for c++17	
				{
					if (entry.path().filename() == selectedMap) {
						exists = true;
					}
				}
			}

			// try to load a map and check map validity
			ConquestFileReader *conquestLoader = new ConquestFileReader();
			string path2 = path1 + "\\" + selectedMap;
			cout << path2;

			// Use adapter to read conquest map file
			ConquestFileReaderAdapter *adapter = new ConquestFileReaderAdapter(*conquestLoader);
			adapter->loadMap(path2);

		}

		cout << endl << endl ;
		cout << "Enter 1 to use the original reader or enter 2 to use the reader Adapter." << endl;
		cout << "Enter 0 to exist." << endl;
		cin >> option;
	}
}