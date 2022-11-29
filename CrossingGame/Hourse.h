#pragma once
#include "Animal.h"

class Hourse :public Animal {
public:
	Hourse(int);
	Hourse(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	bool checkPos();
	void updatePos();
};