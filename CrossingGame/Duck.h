#pragma once
#include "Animal.h"

class Duck :public Animal {
public:
	Duck(int);
	Duck(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	int checkPos();
	void updatePos();
	void setImage(int);
};