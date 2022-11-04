#include "People.h"

People::People()
{
	loadImage(1);
	mX = LEFT_GAMEBOARD;
	mY = TOP_GAMEBOARD;
	_height = 0;
	_width = 0;
	drawToScreen();
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
	mY--;
}
void People::Down() {
	mY++;
}
void People::Left() {
	mX--;
}
void People::Right() {
	mX++;
}
void People::playerHandle(){
	while (true) {
		drawToScreen();
		Sleep(20);
	}
}

void People::move() {

    if ((GetAsyncKeyState(W) != 0)) {
		eraseFromScreen();
        Up();
		drawToScreen();
    }
    if ((GetAsyncKeyState(A) != 0) ) {
		eraseFromScreen();
		Left();
		drawToScreen();
    }
    if ((GetAsyncKeyState(S) != 0) ) {
		eraseFromScreen();
		Down();
		drawToScreen();
    }
    if ((GetAsyncKeyState(D) != 0) ) {
		eraseFromScreen();
		Right();
		drawToScreen();
    }

	//int t = Common::getConsoleInput();
	//switch (t)
	//{
	//case 2:
	//	Up();
	//	break;
	//case 3:
	//	Left();
	//	break;
	//case 4:
	//	Right();
	//	break;
	//case 5:
	//	Down();
	//	break;
	//default:
	//	break;
	//}
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