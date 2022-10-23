#pragma once
#include "Common.h"
#include <iostream>

class Vehicle {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed = 1;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
	int _height, _width;
public:
	Vehicle(); //Khởi tạo obj tại 0,0
	~Vehicle();

	void setCoords(int, int);
	pair<int, int> getCoords(int, int);
	//virtual void Car();
	virtual bool checkPos();
	virtual bool checkmX();
	virtual bool checkmX1();
	virtual void drawToScreen();
	virtual void eraseFromScreen();
	virtual void move();
	virtual void loadImage(int);
	virtual void updatePos();

};
