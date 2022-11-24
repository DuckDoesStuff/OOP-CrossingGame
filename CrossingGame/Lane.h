#pragma once
#include "Common.h"
#include "Truck.h"
#include "Car.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vhLane;			//Có phải làn phương tiện hay không?
	bool reverse = false;	//Đi ngược chiều


public:
	Lane(int, int);

	vector <Vehicle*> _Obj;
	int _numOfObjs;
	void printLane();
	void moveLane();
	void setNumOfObjs(int);
	int getNumOfObjs();
};