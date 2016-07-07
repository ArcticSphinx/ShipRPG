#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Combat.h"
#include "Enemy.h"
#include "Player.h"
using namespace std;

//color stuff
#include <conio.h> 

#pragma once
class Room
{
public:
	struct map{
		//label is the name of the text file
		string label, desc, w, a, s, d;
		//map stored in 2D array
		string mapArray[71][71];
	}mapPart;

	int rmIDX, rmIDY, eventNum, row;
	
	//make a set to hold map files
	vector<string> maps;
	vector<string> mapFixer;

	Room(void);

	//copy constructor and assignment overload operator
	Room(const Room& other);
	Room& operator=(const Room& other); 

	void makeRoom(Player& p);

	void lookRoom(); //looks at room
	void findRoom(string room); //finds location of room
	void makeRoom(Player& p, int idx, int idy);

	void mapLib();
	void mapChange(int id);

	void saveRoom();
	void pMove(char direction, Combat& C, Player& p, Enemy& e);
	void checkExits(Player& p);
	void combatStart(Combat& c, Player& p, Enemy& e);

	~Room(void);
};

