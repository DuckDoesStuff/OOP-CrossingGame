#pragma once
#include "Animal.h"

class Camel :public Animal {
public:
	Camel(int);
	Camel(int, int, int);

	//******************************************//

	void loadImage(int);

	//******************************************//

	bool checkPos();
	void updatePos();

};
