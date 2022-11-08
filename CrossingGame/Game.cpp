#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	Common::clearConsole();
	_level = 0;
	human = nullptr;
}

Game::~Game()
{
	delete human;
	human = nullptr;
}

//******************************************//

void Game::playGame(int level)
{
	initGameData(level);
	drawBoardGame();

	Draw(vh);
	while (human->isAlive()) {
		//updatePeople();
		updateVehicle();
		human->checkImpact();
		human->move();
		Sleep(60);
	}
}

template <class T>
void Game::initLane(vector<T*>& v, T* obj, int numOfObjs, int rowSpacing, int laneSpacing, int i) {
	rowSpacing = (WIDTH_GAMEBOARD - numOfObjs * obj->getWidth()) / numOfObjs;
	obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
	v.push_back(obj);
}

void Game::initGameData(int level)
{
	_level = level;

	int numOfObjs = 0;
	if (_level == 1)
		numOfObjs = 2;
	else
		numOfObjs = 3;


	int rowSpacing = 0;
	int laneSpacing = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < numOfObjs; j++) {
			Vehicle* obj;
			if (i % 2 == 0)
				obj = new Car(0);
			else
				obj = new Truck(0);
			initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);
		}
		laneSpacing += 5;
	}
	human = new People(WIDTH_GAMEBOARD / 2, HEIGHT_GAMEBOARD + 6);
	human->setVehicle(vh);
}

template <class T>
void Game::Draw(vector<T*> v) {
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

//******************************************//

void Game::updateVehicle() {
	for (int i = 0; i < vh.size(); i++) {
		vh[i]->updatePos();
	}
}

void Game::speedUpVehicle() {
	for (int i = 0; i < vh.size(); i++) {
		vh[i]->speedUp();
	}
}

void Game::updatePeople() {
	human->checkImpact();
	human->move();
}

//******************************************//