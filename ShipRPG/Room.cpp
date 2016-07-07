#include "Room.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Enemy.h"
#include "Combat.h"
#include <string>
#include <Windows.h>
using namespace std;

//color stuff
#include <conio.h>

//define for player symbol
#define pSYM '@'

Room::Room(void)
{
}

Room::Room (const Room& other)
{
	rmIDX = other.rmIDX;
	rmIDY = other.rmIDY;
	eventNum = other.eventNum;
	mapPart.label = other.mapPart.label;
	mapPart.desc = other.mapPart.desc;
	mapPart.w = other.mapPart.w;
	mapPart.a = other.mapPart.a;
	mapPart.s = other.mapPart.s;
	mapPart.d = other.mapPart.d;
}

Room& Room::operator=(const Room& other)
{
	rmIDX = other.rmIDX;
	rmIDY = other.rmIDY;
	eventNum = other.eventNum;
	mapPart.label = other.mapPart.label;
	mapPart.desc = other.mapPart.desc;
	mapPart.w = other.mapPart.w;
	mapPart.a = other.mapPart.a;
	mapPart.s = other.mapPart.s;
	mapPart.d = other.mapPart.d;
	return *this;
}

void Room::makeRoom(Player& p)
{
	fstream file(mapPart.label);
	string line, sub;

	while (file.good()){
		getline(file, line);

		for (size_t i = 0, length = line.size(); i < length; ++i){
			sub = line.substr(i, 1);
			mapPart.mapArray[row][i] = sub;
		}
		row++;
	}
	mapPart.mapArray[p.getX()][p.getY()] = pSYM;
	file.close();
	
	if(mapPart.label == "Rm1Original")
		mapPart.label = "Rm1.txt";
	if(mapPart.label == "Rm2Original")
		mapPart.label = "Rm2.txt";
	if(mapPart.label == "Rm3Original")
		mapPart.label = "Rm3.txt";
}

void Room::lookRoom()
{
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 69; j++){
			cout << mapPart.mapArray[i][j]; //print row
		}
		cout << "\n"; //go to next row
	}
}

//populate Set up list of maps
void Room::mapLib()
{
	fstream file("Maps.txt");
	
	//I won't be making any text files with a name that ridiculously long
	//char limit [128];
	string line;

	//if there is something in that line
	while (file.good()){
		//add line to enFiles
		getline(file, line);
		maps.push_back(line);
	}
	file.close();
}

void Room::combatStart(Combat& c, Player& p, Enemy& e)
{
	//bool done = false;
	//cout << "combat called" << endl;
	//select opponent
	e.enemySelect();
	//cout << "enemy select OK" << endl;

	c.getCombatants(&p, &e);
	//cout << "getCombatants OK" << endl;

	//cm.fillMob("Enemies.txt");
	//cm.getCombatants(&p1, ens);
	
	c.fightyTime();
	//cout << "Fight OK" << endl;

	cout << "Combat has ended!\n";
	e.setDefault();
}

//save room for the player to come back to
void Room::saveRoom()
{
	fstream file(mapPart.label);
	string line;

	while (file.good()){
		for (size_t i = 0, length = 30; i < length; ++i){
			for (size_t j = 0, length = 69; j < length; ++j){
				file >> mapPart.mapArray[i][j];
			}
		}
		row++;
	}
	file.close();
}

