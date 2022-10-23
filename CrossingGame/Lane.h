#pragma once
#include "Common.h"
#include "Truck.h"
#include "Car.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vehicle_lane;
	vector <Vehicle*> _Obj;//change later
	int _numOfObjs;

public:
	Lane(int, int, int);

	void printLane();
	void moveLane();
	void addObj(Vehicle*);
	void setNumOfObjs(int);
	int getNumOfObjs();
};