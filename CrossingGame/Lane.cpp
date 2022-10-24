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

		if (type) {
			reverse = false;
			obj = new Car(0);
			rowSpacing = (GAMEBOARD_WIDTH - _numOfObjs * obj->getWidth()) / _numOfObjs;
			obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + _laneNum * laneSpacing);
		}
		else {
			reverse = true;
			obj = new Truck(0);
			rowSpacing = (GAMEBOARD_WIDTH - _numOfObjs * obj->getWidth()) / _numOfObjs;
			obj->setCoords(GAMEBOARD_WIDTH - obj->getWidth() - LEFT_GAMEBOARD - 1 - i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + _laneNum * laneSpacing);
		}

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
	for (int i = 0; i < _numOfObjs; i++) {
		if (reverse) {
			if (_Obj[i]->getX() < GAMEBOARD_WIDTH - _Obj[i]->getWidth())
				_Obj[i]->eraseFromScreen();
		}
		else if (_Obj[i]->getX() > LEFT_GAMEBOARD)
				_Obj[i]->eraseFromScreen();
	}

	for (int i = 0; i < _numOfObjs; i++) {
		_Obj[i]->updatePos();
	}

	for (int i = 0; i < _numOfObjs; i++) {
		if (reverse) {
			if (_Obj[i]->getX() < GAMEBOARD_WIDTH - _Obj[i]->getWidth())
				_Obj[i]->drawToScreen();
		}
		else if(_Obj[i]->getX() > LEFT_GAMEBOARD)
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
