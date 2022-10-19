#pragma once
#include "Common.h"
#include "Truck.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vehicle_lane;
	vector<Truck> _trucks;//change later
	int _numOfTrucks;
public:
	Lane(int, int);

	void printLane();
	void moveLane();
	void addTruck(Truck);
	void setNumOfTrucks(int);
	int getNumOfTrucks();
};