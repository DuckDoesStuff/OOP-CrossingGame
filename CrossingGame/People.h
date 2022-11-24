#pragma once
#include "Common.h"
#include <iostream>

class People {
protected:
	int mX, mY;
	vector<string> image;
	int _height, _width;
	bool isAlive = true;
public:
	People();
	~People();
	void setCoords(int x, int y);
	pair<int, int> getCoords(int, int);
	virtual void drawToScreen();
	virtual void eraseFromScreen();
	virtual void move();
	//void loadImage(int type);
	virtual void loadImage(int type);
	virtual void Up();
	virtual void Down();
	virtual void Left();
	virtual void Right();
	void checkPos(int, int, int, int);
	bool alive() { return isAlive; }
};
