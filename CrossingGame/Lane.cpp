#include "Lane.h"

Lane::Lane(int num, int lane)
{
	_laneNum = lane;
	int rowSpacing = 7;
	int laneSpacing = 5;

	setNumOfTrucks(num);
	for (int i = 0; i < _numOfTrucks; i++) {
		addTruck(Truck(1, 1 + i * (19 + rowSpacing), 1 + _laneNum*laneSpacing));
	}
}

void Lane::printLane()
{
	for (int i = 0; i < _trucks.size(); i++) {
		_trucks[i].drawToScreen();
	}
}

void Lane::moveLane()
{
	for (int i = 0; i < _numOfTrucks; i++)
		_trucks[i].eraseFromScreen();
	
	for (int i = 0; i < _numOfTrucks; i++)
		_trucks[i].updatePos();

	for (int i = 0; i < _numOfTrucks; i++)
		_trucks[i].drawToScreen();
}

void Lane::addTruck(Truck truck)
{
	_trucks.push_back(truck);
}

void Lane::setNumOfTrucks(int num)
{
	_numOfTrucks = num;
}

int Lane::getNumOfTrucks()
{
	return _numOfTrucks;
}
