#include "Actor.h"
#include "Upgrade.h"
#include "Player.h"
#include "Room.h"
#include "Combat.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

//color stuff
#include <conio.h> 

//defines
#define STATS stats()

//stuff that lets the window resize
#define _WIN32_WINNT 0x0500
#include <Windows.h>

using namespace std;

Player p1;
Room rm;
Combat cm;
Upgrade ug;
Enemy en;

//vector that will store all filenames for enemies in one convenient location
vector<string> enFiles;

//populate enFiles with Enemy files
void EnemyLib()
{
	fstream file("Enemies.txt");
	
	//I won't be making any text files with a name that ridiculously long
	//char limit [128];
	string line;

	//if there is something in that line
	while (file.good()){
		//add line to enFiles
		getline(file, line);
		enFiles.push_back(line);
	}
	file.close();
}

//display player stats -- Now with a try catch
void stats()
{
	//make sure stats are defined
	try {
		if (p1.health == NULL) throw("\nSome stats are not defined");
		cout << "Health: " << p1.health << "\n";
		if (p1.shields == NULL) throw("\nSome stats are not defined");
		cout << "Shields: " << p1.shields << "\n";
		if (p1.fuel == NULL) throw("\nSome stats are not defined");
		cout << "Fuel: " << p1.fuel << "\n";
		if (p1.speed == NULL) throw("\nSome stats are not defined");
		cout << "Speed: " << p1.speed << "\n";
		if (p1.credits == NULL){
			p1.credits = 0;
		}
		cout << "Credits: " << p1.credits << "\n";
	}
	catch(string e){
		cout << e << "/n";
	}

}

//randomly pick an enemy type from vector
void EnemySelect()
{
	//create a new vector to re-arrange
	vector <string> enSel;
	enSel.resize(enFiles.size()); //re-size enSel to fit enFiles' values
	
	//use copy algorithm to copy contents of enFiles to enSel
	copy (enFiles.begin(), enFiles.end(), enSel.begin()); //copy seems to be working now

	//algorithm: random shuffle
	random_shuffle(enSel.begin(), enSel.end()); //random shuffle is working;

	//build enemy using random shuffle
	en.buildEnemy(enSel[0]); //since the enemy order is rearranged, print out first enemy
}

void SaveData(){
	ofstream file ("Save.sav");
	if (file.is_open()){
		file << p1.health << "\n";
		file << p1.shields << "\n";
		file << p1.fuel << "\n";
		file << p1.speed << "\n";
		file << p1.credits <<"\n";
		file << p1.getX() << "\n";
		file << p1.getY() << "\n";
		file.close();
		cout << "File saved!\n";
	}
	else{
		cout << "Error saving.\n";
	}
}

void LoadData(){
	int input = 0, j = 0;
	ifstream file ("Save.sav");
	if (file.is_open()) {
		while (file.good()){
			file >> input;
			
			switch(j){
				case 0:
					p1.health = input;
					j++;
					break;
				case 1:
					p1.shields = input;
					j++;
					break;
				case 2:
					p1.fuel = input;
					j++;
					break;
				case 3:
					p1.speed = input;
					j++;
					break;
				case 4:
					p1.credits = input;
					j++;
					break;
				case 5:
					p1.setX(input);
					j++;
					break;
				case 6:
					p1.setY(input);
					j++;
					break;
			}
		}
		file.close();
	}
    else {
		cout << "Save file doesn't exist\n";
    }
}

void combatStart()
{
	bool done = false;

	//select opponent
	EnemySelect();
	cm.getCombatants(&p1, &en);
	//cm.fillMob("Enemies.txt");
	//cm.getCombatants(&p1, ens);
	
	cm.fightyTime();
	cout << "Combat has ended!\n";
	en.setDefault();
}

void test()
{
	ifstream file ("testRM.txt");
	file.getloc();
	string rmNum;
	
	char r = file.get();
	
	while(rmNum == "#Room:" || rmNum.empty()){
		getline(file, rmNum);
		if(rmNum.find('^')){
			rmNum.erase(rmNum.end()-1, rmNum.end());
			cout << rmNum << endl;
			file.close();
			break;
		}
	}
	file.close();
}

