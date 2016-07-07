#include "Actor.h"
#include "Upgrade.h"
#include <iostream>
#include <fstream>
#include <queue>
#include "Thing.h"
using namespace std;

#pragma once
class Player : virtual public Actor
{
private:
	int x, y;

public:
	//inventory of upgrades
	queue<Upgrade> inventory;
	queue<Upgrade> equipment;

	Player(void);
	
	//copy const and assignment operator
	Player (const Player& other);
	Player& operator=(const Player& other);

	//overloading + and - operator for equipment
	void operator +(const Upgrade& other);
	void operator -(const Upgrade& other);
	void operator *();

	//get location
	int getX();
	int getY();

	//set location
	void setX(int n);
	void setY(int n);

	void addInv(string str); //add an upgrade to inventory
	void dropInv(Upgrade& u); //remove an item from inventory

	void lookInv(); //look at inventory
	
	void equip(Upgrade u); //equip upgrade to player
	void unequip(Upgrade u);

	void SaveData();
	void alterHealth(int inc);
	bool heal(); //heal player

	~Player(void);
};

