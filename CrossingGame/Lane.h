#pragma once
#include "Common.h"
#include "Truck.h"
#include "Car.h"
#include "Vehicle.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vehicleLane = false;
	int _numOfObj = 0;
	vector<Vehicle*> _vh;
public:
	Lane(Vehicle**, int, int);
	//~Lane();

	void printLane();
	void moveLane();
};