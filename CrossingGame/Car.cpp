#include "Car.h"

Car::Car(int type)
{
	loadImage(type);
	mX = mY = 0;
	mSpeed = 1;
}

Car::Car(int type, int x, int y)
{
	loadImage(type);
	mX = x + LEFT_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	mSpeed = 1;
}

//******************************************//

void Car::loadImage(int type)
{
	string file;
	switch (type){
	case 0:
		file = "ASCII\\car1.txt";
		_height = 4;
		_width = 15;
	}

	ifstream fin(file);
	string s;
	while (!fin.eof()) {
		getline(fin, s);
		image.push_back(s);
	}

	fin.close();
}

//******************************************//

bool Car::checkPos()
{
	if ((mX + mSpeed) < WIDTH_GAMEBOARD + LEFT_GAMEBOARD) return true;
	return false;
}

void Car::updatePos()
{
	if (!moving) return;
	if (mX < WIDTH_GAMEBOARD + LEFT_GAMEBOARD) 
		eraseFromScreen();

	if (checkPos())
		mX += mSpeed;
	else
		mX = LEFT_GAMEBOARD - _width - 1;

	if (mX < WIDTH_GAMEBOARD + LEFT_GAMEBOARD) 
		drawToScreen();
}
