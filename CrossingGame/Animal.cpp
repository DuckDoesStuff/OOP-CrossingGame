#include "Animal.h"

Animal::Animal()
{
	mSpeed = _height = _width = mX = mY = 0;
}

Animal::~Animal()
{
}

//******************************************//

void Animal::setCoords(int x, int y)
{
	mX = x;
	mY = y;
}

pair<int, int> Animal::getCoords(int, int)
{
	return pair<int, int>(mX, mY);
}

//******************************************//

void Animal::loadImage(int)
{
}

void Animal::drawToScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		cout << image[i] << endl;
	}
}

void Animal::eraseFromScreen()
{
	for (int i = 0; i < image.size(); i++) {
		Common::gotoXY(mX, mY + i);
		for (int j = 0; j < image[i].length(); j++)
			putchar(' ');
	}
}

//******************************************//

bool Animal::checkPos()
{
	return true;
}

void Animal::updatePos()
{
}

void Animal::speedUp() {
	if (mSpeed > 0) mSpeed++;
	else mSpeed--;
}


