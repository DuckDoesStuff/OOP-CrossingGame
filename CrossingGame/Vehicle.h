#pragma once
#include "Common.h"'
#include <vector>
#include <string>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed = 1;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
	int _height = 0, _width = 0;
public:
	Vehicle(); //Khởi tạo obj tại 0,0
	~Vehicle();

	//******************************************//

	void setCoords(int, int);
	pair<int, int> getCoords(int, int);

	//******************************************//

	int getX() { return mX; }
	int getY() { return mY; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }

	//******************************************//

	virtual void loadImage(int);
	void drawToScreen();
	void eraseFromScreen();

	//******************************************//

	virtual bool checkPos();
	virtual void updatePos();
};
