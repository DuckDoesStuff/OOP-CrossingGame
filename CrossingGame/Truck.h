#include "Vehicle.h"
#pragma once

class Truck:public Vehicle {
private:
	int _height;	//Bề dọc và ngang của obj
	int _width;
public:
	Truck();
	Truck(int, int, int);
	void drawToScreen();
	void eraseFromScreen();
	void move();
	void loadImage(int);
	void updatePos();
};
