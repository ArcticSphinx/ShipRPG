#include <string>
using namespace std;

#ifndef Thing_H
#define Thing_H

#pragma once
class Thing
{
//position and color of symbol on map
protected:
	int x, y, color;

public:
	Thing(void);

	//copy constructor and assignment operator
	Thing(const Thing& other);
	Thing& operator=(const Thing& other);

	~Thing(void);

	void makeThing(int x, int y, int col);

	int getX();
	int getY();
	int getColor();

	void setX(int n);
	void setY(int n);
	void setColor(int n);
};
#endif
