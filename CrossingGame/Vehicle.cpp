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
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}

void Vehicle::eraseFromScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++)
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