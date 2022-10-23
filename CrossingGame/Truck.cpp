#include "Truck.h"

Truck::Truck() {
	loadImage(1);
	mX = mY = 1;
}

Truck::Truck(int type, int x, int y) {
	mX = x + LEFT_GAMEBOARD;
	mY = y + TOP_GAMEBOARD;
	loadImage(type);
}

void Truck::drawToScreen() {
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}

void Truck::eraseFromScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++)
			putchar(' ');
	}
}

void Truck::move()
{
	mX += mSpeed;
	drawToScreen();
}

void Truck::loadImage(int type)
{
	//Hình ảnh của obj
	string file;
	switch (type)
	{
	case 1:
		file = "ASCII\\truck1.txt";
		_height = 4;
		_width = 19;
		break;
	case 2:
		file = "ASCII\\truck2.txt";
		_height = 4;
		_width = 13;
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

void Truck::updatePos()
{
	mX += mSpeed;
}
