#pragma once
#include "Common.h"
#include "Lane.h"
//#include "Vehicle.h"
#include "Truck.h"
#include <iostream>
#include <string>
#include "People.h"

int const LEFT = 0;
int const RIGHT = 10;

class Game {
private:
	int _level;
	vector<Lane> _lane;
	int _numOfLane;
	People human;
public:
	Game();
	~Game();

	void playGame();
	void initGameData();
	void drawBoardGame();

	void setLevel(int);
	int getLevel();
};
