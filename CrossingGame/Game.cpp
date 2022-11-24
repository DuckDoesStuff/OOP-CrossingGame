#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	level = 0;
	human = nullptr;
	numOfObjs = 0;
	frame = 0;
}

Game::~Game()
{
	delete human;
	human = nullptr;

	for (int i = 0; i < vh.size(); i++) {
		delete vh[i];
		vh[i] = nullptr;
	}

	for (int i = 0; i < an.size(); i++) {
		delete an[i];
		an[i] = nullptr;
	}

	trafficLane.clear();
}

//******************************************//

void Game::runGame() {
	Common::clearConsole();
	playGame();
}

void Game::playGame(int level)
{
	initGameData(level);
	drawBoardGame();
	//drawTraffic();
	drawPeople();

	DrawObj(vh);
	DrawObj(an);

	Sleep(10);
	while (true) {
		updateVehicle();
		updateAnimal();

		human->move();
		if(human->checkImpact()) break;

		Sleep(frame);
	}
}

template <class T>
void Game::initLane(vector<T*>& v, T* obj, int numOfObjs, int rowSpacing, int laneSpacing, int i) {
	rowSpacing = (WIDTH_GAMEBOARD - numOfObjs * obj->getWidth()) / numOfObjs;
	obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
	v.push_back(obj);
}

