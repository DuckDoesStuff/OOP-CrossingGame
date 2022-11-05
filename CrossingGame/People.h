#pragma once
#include "Common.h"
#include <vector>
#include <string>

class People {
protected:
	int mX, mY;
	vector<string> image;
	int _height, _width;
public:
	People();
	~People();

	//******************************************//

	void setCoords(int x, int y);
	pair<int, int> getCoords(int, int);

	//******************************************//

	virtual void loadImage(int type);
	virtual void drawToScreen();
	virtual void eraseFromScreen();
	virtual void move();

	//******************************************//

};
