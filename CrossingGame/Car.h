#pragma once
#include "Vehicle.h"

class Car:public Vehicle {
public:
	Car(int);
	Car(int, int, int);

	void drawToScreen();
	void eraseFromScreen();
	void move();
	void loadImage(int);
	void updatePos();
};