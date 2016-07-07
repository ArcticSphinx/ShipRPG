#include "Combat.h"
#include "Actor.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>
#include <WinBase.h>

Combat::Combat()
{
}

Combat::Combat(const Combat& other)
{
	player = other.player;
	enemy = other.enemy;
	mob = other.mob;
}

Combat& Combat::operator=(const Combat& other)
{
	player = other.player;
	enemy = other.enemy;
	mob = other.mob;
	return *this;
}

//fill vector with txt files for enemies
void Combat::fillMob(string str)
{
	ifstream file (str);
	string line;
	int numLines;
	
	//first number in file will be a number
	numLines = file.get();

	for (int i = 1; i < numLines; i++){
		getline(file, line);
		
		//read anything that is not the number
		if(line.size() > 1){
			//mob[i] = line;
		}
	}
	file.close();
}

void Combat::getCombatants(Player* pl, Enemy* en)
{
	//cout << "A new challenger has appeared!!!\n";
	enemy = en;
	player = pl;
	//fightyTime();
}

void Combat::getCombatants(Player* pl, string en)
{
	//cout << "A new challenger has appeared!!!\n";
	enemy->buildEnemy("enSkiff.txt");
	player = pl;
	//fightyTime();
}

void Combat::getCombatants(Player* pl, vector<string> en)
{
	//string to hold stuff
	//char quant;
	//string file;
	
	//run through loop for each string passed in
	/*
	for(int i = 0; i < en.size(); i++)
	{
		//since strings are arrays, I am looking for the first character in en[i], which will be a number no greater than 9
		quant = en[i][0]; //number of ships of a certain type -- we won't bother with double digits, as that would be insane
		
		for(int j = 0; j < (int)quant; j++)
		{
			file = en[i].substr(1, en[i].size()); //type of ship to create
			enemy->buildEnemy(file);
			mob[i] = *enemy;
		}
	//}
	*/
	/*
	//run through ints as long as there are ship types to assign them to
	for(int i = 0; i < mob.size(); i++)
	{
		//make instances of the ship equal to the int at en[i]
		for(int j = 0; j < en[i]; j++)
		{
			//at i = 0, you build the enemy type at mob[0]...
			enemy->buildEnemy(mob[i]);
		}
	}
	*/

	//make the player
	//player = pl;
}

//combat function
void Combat::fightyTime()
{
	cout << "Fight!\n";
	//figure out who goes first
	if(enemy->getSpeed() > player->getSpeed()){
		cout << "Enemy goes first.\n";
		enemyTurn();
	}
	else{
		//player wins ties
		cout << "Player goes first.\n";
	}
	playerTurn();
}

//reduce target's health
void Combat::playerAttack(Player p, Enemy* target)
{
	target->health -= 10 + p.atk;
	cout << "Enemy takes damage!\n";
}

void Combat::enemyAttack(Enemy e, Player* target)
{
	target->health -= 10 + e.atk;
	cout << "The enemy opens fire!\n";
}

void Combat::playerTurn()
{
	while(player->getHealth() > 0 &&  enemy ->getHealth() > 0){
		//combat prompt
		bool done = false;
		while(!done){
			string input = "";
			int cmdNum = -1;
			done = true;
			
			while (true){
				getline(cin, input);
				stringstream flow(input);
			
				if (flow >> cmdNum){
					break;
				}
				else{
					cout << "Your health: " << player->getHealth() << "\n";
					cout << "Enemy health: " << enemy->getHealth() << "\n";
					cout << "Player turn, enter a command:\n";
					cout << " 0) Pass turn\n"
						 << " 1) Basic attack: Bite\n"
						 << " 2) Repair\n";
				}
			}

			switch(cmdNum){
				//do nothing: you passed your turn
				case 0:
					cout << "You just sit there and do nothing. WHY ARE YOU DOING NOTHING!!!???\n";
					Beep(700, 500);
					break;
				case 1:
					playerAttack(*player, enemy);
					cout << "You bite into the enemy! OM NOM NOM NOM!\n";
					break;
				//repair
				case 2:
					Beep(700, 500);

					 //if you have the credits, you can heal mid-battle.
					if(!player->heal()){
						//don't end player's turn if he/she can't heal or changes his/her mind
						done = false;
					}
					break;
				default:
					cout << "\nInvalid input, try again.\n";
					done = false;
					break;	
			}
		}
		enemyTurn();
		cout << "Your health: " << player->getHealth() << "\n";
		cout << "Enemy health: " << enemy->getHealth() << "\n";
	}
	//pay player with credits if he/she won
	if (player->getHealth() <=0){
		cout << "You have been defeated!\n";
		cout << "You lose " << enemy->credits << " credits!\n";
	}
	if (enemy ->getHealth() <= 0){
		cout << "You acquire " << enemy->credits << " credits!\n";
		player->credits += enemy->credits;

		//currently, heal after every battle -- enemies may be a bit too difficult without this
		player->alterHealth((player->maxHealth)/2);
	}
}

void Combat::enemyTurn()
{
	enemyAttack(*enemy, player);
}

Combat::~Combat(void)
{
}
