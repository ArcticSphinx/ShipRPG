//A class that each upgrade will inherit from.
//Player should be able to access/take upgrades so that we can track what upgrades a player has
//Upgrades should be able to affect the player in different ways, so doing making them this way seems like it will make implementing them easier.
#include <fstream>
#include <string>
using namespace std;

#pragma once
class Upgrade
{
public:
	//upgrade acts as equipment
	bool equipped;
	int health, fuel, speed, shields, atk;
	string name;
	
	Upgrade(void);
	Upgrade(const Upgrade& other);
	Upgrade(string str);
	Upgrade& operator=(const Upgrade& other);

	void makeUpgrade(string str);

	~Upgrade(void);
};

