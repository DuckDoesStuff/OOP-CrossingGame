#pragma once
#include "Common.h"
#include <iostream>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed = 1;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
	int _height = 0, _width = 0;
public:
	Vehicle();						//Khởi tạo obj tại 0,0
	~Vehicle();

	void setCoords(int, int);
	pair<int, int> getCoords(int, int);
	virtual void drawToScreen();
	virtual void eraseFromScreen();
	virtual void move();
	virtual void loadImage(int);
	virtual void updatePos();
	virtual int getWidth() { return _width; }
	virtual int getHeight() { return _height; }
};