//move player
void Room::pMove(char direction, Combat& c, Player& p, Enemy& e)
{
	fstream file (mapPart.label);
	switch (direction){
		case 'w':
			//change values in array
			if (mapPart.mapArray[(p.getX() - 1)][p.getY()] != "*"){
				checkExits(p);
				//is it an enemy encounter?
				if (mapPart.mapArray[(p.getX() - 1)][p.getY()] == "X"){
					cout << "You ran into an enemy!\n";	
					combatStart(c, p, e);
				}
				if (mapPart.mapArray[(p.getX() - 1)][p.getY()] == "$"){
					p.credits += 100;
				}
				//the char at p.x in the line at p.y is replaced by a blank space
				if(mapPart.mapArray[p.getX()][(p.getY() - 1)] != "N" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "S" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "E" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "W")
				{
					mapPart.mapArray[p.getX()][p.getY()] = " ";
				}
				//increment p.y -- lower = up
				p.setX((p.getX() - 1));
				mapPart.mapArray[p.getX()][p.getY()] = pSYM;
			}
			break;
		case 's':	
			if (mapPart.mapArray[(p.getX() + 1)][p.getY()] != "*"){
				checkExits(p);
				//is it an enemy encounter?
				if (mapPart.mapArray[(p.getX() + 1)][p.getY()] == "X"){
					cout << "You ran into an enemy!\n";
					combatStart(c, p, e);
				}
				if (mapPart.mapArray[(p.getX() + 1)][p.getY()] == "$"){
					p.credits += 100;
				}
				//the char at p.x in the line at p.y is replaced by a blank space
				if(mapPart.mapArray[p.getX()][(p.getY() - 1)] != "N" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "S" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "E" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "W")
				{
					mapPart.mapArray[p.getX()][p.getY()] = " ";
				}
				//decrement p.y -- higher = down
				p.setX((p.getX() + 1));
				mapPart.mapArray[p.getX()][p.getY()] = pSYM;
			}
			break;
		case 'd':
			if (mapPart.mapArray[p.getX()][(p.getY() + 1)] != "*"){
				checkExits(p);
				if (mapPart.mapArray[p.getX()][(p.getY() + 1)] == "X"){
					cout << "You ran into an enemy!\n";
					combatStart(c, p, e);
				}
				if (mapPart.mapArray[p.getX()][(p.getY() + 1)] == "$"){
					p.credits += 100;
				}
				//the char at p.x in the line at p.y is replaced by a blank space
				if(mapPart.mapArray[p.getX()][(p.getY() - 1)] != "N" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "S" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "E" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "W")
				{
					mapPart.mapArray[p.getX()][p.getY()] = " ";
				}
				//increment p.y
				p.setY((p.getY() + 1));
				mapPart.mapArray[p.getX()][p.getY()] = pSYM;
			}
			break;
		case 'a':
			if (mapPart.mapArray[p.getX()][(p.getY() - 1)] != "*"){
				checkExits(p);
				if (mapPart.mapArray[p.getX()][(p.getY() - 1)] == "X"){
					cout << "You ran into an enemy!\n";
					combatStart(c, p, e);
				}
				if (mapPart.mapArray[p.getX()][(p.getY() - 1)] == "$"){
					p.credits += 100;
				}
				//the char at p.x in the line at p.y is replaced by a blank space
				if(mapPart.mapArray[p.getX()][(p.getY() - 1)] != "N" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "S" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "E" && mapPart.mapArray[p.getX()][(p.getY() - 1)] != "W")
				{
					mapPart.mapArray[p.getX()][p.getY()] = " ";
				}
				//decrement p.y
				p.setY((p.getY() - 1));
				mapPart.mapArray[p.getX()][p.getY()] = pSYM;
			}
			break;
		default:
			break;
	}
}

void Room::checkExits(Player& p)
{
	if(mapPart.mapArray[(p.getX() - 1)][p.getY()] == "N"){
		if(mapPart.label == "Rm1.txt"){
			mapPart.label = "Rm3Original.txt";
			makeRoom(p);
			system("CLS");
			cout << "Moving north...\n";
			system("PAUSE");
		}	
	}
	if(mapPart.mapArray[(p.getX() - 1)][p.getY()] == "S"){
		if(mapPart.label == "Rm3.txt"){
			mapPart.label = "Rm1Original.txt";
			makeRoom(p);
			system("CLS");
			cout << "Moving south...\n";
			system("PAUSE");
		}	
	}
	if(mapPart.mapArray[(p.getX() - 1)][p.getY()] == "E"){
		if(mapPart.label == "Rm2.txt"){
			mapPart.label = "Rm1Original.txt";
			makeRoom(p);
			system("CLS");
			cout << "Moving east...\n";
			system("PAUSE");
		}	
	}
	if(mapPart.mapArray[(p.getX() - 1)][p.getY()] == "W"){
		if(mapPart.label == "Rm1.txt"){
			mapPart.label = "Rm2Original.txt";
			makeRoom(p);
			system("CLS");
			cout << "Moving west...\n";
			system("PAUSE");
		}
	}
}

void Room::mapChange(int id)
{
	//make a room
	//makeRoom(maps[id]);
	mapPart.label = maps[id];
}

Room::~Room(void)
{
}
