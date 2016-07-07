#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "Thing.h"
using namespace std;

//class for all characters that will have health and fuel
#pragma once
class Actor : public Thing
{
public:
	//stuff that actors have
	int  maxHealth, maxFuel;
	int health, fuel, speed, shields, credits, length, atk;
	
	Actor(void);
	//copy and assignment overload
	Actor(Actor& other);
	Actor& operator=(Actor& other);

	//move vertically
	void vMove(int m);
	//move horizontally
	void hMove(int m);

	int getHealth();
	void setHealth(int set);
	void alterHealth(int inc);

	int getFuel();
	void setFuel(int set);
	virtual void alterFuel(int inc);

	int getShields();
	void setShields(int set);
	virtual void alterShields(int inc);

	int getSpeed();
	void setSpeed(int set);

	//add parts to ships
	void addPart(string p);
	void printParts();

	//Combat AI
	void hit(int chance[]);

	//cleanup
	//void cleanUp();

	~Actor(void);
};

