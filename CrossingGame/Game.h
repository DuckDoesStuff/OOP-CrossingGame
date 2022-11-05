#pragma once
#include <thread>
#include "Common.h"
#include "People.h"
#include "Car.h"
#include "Truck.h"

#define _numOfLane 4

class Game {
private:
	int _level = 0;
	People human;
	vector<Vehicle*> vh;
public:
	Game();
	~Game();

	//******************************************//

	void playGame(int);
	void initGameData(int);
	void drawBoardGame();

	//******************************************//

	void updateVehicle();

	//******************************************//

	void setLevel(int n) { _level = n; }
	int getLevel() { return _level; }
};
