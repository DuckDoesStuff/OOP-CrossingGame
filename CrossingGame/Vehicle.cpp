#include "Vehicle.h"

Vehicle::Vehicle()
{
	mSpeed = _height = _width = mX = mY = 0;
	moving = true;
}

Vehicle::~Vehicle()
{
}

//******************************************//

void Vehicle::setCoords(int x, int y)
{
	mX = x;
	mY = y;
}

pair<int, int> Vehicle::getCoords(int, int)
{
	return pair<int, int>(mX, mY);
}

//******************************************//

void Vehicle::loadImage(int)
{
}

void Vehicle::drawToScreen()
{
	//for (int i = 0; i < image.size(); i++) {
	//	Common::gotoXY(mX, mY + i);
	//	cout << image[i] << endl;
	//}

	int start = 0, end = 0;

	if (mX < LEFT_GAMEBOARD + 1) 
		start = LEFT_GAMEBOARD - mX + 1;
	if (mX < LEFT_GAMEBOARD + WIDTH_GAMEBOARD)
		end = LEFT_GAMEBOARD + WIDTH_GAMEBOARD - mX - 1;
	if (end > _width) 
		end = _width;

	if (start == 0 && end == 0) return;
	for (int i = 0; i < _height; i++) {
		Common::gotoXY(mX + start, mY + i);
		for (int j = start; j <= end; j++)
			putchar(image[i][j]);
	}
}

void Vehicle::eraseFromScreen()
{
	//for (int i = 0; i < image.size(); i++) {
	//	Common::gotoXY(mX, mY + i);
	//	for (int j = 0; j < image[i].length(); j++)
	//		putchar(' ');
	//}

	int start = 0, end = _width;

	if (LEFT_GAMEBOARD - mX + 1 > 0)
		start = LEFT_GAMEBOARD - mX + 1;
	if (LEFT_GAMEBOARD + WIDTH_GAMEBOARD - mX > 0)
		end = LEFT_GAMEBOARD + WIDTH_GAMEBOARD - mX - 1;
	if (end > _width)
		end = _width;

	for (int i = 0; i < _height; i++) {
		Common::gotoXY(mX + start, mY + i);
		for (int j = start; j <= end; j++)
			putchar(' ');
	}
}

//******************************************//

bool Vehicle::checkPos()
{
	return true;
}

void Vehicle::updatePos()
{
}

void Vehicle::speedUp() {
	if (mSpeed > 0) mSpeed++;
	else mSpeed--;
}

void Vehicle::setImage(int) {

}