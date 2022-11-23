#pragma once
#include <thread>
#include <mutex>
#include "Common.h"
#include "People.h"
#include "Car.h"
#include "Truck.h"

#define _numOfLane 5

class Game {
private:
	int level;
	int frame;
	vector<pair<int, int>> trafficLane;
	vector<int> trafficTimer;

	int numOfObjs;
	People* human;
	vector<Vehicle*> vh;

public:
	Game();
	~Game();

	//******************************************//

	void runGame();
	void playGame(int level = 1);

	template <class T> 
	void initLane(vector<T*>&, T*, int, int, int, int);
	void initGameData(int);

	template <class T>
	void DrawObj(vector<T*>);

	void drawBoardGame();

	//******************************************//

	void updateVehicle();
	void setTraffic();
	void drawTraffic();

	//******************************************//

	void setLevel(int n) { level = n; }
	int getLevel() { return level; }
};
