#pragma once
#include "Common.h"
#include "Sound.h"
#include <vector>
#include <string>

class Animal {
protected:
	int mX, mY;				//Tọa độ của obj trong game frame
	int mSpeed;			//Tốc độ của obj
	vector<string> image;	//Lưu hình ảnh của obj
	int _height, _width;
	bool moving;

	Sound* sound = Sound::getInstance();
public:
	Animal(); //Khởi tạo obj tại 0,0
	~Animal();

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

	virtual int checkPos();
	virtual void updatePos();
	virtual void setImage(int);
	void speedUp();
	void setmX(int x) { mX = x; }
	void setSpeed(int x) { mSpeed = x; }
	bool isMoving() { return moving; }
};
