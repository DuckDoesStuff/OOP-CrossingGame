#pragma once
#include "Common.h"
#include <vector>
#include <string>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
	int _height, _width;
	bool moving;
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
	int getSpeed() { return mSpeed; }

	//******************************************//

	virtual void loadImage(int);
	void drawToScreen();
	void eraseFromScreen();
	void startORstop() { moving = !moving; }

	//******************************************//

	virtual bool checkPos();
	virtual void updatePos();
	virtual void speedUp();
	virtual bool isMoving() { return moving; }
};
