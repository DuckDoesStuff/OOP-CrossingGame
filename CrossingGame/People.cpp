#include "People.h"

People::People() {
	loadImage(1);
	mX = mY = 0;
}

People::~People() {

}

//******************************************//

void People::setCoords(int x, int y) {
	mX = x;
	mY = y;
}

pair<int, int> People::getCoords(int, int) {
	return pair<int, int>(mX, mY);
}

//******************************************//

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


//******************************************//

void People::move() {
	eraseFromScreen();

    if (Common::pressedKey(W))
		mY--;

    if (Common::pressedKey(A))
		mX--;

    if (Common::pressedKey(S))
		mY++;

    if (Common::pressedKey(D))
		mX++;

	drawToScreen();
}