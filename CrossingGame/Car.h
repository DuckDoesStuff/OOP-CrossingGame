#pragma once
#include "Vehicle.h"

class Car:public Vehicle {
public:
	Car(int);
	Car(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	bool checkPos();
	void updatePos();
	void startORstop();
};