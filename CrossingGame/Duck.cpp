#include "Duck.h"
#include "Game.h"
Duck::Duck(int type)
{
	loadImage(type);
	mX = mY = 0;
}

Duck::Duck(int type, int x, int y)
{
	loadImage(type);
	mX = x + LEFT_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	
}

//******************************************//

void Duck::loadImage(int type)
{
	string file;
	switch (type) {
	case 1:
		file = "ASCII\\duck2.txt";
		_height = 4;
		_width = 19;
		mSpeed = -1;
		break;
	case 0:
		file = "ASCII\\duck1.txt";
		_height = 4;
		_width = 19;
		mSpeed = 1;
	}

	ifstream fin(file);

	string s;
	image.clear();
	while (!fin.eof()) {
		getline(fin, s);
		image.push_back(s);
	}

	fin.close();
}

//******************************************//

int Duck::checkPos()
{
	if ((mX + mSpeed) >= WIDTH_GAMEBOARD + LEFT_GAMEBOARD) return -1;

	if ((mX + mSpeed + _width) <= LEFT_GAMEBOARD) return -2;
	
	
	return 0;
}

void Duck::updatePos()
{
	if (!moving) return;

	if (mX <= WIDTH_GAMEBOARD + LEFT_GAMEBOARD||mX>=LEFT_GAMEBOARD)
		eraseFromScreen();
	

	if (checkPos() == -2)
	{
		loadImage(0);
		sound->soundSelector = DUCK;
	}
	else if (checkPos() == -1)
	{
		loadImage(1);
		sound->soundSelector = DUCK;
	}

	mX += mSpeed;
	

	if (mX <= WIDTH_GAMEBOARD + LEFT_GAMEBOARD|| mX >= LEFT_GAMEBOARD)
	{
		drawToScreen();
	}
}

void Duck::setImage(int i) {
	image.clear();
	loadImage(i);
}