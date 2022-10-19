#pragma once
#include "Common.h"
#include <iostream>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed = 2;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
public:
	Vehicle();						//Khởi tạo obj tại 0,0
	~Vehicle();

	void setCoords(int, int);
	pair<int, int> getCoords(int, int);
	virtual void drawToScreen();
	virtual void move();
	virtual void loadImage(int);
};
