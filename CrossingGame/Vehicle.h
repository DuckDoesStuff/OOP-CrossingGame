#pragma once
#include "Common.h"
#include <iostream>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed = 1;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
public:
	Vehicle();						//Khởi tạo obj tại 0,0
	Vehicle(int col, int row);		//Khởi tạo obj tại tọa độ truyền vào
	~Vehicle();

	virtual void drawToScreen();
	virtual void move();
	virtual void loadImage();
};
