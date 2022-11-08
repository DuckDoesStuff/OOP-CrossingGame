#include "People.h"

People::People() {
	loadImage(1);
	mX = mY = 0;
	alive = true;
}

People::People(int x, int y) {
	loadImage(1);
	mX = x;
	mY = y;
	alive = true;
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

void People::setVehicle(vector<Vehicle*>& vh) {
	g_vh = &vh;
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

void People::move() {
	eraseFromScreen();

    if (Common::pressedKey(W) && mY > TOP_GAMEBOARD - 3)
		mY-=5;

    if (Common::pressedKey(A) && mX > LEFT_GAMEBOARD + 1)
		mX--;

	if (Common::pressedKey(S) && mY < TOP_GAMEBOARD + HEIGHT_GAMEBOARD)
		mY+=5;

    if (Common::pressedKey(D) && mX < LEFT_GAMEBOARD + WIDTH_GAMEBOARD - 4)
		mX++;

	drawToScreen();
}

//******************************************//

void People::checkImpact() {
	vector<Vehicle*> v = *g_vh;
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->getY() == mY - 1) {
			if (mX + _width >= v[i]->getX() && mX < v[i]->getX() + v[i]->getWidth()) {
				alive = false;
				break;
			}
		}

		/*Common::gotoXY(WIDTH_GAMEBOARD + 2, 0);
		cout << "                ";
		Common::gotoXY(WIDTH_GAMEBOARD + 2, 0);
		cout << v[0]->getX() << ":" << v[0]->getX() + v[0]->getWidth() << " " << mX;
		if (mX > v[0]->getX() - 1 && mX < v[0]->getX() + v[0]->getWidth()) cout << " Impacted";*/
	}
}