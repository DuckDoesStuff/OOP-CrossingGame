﻿#include "Vehicle.h"
#pragma once

class Truck:public Vehicle {
public:
	Truck();
	Truck(int, int, int);
	void drawToScreen();
	void eraseFromScreen();
	void move();
	void loadImage(int);
	void updatePos();
};
