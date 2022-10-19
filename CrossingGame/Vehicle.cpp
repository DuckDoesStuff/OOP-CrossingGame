#include "Vehicle.h"

Vehicle::Vehicle()
{
	mX = mY = 0;
}

Vehicle::Vehicle(int col, int row)
{
	mX = col;
	mY = row;
}

Vehicle::~Vehicle()
{
}

void Vehicle::drawToScreen()
{
}

void Vehicle::move()
{
}

void Vehicle::loadImage()
{
}
