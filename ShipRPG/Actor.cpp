#include "Actor.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//#define ALTERHEALTH(int inc) ((health) + (inc))

int health, fuel, speed, shields, length, atk, x, y;
string parts[];

Actor::Actor(void)
{
	length = 1;
}

//copy and assignment overload
Actor::Actor (Actor& other)
{
	maxHealth = other.maxHealth;
	maxFuel = other.maxFuel;
	health = other.health;
	fuel = other.fuel;
	speed = other.speed;
	shields = other.shields;
	length = other.length;
	atk = other.atk;
}

Actor& Actor::operator=(Actor& other)
{
	maxHealth = other.maxHealth;
	maxFuel = other.maxFuel;
	health = other.health;
	fuel = other.fuel;
	speed = other.speed;
	shields = other.shields;
	length = other.length;
	atk = other.atk;
	return *this;
}

//move vertically
void Actor::vMove(int m)
{
	this->setY(this->getY() + m);
}

//move horizontally
void Actor::hMove(int m)
{
	this->setX(this->getX() + m);
}

//get, set, and alter methods for health, fuel, and shields
int Actor::getHealth(){ return health; }
void Actor::setHealth(int set){ health = set; }

void Actor::alterHealth(int inc)
{
	health += inc;		
}

int Actor::getFuel(){ return fuel; }
void Actor::setFuel(int set){ fuel = set; }
void Actor::alterFuel(int inc)
{
	health += inc;		
}

int Actor::getShields(){return shields;}
void Actor::setShields(int set){ shields = set; }
void Actor::alterShields(int inc)
{
	shields += inc;		
}

//speed
int Actor::getSpeed(){ return speed; }
void Actor::setSpeed(int set){ speed = set; }

/*
//cleanup
void cleanUp()
{
	free(parts);
}
*/

//destructor
Actor::~Actor(void)
{
	//cleanUp();
}
