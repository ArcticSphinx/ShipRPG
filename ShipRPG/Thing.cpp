#include "Thing.h"
#include <string>
#include <istream>
using namespace std;

Thing::Thing(void)
{
}

void Thing::makeThing(int x, int y, int col)
{
	x = x;
	y = y;
	color = color;
}

Thing::Thing(const Thing& other)
{
	this->x = x;
	this->y = y;
	this->color = color;
}

Thing& Thing::operator=(const Thing& other)
{
	this->x = x;
	this->y = y;
	this->color = color;
	return *this;
}

//get methods for things on map
int Thing::getX()
{
	return x;
}

int Thing::getY()
{
	return y;
}

int Thing::getColor()
{
	return color;
}

//set methods for things on map
void Thing::setX(int n)
{
	x = n;
}

void Thing::setY(int n)
{
	y = n;
}

void Thing::setColor(int n)
{
	color = n;
}

Thing::~Thing(void)
{
}
