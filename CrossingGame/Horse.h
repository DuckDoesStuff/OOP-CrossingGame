#pragma once
#include "Animal.h"

class Horse :public Animal {
public:
	Horse(int);
	Horse(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	bool checkPos();
	void updatePos();
};