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
	Truck* tr;
public:
	Game();
	~Game();

	void playGame();

	void setLevel(int);
	int getLevel();
};
