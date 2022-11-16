#pragma once
#include <thread>
#include "Common.h"
#include "People.h"
#include "Car.h"
#include "Truck.h"
#include "Camel.h"
#include "Hourse.h"

#define _numOfLane 4

class Game {
private:
	int _level;
	People* human;
	vector<Vehicle*> vh;
	vector<Animal*> an;
public:
	Game();
	~Game();

	//******************************************//

	void playGame(int);
	template <class T> 
	void initLane(vector<T*>&, T*, int, int, int, int);
	void initGameData(int);
	template <class T>
	void Draw(vector<T*>);
	void drawBoardGame();

	//******************************************//

	void updateVehicle();
	void updateAnimal();

	void speedUpAnimal();
	
	void speedUpVehicle();


	void updatePeople();

	//******************************************//

	void setLevel(int n) { _level = n; }
	int getLevel() { return _level; }
};
