#pragma once
#include "Common.h"
#include "Vehicle.h"
#include "Animal.h"
#include <vector>

class People {
protected:
	int mX, mY;
	vector<string> image;
	int _height, _width;
	bool alive;
	vector<Vehicle*>* g_vh;
	vector<Animal*>* g_an;

	Sound* sound = Sound::getInstance();

public:
	People();
	People(int, int);
	~People();

	//******************************************//

	void setCoords(int x, int y);
	pair<int, int> getCoords();

	void setVehicle(vector<Vehicle*>&);
	void setAnimal(vector<Animal*>&);

	int getmY();

	//******************************************//

	void loadImage(int type);
	void drawToScreen();
	void eraseFromScreen();
	void dieAnimation();
	void move();
	void setAlive(bool a) { alive = a; }

	//******************************************//

	bool isAlive() { return alive; }
	bool checkImpact();
};
