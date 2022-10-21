#include "Vehicle.h"


Vehicle::Vehicle()
{
	mX = mY = 0;
}

Vehicle::~Vehicle()
{
}

void Vehicle::setCoords(int x, int y)
{
	mX = x;
	mY = y;
}

pair<int, int> Vehicle::getCoords(int, int)
{
	return pair<int, int>(mX, mY);
}

void Vehicle::drawToScreen()
{
}

void Vehicle::move()
{
}

void Vehicle::loadImage(int)
{
}

void Vehicle::updatePos()
{
}

void Vehicle::eraseFromScreen()
{
}
