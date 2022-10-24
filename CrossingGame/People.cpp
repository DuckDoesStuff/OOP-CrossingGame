#include "People.h"

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
	Common::gotoXY(mX, mY - 2);
}
void People::Down() {
	Common::gotoXY(mX, mY + 2);
}
void People::Left() {
	Common::gotoXY(mX - 4, mY);
}
void People::Right() {
	Common::gotoXY(mX + 4, mY);
}
void People::move() {
    if ((GetAsyncKeyState('W') != 0) ) {
        Up();
    }
    if ((GetAsyncKeyState('A') != 0) ) {
        Left();
    }
    if ((GetAsyncKeyState('S') != 0) ) {
        Down();
    }
    if ((GetAsyncKeyState('D') != 0) ) {
        Right();
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