#pragma once
#include "Common.h"
#include "Vehicle.h"
#include <thread>
#include <vector>
#include <string>

class People {
protected:
	int mX, mY;
	vector<string> image;
	int _height, _width;
	bool alive;
	vector<Vehicle*>* g_vh;
public:
	People();
	People(int, int);
	~People();

	//******************************************//

	void setCoords(int x, int y);
	pair<int, int> getCoords(int, int);

	void setVehicle(vector<Vehicle*>&);

	//******************************************//

	virtual void loadImage(int type);
	virtual void drawToScreen();
	virtual void eraseFromScreen();
	virtual void move();

	//******************************************//

	bool isAlive() { return alive; }
	bool checkImpact();
};
