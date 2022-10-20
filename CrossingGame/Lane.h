#pragma once
#include "Common.h"
#include "Truck.h"
#include "Car.h"

class Lane {
private:
	short _laneNum = 0;
	bool _vehicle_lane;
	vector<Truck> _trucks;//change later
	int _numOfTrucks;

	vector<Car> _cars;
	int _numOfCars;
public:
	Lane(int, int);

	void printLane();
	void moveLane();
	void addTruck(Car);
	void setNumOfTrucks(int);
	int getNumOfTrucks();
};