#include "Player.h"
#include "Enemy.h"
#include <fstream>
#include <vector>

#pragma once
class Combat
{
public:
	Player* player;
	Enemy* enemy;

	//makin' a vector to hold many enemies so you can EAT ALL THE SHIPS!
	vector<Enemy> mob;
	Combat();

	//copy constructor and assignment operator
	Combat(const Combat& other);
	Combat& operator=(const Combat& other);

	void fillMob(string str);

	void getCombatants(Player* pl, Enemy* en);
	void getCombatants(Player* pl, string en);

	//seriously, if you wanted, you could probably make more ships than the Young Justice fandom
	void getCombatants(Player* pl, vector<string> en);

	void fightyTime();

	void playerTurn();
	void enemyTurn();
	
	void playerAttack(Player p, Enemy* target);
	void enemyAttack(Enemy e, Player* target);

	~Combat(void);
};

