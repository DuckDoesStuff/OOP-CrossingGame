#include "Lane.h"




Lane::Lane(int num, int lane)
{
	_laneNum = lane;
	_vhLane = true;
	int rowSpacing = 0;
	int laneSpacing = 5;

	int type = rand() % 2;
	int model = rand() % 2;

	_numOfObjs = num;
	for (int i = 0; i < _numOfObjs; i++) {
		Vehicle* obj;

		if (type)
			obj = new Car(0);
		else 
			obj = new Truck(0);

		rowSpacing = (GAMEBOARD_WIDTH - _numOfObjs * obj->getWidth()) / _numOfObjs;
		obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + _laneNum * laneSpacing);
		_Obj.push_back(obj);
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

	for (int i = 0; i < _numOfObjs; i++) {
		_Obj[i]->updatePos();
	}

	for (int i = 0; i < _numOfObjs; i++) {
		_Obj[i]->drawToScreen();
	}
}

void Lane::setNumOfObjs(int num)
{
	_numOfObjs = num;
}

int Lane::getNumOfObjs()
{
	return _numOfObjs;
}
