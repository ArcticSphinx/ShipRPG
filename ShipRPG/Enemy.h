#include "Actor.h"
#include <fstream>
#include <vector>
#include <algorithm>

#pragma once
class Enemy : virtual public Actor
{
public:
	//vector that will store all filenames for enemies in one convenient location
	vector<string> enFiles;

	Enemy(void);
	//copy constructor and assignment operator
	Enemy (const Enemy& other);
	Enemy& operator=(const Enemy& other);
	
	void enemyLib();
	void buildEnemy(string enStats);
	void setDefault();
	void enemySelect();

	bool EnCheck();

	~Enemy(void);
};

