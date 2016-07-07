#include "Upgrade.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Upgrade::Upgrade(void)
{
}

Upgrade::Upgrade(const Upgrade& other)
{
	name = other.name;
	health = other.health;
	shields = other.shields;
	fuel = other.fuel;
	speed = other.speed;
	atk = other.atk;
}

Upgrade::Upgrade(string str)
{
	makeUpgrade(str);
}

Upgrade& Upgrade::operator=(const Upgrade& other)
{
	name = other.name;
	health = other.health;
	shields = other.shields;
	fuel = other.fuel;
	speed = other.speed;
	atk = other.atk;
	return *this;
}

void Upgrade::makeUpgrade(string str)
{
	int input = 0, j = 0;
	string line;

	ifstream file(str);
	if (file.is_open()){
		while (file.good()){
			switch(j){
				case 0:
					file >> line;
					name = line;
					j++;
					break;
				case 1:
					file >> input;
					health = input;
					j++;
					break;
				case 2:
					file >> input;
					shields = input;
					j++;
					break;
				case 3:
					file >> input;
					fuel = input;
					j++;
					break;
				case 4:
					file >> input;
					speed = input;
					j++;
					break;
				case 5:
					file >> input;
					atk = input;
					j++;
					break;
			}
		}
		file.close();

		cout << name << " obtained!\n";
		if (health > 0){
			cout << "Health +" << health << "\n";
		}
		if (shields > 0){
			cout << "Shields +" << shields << "\n";
		}
		if (fuel > 0){
			cout << "Fuel +" << fuel << "\n";
		}
		if (speed > 0){
			cout << "Speed +" << speed << "\n";
		}
		if (atk > 0){
			cout << "Attack +" << atk << "\n";
		}
	}
}

Upgrade::~Upgrade(void)
{
}
