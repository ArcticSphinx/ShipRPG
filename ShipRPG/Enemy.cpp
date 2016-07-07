#include "Enemy.h"
#include <fstream>
#include <vector>
#include <algorithm>

#define ENEMY_LIBRARY_EMPTY true
#define LIBRARY_OK false


Enemy::Enemy(void)
{
	enemyLib();
}

bool Enemy::EnCheck()
{
	if(enFiles.empty()){
		return ENEMY_LIBRARY_EMPTY;
	}
	else{
		return LIBRARY_OK;
	}
}

Enemy::Enemy (const Enemy& other)
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

//you can copy enemies
Enemy& Enemy::operator=(const Enemy& other)
{
	health = other.health;
	shields = other.shields;
	fuel = other.fuel;
	speed = other.speed;
	return *this;
}

//populate enFiles with Enemy files
void Enemy::enemyLib()
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

//constructor that reads in stuff from file
void Enemy::buildEnemy(string enStats)
{
	int input = 0, j = 0;
	ifstream file (enStats);
	if (file.is_open()){
		while (file.good()){
			file >> input;

			switch(j){
				case 0:
					health = input;
					j++;
					break;
				case 1:
					shields = input;
					j++;
					break;
				case 2:
					fuel = input;
					j++;
					break;
				case 3:
					speed = input;
					j++;
					break;
				case 4:
					credits = input;
					j++;
				default:
					break;
			}
		}
		file.close();
	}
	cout << "An enemy vessel has appeared!\n";
}

void Enemy::setDefault()
{
	health = 80;
	shields = 40;
	fuel = 100;
	speed = 2;
}

//randomly pick an enemy type from vector
void Enemy::enemySelect()
{
	//cout << "enemy select called\n"; //yes

	if(EnCheck() == ENEMY_LIBRARY_EMPTY){
		cout << "\nEnemy library is empty!!!\n" << endl;
		return;
	}

	//create a new vector to re-arrange
	vector <string> enSel;
	enSel.resize(enFiles.size()); //re-size enSel to fit enFiles' values
	//cout << "resize works" << endl;

	//use copy algorithm to copy contents of enFiles to enSel
	copy (enFiles.begin(), enFiles.end(), enSel.begin()); //copy seems to be working now
	//cout << "copy works" << endl;

	//algorithm: random shuffle
	random_shuffle(enSel.begin(), enSel.end()); //random shuffle is working;
	//cout << "shuffle works" << endl;

	//build enemy using random shuffle
	buildEnemy(enSel[0]); //since the enemy order is rearranged, print out first enemy
	//cout << "enemy built" << endl;
}

Enemy::~Enemy(void)
{
}
