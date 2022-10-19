#include "Vehicle.h"
#pragma once

class Truck:public Vehicle {
public:
	Truck();
	void drawToScreen();
	void move();
	void loadImage();
};