void Game::initGameData(int l)
{
	level = l;

	//if (level == 1) {
	//	numOfObjs = 2;
	//	frame = 60;
	//	for (int i = 0; i < 3; i++) {
	//		int index;
	//		bool unique = false;
	//		do {
	//			index = rand() % 5;
	//			unique = true;
	//			for (auto& it : trafficLane) {
	//				if (it.first == index) {
	//					unique = false;
	//					break;
	//				}
	//			}
	//		} while (!unique);

	//		int laneTimer = rand() % (60 - 90 + 1) + 60;
	//		trafficLane.push_back({ index, laneTimer });
	//		trafficTimer.push_back(laneTimer);
	//	}

	//}
	//else {
	//	numOfObjs = 3;
	//	frame = 45;
	//	for (int i = 0; i < 2; i++) {
	//		int index;
	//		bool unique = false;
	//		do {
	//			index = rand() % 5;
	//			unique = true;
	//			for (auto& it : trafficLane) {
	//				if (it.first == index) {
	//					unique = false;
	//					break;
	//				}
	//			}
	//		} while (!unique);

	//		int laneTimer = rand() % (30 - 40 + 1) + 30;
	//		trafficLane.push_back({ index, laneTimer });
	//		trafficTimer.push_back(laneTimer);
	//	}
	//}

	int animalCount = 0;
	int vehicleCount = 0;
	int trafficCount = 0;

	if (level == 1) {
		numOfObjs = 2;
		frame = 60;

		animalCount = 1;
		vehicleCount = 2;
		trafficCount = 2;
	}
	else {
		numOfObjs = 3;
		frame = 45;

		animalCount = 2;
		vehicleCount = 1;
		trafficCount = 2;
	}


	int rowSpacing = 0;
	int laneSpacing = 0;
	unordered_map<int, string> lane;
	
	//Picking animal lane
	for (int i = 0; i < animalCount; i++) {
		int randomIndex;
		do {
			randomIndex = rand() % _numOfLane;
		} while (lane.find(randomIndex) != lane.end());
		lane.insert({ randomIndex, "animal" });
	}

	//Picking vehicle lane
	for (int i = 0; i < vehicleCount; i++) {
		int randomIndex;
		do {
			randomIndex = rand() % _numOfLane;
		} while (lane.find(randomIndex) != lane.end());
		lane.insert({ randomIndex, "vehicle" });
	}

	//Picking traffic lane
	for (int i = 0; i < trafficCount; i++) {
		int randomIndex;
		do {
			randomIndex = rand() % _numOfLane;
		} while (lane.find(randomIndex) != lane.end());
		lane.insert({ randomIndex, "traffic" });
	}

	for (int i = 0; i < _numOfLane; i++) {
		if (lane[i] == "animal") 
			for (int j = 0; j < numOfObjs; j++) {
				Animal* obj;
				if (i % 2 == 0)
					obj = new Horse(0);
				else
					obj = new Camel(0);
				initLane(an, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		else if (lane[i] == "vehicle") 
			for (int j = 0; j < numOfObjs; j++) {
				Vehicle* obj;
				if (i % 2 == 0)
					obj = new Car(0);
				else
					obj = new Truck(0);
				initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		else if (lane[i] == "traffic") {
			int laneTimer = rand() % (frame - (frame + 30) + 1) + frame;
			for (int j = 0; j < numOfObjs; j++) {
				Vehicle* obj;
				if (i % 2 == 0)
					obj = new Car(0);
				else
					obj = new Truck(0);
				initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
			trafficLane.push_back({ i, laneTimer });
			trafficTimer.push_back(laneTimer);
		}
		laneSpacing += 5;
	}


	//for (int i = 0; i < _numOfLane; i++) {
	//	for (int j = 0; j < numOfObjs; j++) {
	//		/*Vehicle* obj;
	//		if (i % 2 == 0)
	//			obj = new Car(0);
	//		else
	//			obj = new Truck(0);
	//		initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);*/
	//
//			Animal* obj;
//			if (i % 2 == 0)
//				obj = new Horse(0);
//			else
//				obj = new Camel(0);
//			initLane(an, obj, numOfObjs, rowSpacing, laneSpacing, j);
	//
	//		
	//	}
	//	laneSpacing += 5;
	//}
	human = new People(LEFT_GAMEBOARD + WIDTH_GAMEBOARD / 2, HEIGHT_GAMEBOARD + 6);
	human->setVehicle(vh);
	human->setAnimal(an);
}

template <class T>
void Game::DrawObj(vector<T*> v) {
	for (int i = 0; i < v.size(); i++)
		v[i]->drawToScreen();
}

void Game::drawBoardGame()
{
	int left = LEFT_GAMEBOARD, top = TOP_GAMEBOARD;
	int boxW = WIDTH_GAMEBOARD, boxH = 5;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
	for (int j = 0; j < boxW; j++) {
		Common::gotoXY(left + j, top - boxH);
		putchar(205);
	}
	for (int j = 0; j < boxH; j++) {
		Common::gotoXY(left, top - boxH + j);
		putchar(186);
		Common::gotoXY(left + boxW, top - boxH + j);
		putchar(186);
	}

	Common::gotoXY(left, top - boxH);
	putchar(201);
	Common::gotoXY(left + boxW, top - boxH);
	putchar(187);

	for (int i = 0; i < _numOfLane; i++) {
		box = i * boxH;
		for (int j = 0; j < boxW; j++) {
			Common::gotoXY(left + j, top + box);
			putchar(205);
			Common::gotoXY(left + j, top + boxH + box);
		putchar(205);
		}

		for (int j = 0; j < boxH; j++) {
			Common::gotoXY(left, top + j + box);
			putchar(186);
			Common::gotoXY(left + boxW, top + j + box);
			putchar(186);
		}

		Common::gotoXY(left, top + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + box);
		putchar(185);
		Common::gotoXY(left, top + boxH + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + boxH + box);
		putchar(185);
	}
	Common::gotoXY(left, top);
	putchar(204);
	Common::gotoXY(left + boxW, top);
	putchar(185);

	for (int j = 0; j < boxW; j++) {
		Common::gotoXY(left + j, top + boxH * _numOfLane + boxH);
		putchar(205);
	}
	for (int j = 0; j < boxH; j++) {
		Common::gotoXY(left, top + boxH * _numOfLane + j);
		putchar(186);
		Common::gotoXY(left + boxW, top + boxH * _numOfLane + j);
		putchar(186);
	}

	Common::gotoXY(left, top + boxH * _numOfLane + boxH);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane + boxH);
	putchar(188);

	Common::gotoXY(left, top + boxH * _numOfLane);
	putchar(204);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane);
	putchar(185);
}

void Game::drawPeople() {
	human->drawToScreen();
}

//******************************************//

void Game::updateVehicle() {
	for (int i = 0; i < vh.size(); i++) {
		vh[i]->updatePos();
	}
	//setTraffic();
}

void Game::updateAnimal() {
	for (int i = 0; i < an.size(); i++) {
		an[i]->updatePos();
	}
}

void Game::setTraffic() {
}

void Game::drawTraffic() {
}

//******************************************//