#include "Camel.h"

Camel::Camel(int type) {
	loadImage(type);
	mX = mY = 0;

}

Camel::Camel(int type, int x, int y) {
	loadImage(type);
	mX = x + LEFT_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
}

//******************************************//

void Camel::loadImage(int type)
{
	//Hình ảnh của obj
	string file;
	switch (type)
	{
	case 1:
		file = "ASCII\\camel2.txt";
		_height = 4;
		_width = 13;
		mSpeed = -1;
		break;
	case 0:
		file = "ASCII\\camel1.txt";
		_height = 4;
		_width = 13;
		mSpeed = 1;
	}
	ifstream in(file);

	string s;
	image.clear();
	while (!in.eof()) {
		getline(in, s);
		image.push_back(s);
	}
	in.close();
}

//******************************************//

int Camel::checkPos() {
	if ((mX + mSpeed) >= WIDTH_GAMEBOARD + LEFT_GAMEBOARD) return -1;

	if ((mX + mSpeed + _width) <= LEFT_GAMEBOARD) return -2;


	return 0;
}

void Camel::updatePos()
{
	if (!moving) return;

	if (mX <= WIDTH_GAMEBOARD + LEFT_GAMEBOARD || mX >= LEFT_GAMEBOARD)
		eraseFromScreen();


	if (checkPos() == -2)
	{

		loadImage(0);
		sound->soundSelector = CAMEL;
	}
	else if (checkPos() == -1)
	{
		loadImage(1);
		sound->soundSelector = CAMEL;
	}

	mX += mSpeed;


	if (mX <= WIDTH_GAMEBOARD + LEFT_GAMEBOARD || mX >= LEFT_GAMEBOARD)
	{
		drawToScreen();
	}
}

void Camel::setImage(int i) {
	image.clear();
	loadImage(i);
}