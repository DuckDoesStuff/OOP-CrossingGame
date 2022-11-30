#include "Camel.h"

Camel::Camel(int type) {
	loadImage(type);
	mX = mY = 0;
	mSpeed = -1;
}

Camel::Camel(int type, int x, int y) {
	loadImage(type);
	mX = x + LEFT_GAMEBOARD + WIDTH_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	mSpeed = -1;
}

//******************************************//

void Camel::loadImage(int type)
{
	//Hình ảnh của obj
	string file;
	switch (type)
	{
	case 0:
		file = "ASCII\\camel1.txt";
		_height = 4;
		_width = 13;
		mSpeed = 1;
		break;
	case 1:
		file = "ASCII\\camel2.txt";
		_height = 4;
		_width = 13;
		mSpeed = 1;
		break;
	default:
		break;
	}
	ifstream in(file);

	string s;
	while (!in.eof()) {
		getline(in, s);
		image.push_back(s);
	}
	in.close();
}

//******************************************//

int Camel::checkPos() {
	if ((mX + mSpeed + _width) > LEFT_GAMEBOARD) return 1;
	return 0;
}

void Camel::updatePos()
{
	if (!moving) return;
	if (mX < WIDTH_GAMEBOARD + LEFT_GAMEBOARD)
		eraseFromScreen();

	if (checkPos())
		mX += mSpeed;
	else
		mX = WIDTH_GAMEBOARD + LEFT_GAMEBOARD + 1;

	if (mX < WIDTH_GAMEBOARD + LEFT_GAMEBOARD)
		drawToScreen();
}


