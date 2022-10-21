#include "Lane.h"




Lane::Lane(int num, int lane, int type)
{
	_laneNum = lane;
	int rowSpacing = 7;
	int laneSpacing = 5;

	setNumOfTrucks(num);
	for (int i = 0; i < _numOfObjs; i++) {
		Vehicle* Obj;
		switch (type) {
		case 0:
			Obj = new Car(1, 1 + i * (19 + rowSpacing), 1 + _laneNum * laneSpacing);
			addObj(Obj);
			break;
		case 1:
			Obj = new Truck(1, 1 + i * (19 + rowSpacing), 1 + _laneNum * laneSpacing);
			addObj(Obj);
			break;
		}
	}
}

void Lane::printLane()
{
	for (int i = 0; i < _Obj.size(); i++) {
		_Obj[i]->drawToScreen();
	}
}

void Lane::moveLane()
{
	for (int i = 0; i < _numOfObjs; i++)
		_Obj[i]->eraseFromScreen();
	
	for (int i = 0; i < _numOfObjs; i++)
		_Obj[i]->updatePos();

	for (int i = 0; i < _numOfObjs; i++)
		_Obj[i]->drawToScreen();
}

void Lane::addObj(Vehicle* Obj)
{
	_Obj.push_back(Obj);
}

void Lane::setNumOfTrucks(int num)
{
	_numOfObjs = num;
}

int Lane::getNumOfTrucks()
{
	return _numOfObjs;
}
