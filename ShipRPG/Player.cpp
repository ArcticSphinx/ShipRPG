#include "Player.h"
#include "Upgrade.h"
#include <ostream>
#include "Thing.h"
using namespace std;

//default constructor
Player::Player(void)
{
	maxHealth = 100;
	health = 100;
	shields = 50;
	fuel = 100;
	speed = 3;
	atk = 1;
	setX(50);
	setY(30);
	this->setColor(4);
}

//copy and assignment overload
Player::Player (const Player& other)
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

Player& Player::operator=(const Player& other)
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

//add item to inventory
void Player::addInv(string str)
{
	Upgrade u;
	u.makeUpgrade(str);
	inventory.push(u);
}

//add item stats to player
void Player::equip(Upgrade u)
{
	equipment.push(u);
	u.equipped = true;

	maxHealth += u.health;
	shields += u.shields;
	maxFuel += u.fuel;
	speed += u.speed;
	atk += u.atk;
}

void Player::unequip(Upgrade u)
{
	equipment.pop();
	u.equipped = false;

	maxHealth -= u.health;
	shields -= u.shields;
	maxFuel -= u.fuel;
	speed -= u.speed;
	atk -= u.atk;
}

//overloading + operator for equipment (quick-equip)
void Player::operator +(const Upgrade& other)
{
	equip(other);
}

//overloading - operator for quick unequipping
void Player::operator -(const Upgrade& other)
{
	unequip(other);
}

//quick heal
void Player::operator *()
{
	heal();
}

void Player::lookInv()
{
	queue<string> in;
	//temporary queue
	queue<Upgrade> temp = inventory;
	Upgrade u;

	//show contents of inventory
	cout << "---Inventory---\n";

	if(temp.size() == 0){
		cout << "EMPTY\n";
	}
	else{
		//signed vs unsigned fix found on stack overflow
		//http://stackoverflow.com/questions/7443222/how-do-i-deal-with-signed-unsigned-mismatch-warnings-c4018
		for (size_t i = 0, length = temp.size(); i < length; ++i){
			//show contents of inventory
			cout << i+1 << ") " << temp.front().name << "\n";
			temp.pop();
		}
	}

	cout << "Enter the slot number of an upgrade to equip it, or type \"q\" to quit.\n";

	string input;
	cin >> input;
	//ignore capitals in input
	for (size_t i = 0, length = input.size(); i < length; ++i){
		input[i] = tolower(input[i]);
	}
}

//actor changehealth
void Player::alterHealth(int inc)
{
	dynamic_cast<Actor*>(this);

	if(health > maxHealth){
		this->alterHealth(maxHealth);
	}
	//fix health if it doesn't work the first time
	if(health != maxHealth)
	{
		health = maxHealth;
	}

}

//heal player for money - bool is used for combat
bool Player::heal()
{
	string input;
	if (credits >= 200){
		cout << "Would you like to consume 200 credits to repair yourself?(y/n)\n";
		
		cin >> input;
		//ignore capitals in input
		//signed vs unsigned fix
		for (size_t i = 0, length = input.size(); i < length; ++i){
			input[i] = tolower(input[i]);
		}

		if (input == "yes" || input == "y"){
			//only do this if player is not at max health
			if(health != maxHealth){
				alterHealth(maxHealth);
				credits -= 200;
				cout << "Om nom nom credits!\n";
				cout << "Health: " << health << "\n";
				cout << "Credits remaining: " << credits << "\n";
				system("PAUSE");
				return true;
			}
			else{
				cout << "You are already as healthy as you can be.\n";
				return false;
			}
		}
		else if (input == "no" || input == "n"){
			cout << "Operation cancelled.\n";
			return false;
		}
		else{
			cout << "Invalid response.\n";
			heal();
		}
	}
	else{
		cout << "Insufficient Credits.\n";
		return false;
	}
	return false;
}

//get methods for things on map
int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

//set methods for things on map
void Player::setX(int n)
{
	x = n;
}

void Player::setY(int n)
{
	y = n;
}

Player::~Player()
{}