#include "Hourse.h"

Hourse::Hourse(int type)
{
	loadImage(type);
	mX = mY = 0;
	mSpeed = 1;
}

Hourse::Hourse(int type, int x, int y)
{
	loadImage(type);
	mX = x + LEFT_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	mSpeed = 1;
}

//******************************************//

void Hourse::loadImage(int type)
{
	string file;
	switch (type) {
	case 0:
		file = "ASCII\\hourse.txt";
		_height = 4;
		_width = 19;
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

bool Hourse::checkPos()
{
	if ((mX + mSpeed) < WIDTH_GAMEBOARD - _width) return true;
	return false;
}

void Hourse::updatePos()
{
	if (mX > LEFT_GAMEBOARD)
		eraseFromScreen();

	if (checkPos())
		mX += mSpeed;
	else
		mX = -_width;

	if (mX > LEFT_GAMEBOARD)
		drawToScreen();
}
