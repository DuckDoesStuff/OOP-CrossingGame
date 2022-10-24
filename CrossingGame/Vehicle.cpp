#include "Vehicle.h"
#include "Truck.h"
#include "Car.h"

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

bool Vehicle::checkPos()
{
	return true;
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
