#pragma once
#include "Vehicle.h"

class Truck:public Vehicle {
public:
	Truck(int);
	Truck(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	bool checkPos();
	void updatePos();
};
