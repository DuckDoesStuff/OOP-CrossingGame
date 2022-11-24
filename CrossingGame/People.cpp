#include "People.h"

People::People()
{
	loadImage(1);
	setCoords(GAMEBOARD_WIDTH/2, 25);
}

People::~People()
{
}

void People::setCoords(int x, int y) {
	mX = x;
	mY = y;
}
pair<int, int> People::getCoords(int, int) {
	return pair<int, int>(mX, mY);
}

void People::drawToScreen() {
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}
void People::eraseFromScreen() {
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++)
			putchar(' ');
	}
}

void People::Up() {
	eraseFromScreen();
	mY--;
	drawToScreen();
}
void People::Down() {
	eraseFromScreen();
	mY++;
	drawToScreen();
}
void People::Left() {
	eraseFromScreen();
	mX--;
	drawToScreen();
}
void People::Right() {
	eraseFromScreen();
	mX++;
	drawToScreen();
}

void People::move() {
	if ((GetAsyncKeyState('W') != 0)) {
		if (mY>TOP_GAMEBOARD - 3) Up();
	}
	if ((GetAsyncKeyState('A') != 0)) {
		if (mX> LEFT_GAMEBOARD + 1) Left();
	}
	if ((GetAsyncKeyState('S') != 0)) {
		if (mY<25) Down();
	}
	if ((GetAsyncKeyState('D') != 0)) {
		if (mX<GAMEBOARD_WIDTH - _width) Right();
	}
}

void People::checkPos(int x, int y, int width, int height) {
	if (x+1 <= mX && mX <= x + width-1) {
		if (y+1 <= mY && mY <= y + height-1) {
			isAlive = false;
		}
	}
}



void People::loadImage(int type) {
	string file;
	if (type == 1) {
		file = "ASCII\\life.txt";
		_height = 3;
		_width = 3;
	}
	ifstream fin(file);
	string s;
	while (!fin.eof()) {
		getline(fin, s);
		image.push_back(s);
	}
}
