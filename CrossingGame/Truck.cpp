#include "Truck.h"

Truck::Truck() {
	loadImage();
}

void Truck::drawToScreen() {
	for (int i = 0; i < image.size(); i++)
		cout << image[i] << endl;
}

void Truck::move()
{
	mX += mSpeed;
}

void Truck::loadImage()
{
	ifstream in("ASCII\\semi_truck.txt");
	string s;
	while (!in.eof()) {
		getline(in, s);
		image.push_back(s);
	}
	in.close();
}