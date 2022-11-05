#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	Common::clearConsole();
}

Game::~Game()
{
}

//******************************************//

void Game::playGame(int level)
{
	initGameData(level);
	drawBoardGame();

	for (int i = 0; i < vh.size(); i++) {
		vh[i]->drawToScreen();
	}

	while (true) {
		human.move();
		updateVehicle();
		Sleep(100);
	}
}

void Game::initGameData(int level)
{
	_level = level;

	int numOfObjs = 0;
	switch (_level)
	{
	case 1:
		numOfObjs = 2;
		break;
	case 2:
		numOfObjs = 3;
		break;
	case 3:
		numOfObjs = 3;
		break;
	default:
		break;
	}

	int rowSpacing = 0;
	int laneSpacing = 0;

	//Lane 1
	for (int i = 0; i < numOfObjs; i++) {
		Car* obj = new Car(0);
		rowSpacing = (GAMEBOARD_WIDTH - numOfObjs * obj->getWidth()) / numOfObjs;
		obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
		vh.push_back(obj);
	}
	laneSpacing += 5;
	//Lane 2
	for (int i = 0; i < numOfObjs; i++) {
		Truck* obj = new Truck(0);
		rowSpacing = (GAMEBOARD_WIDTH - numOfObjs * obj->getWidth()) / numOfObjs;
		obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
		vh.push_back(obj);
	}
	laneSpacing += 5;
	//Lane 3
	for (int i = 0; i < numOfObjs; i++) {
		Truck* obj = new Truck(0);
		rowSpacing = (GAMEBOARD_WIDTH - numOfObjs * obj->getWidth()) / numOfObjs;
		obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
		vh.push_back(obj);
	}
	laneSpacing += 5;
	//Lane 4
	for (int i = 0; i < numOfObjs; i++) {
		Car* obj = new Car(0);
		rowSpacing = (GAMEBOARD_WIDTH - numOfObjs * obj->getWidth()) / numOfObjs;
		obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
		vh.push_back(obj);
	}
}

void Game::drawBoardGame()
{
	int left = LEFT_GAMEBOARD, top = TOP_GAMEBOARD;
	int boxW = GAMEBOARD_WIDTH, boxH = 5;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
	for (int j = 0; j < boxW; j++) {
		Common::gotoXY(left + j, top - 3);
		putchar(205);
	}
	for (int j = 0; j < boxH; j++) {
		Common::gotoXY(left, top - 3 + j);
		putchar(186);
		Common::gotoXY(left + boxW, top - 3 + j);
		putchar(186);
	}

	Common::gotoXY(left, top - 3);
	putchar(201);
	Common::gotoXY(left + boxW, top - 3);
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
		Common::gotoXY(left + j, top + boxH * _numOfLane + 3);
		putchar(205);
	}
	for (int j = 0; j < 3; j++) {
		Common::gotoXY(left, top + boxH * _numOfLane + j);
		putchar(186);
		Common::gotoXY(left + boxW, top + boxH * _numOfLane + j);
		putchar(186);
	}

	Common::gotoXY(left, top + boxH * _numOfLane + 3);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane + 3);
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