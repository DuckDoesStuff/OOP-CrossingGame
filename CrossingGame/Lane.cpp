#include "Lane.h"

Lane::Lane(Vehicle** obj, int num, int lane)
{
	_vehicleLane = true;
	_laneNum = lane;
	_numOfObj = num;
	int rowSpacing = 7;
	int laneSpacing = 5;

	int type = rand() % 2;
	int model = rand() % 2;

	for (int i = 0; i < num; i++) {
		if (type)
			obj[i] = new Truck(model);
		else
			obj[i] = new Car();
		obj[i]->setCoords(1 + _vh.size() * (obj[i]->getWidth() + rowSpacing), 1 + _laneNum * laneSpacing);
		_vh.push_back(obj[i]);
	}
}

void Lane::printLane()
{
	for (int i = 0; i < _vh.size(); i++) {
		_vh[i]->drawToScreen();
	}
}

void Lane::moveLane()
{
	for (int i = 0; i < _numOfObj; i++)
		_vh[i]->eraseFromScreen();

	for (int i = 0; i < _numOfObj; i++)
		_vh[i]->updatePos();

	for (int i = 0; i < _numOfObj; i++)
		_vh[i]->drawToScreen();
}
