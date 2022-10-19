#pragma once
#include "Truck.h"
#include "Common.h"
#include <iostream>
#include <string>

int const LEFT = 0;
int const RIGHT = 10;

class Game {
private:
	int _level;
	int _numOfLane;
	Truck* _trucks;
	int _numOfTrucks = 2;
public:
	Game();
	~Game();

	void playGame();
	void initGameData();

	void setLevel(int);
	int getLevel();
};
