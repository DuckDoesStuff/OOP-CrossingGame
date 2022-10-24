#pragma once
#include "Common.h"
#include "Truck.h"
#include "Car.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vhLane;			//Có phải làn phương tiện hay không?
	vector <Vehicle*> _Obj;
	int _numOfObjs;
	bool reverse = false;	//Đi ngược chiều

public:
	Lane(int, int);

	void printLane();
	void moveLane();
	void setNumOfObjs(int);
	int getNumOfObjs();
};