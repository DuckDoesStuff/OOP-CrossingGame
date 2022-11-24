#pragma once
#include <thread>
#include <mutex>
#include <unordered_map>
#include "Common.h"
#include "People.h"

#include "Car.h"
#include "Truck.h"
#include "Camel.h"
#include "Horse.h"

#define _numOfLane 5

class Game {
private:
	int level;
	int frame;
	vector<pair<int, int>> trafficLane;			//{index of first vh, timer}
	vector<int> trafficTimer;					//{timer}

	int numOfObjs;
	People* human;
	vector<Vehicle*> vh;
	vector<Animal*> an;
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
	void drawPeople();

	//******************************************//

	void updateVehicle();
	void updateAnimal();
	void setTraffic();
	void drawTraffic();

	//******************************************//

	void setLevel(int n) { level = n; }
	int getLevel() { return level; }
};