//take player input (easier as its own method than putting it in main)
void getCommands()
{
	string input;

	//the point of while true, in this case, is that the game does not end until the player ends it
	while(true){
		system("CLS");
		rm.lookRoom();
		cout << "Health: " << p1.health << " | Shields: " << p1.shields << " | Credits: " << p1.credits << "\n\n";

		cout << "Legend:\n"
		<< " @.................player\n"
		<< " *.................space debris, blocks a space\n"
		<< " $.................credits\n"
		<< " X.................enemy\n"
		<< " N S E W...........exits\n";

		cout << "What do you do next? (type list to see a list of commands)\n";
		cin >> input;
		//signed vs unsigned fix
		for (size_t i = 0, length = input.size(); i < length; ++i){
			input[i] = tolower(input[i]);
		}
		
		if (input == "save"){
			SaveData();
		}
		if (input == "load"){
			LoadData();
		}
		if (input == "pause"){
			cout << "Game Paused\n";
			system("PAUSE");
		}

		//movement
		if (input == "w"){
			rm.pMove('w', cm, p1, en);
		}
		if (input == "s"){
			rm.pMove('s', cm, p1, en);
		}
		if (input == "a"){
			rm.pMove('a', cm, p1, en);
		}
		if (input == "d"){
			rm.pMove('d', cm, p1, en);
		}

		//check inventory
		if (input == "inv" || input == "inventory"){
			p1.lookInv();
		}

		//heal and repair
		if (input == "heal" || input == "repair"){
			p1.heal();
		}
		//upgrade test
		if(input == "ug"){
			ug.makeUpgrade("upChitinousPlating.txt");
		}

		//test adding things to inventory
		if(input == "testitem"){
			p1.addInv("upChitinousPlating.txt");
		}

		//show status
		if(input == "status" || input == "stats"){
			STATS;
			system("PAUSE");
		}
		//look at room, activate events, etc
		if (input == "look"){
			rm.lookRoom();
			system("PAUSE");
		}
		//test run
		if(input == "test"){
			//rm.findRoom(rm.label);
		}
		if (input == "explore"){
			combatStart();
		}

		if (input == "quit"){
			cout << "End game(y/n)?\n"; 
			cin >> input;
			if (input == "yes" || input == "y"){
				cout << "Would you like to save before you go(y/n)?\n";
				cin >> input;
				if (input == "yes" || input == "y"){
					SaveData();
				}
				break;
			}
		}

		if (input == "list"){
			cout << "\nCommands:\n"
				<< " w.................moves ship forwards a specified number of units\n"
				<< " s.................moves ship backwards a specified number of units\n"
				<< " a.................moves ship left a specified number of units\n"
				<< " d.................moves ship right a specified number of units\n"
				<< " status/stats......returns ship status\n"
				<< " look..............look at room\n"
				<< " heal/repair.......restore health\n"
				<< " explore...........look for ships to \"salvage\"\n"
				<< " save..............saves game\n"
				<< " load..............loads game\n"
				<< " pause.............pauses game\n"
				<< " quit..............exits game\n";
			system("PAUSE");
		}
	}
}

void startMenu()
{
	string input, line;

	fstream file("Title.txt");
	while (file.good()){
		getline(file, line);
		cout << line << "\n";
	}
	file.close();
	system("PAUSE");
	cout << "\n";

	while(true){
		fstream file("Story.txt");
		while (file.good()){
			getline(file, line);
			cout << line << "\n";
		}
		file.close();
		
		cout << "\nType \"new\" to start a new game, or \"load\" to restore a saved game.\n";
		cin >> input;
		if (input == "new"){
			cout << "Enter save file name: " << endl;
			cin >> input;
			fstream file(input + ".sav");

			while (file.good()){
				int temp;
				file >> p1.health;
				file >> p1.shields;
				file >> p1.fuel;
				file >> p1.speed;
				file >> p1.credits;
				temp = p1.getX();
				file >> temp;
				temp = p1.getY();
				file >> temp;
			}
			file.close();
			break;
		}
		else if (input == "load"){
			LoadData();
			break;
		}
	}
}

void main()
{
	//re-size window
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	//should change color of text - 2 is green
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

	MoveWindow(console, r.left, r.top, 1500, 800, true);

	startMenu();

	//set up room
	if (rm.mapPart.label == ""){
		rm.mapPart.label = "Rm1Original.txt";
	}
	rm.makeRoom(p1);

	//set up enemy library
	EnemyLib();
	//en.enemyLib();

	LoadData();
	getCommands();
}
	
