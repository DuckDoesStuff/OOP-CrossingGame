#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	Common::clearConsole();
	_level = 1;
	_numOfLane = 5;
	_trucks = new Truck[_numOfTrucks];
}

Game::~Game()
{
	delete _trucks;
}

void Game::playGame()
{
	//_trucks[0].drawToScreen();

	//while (true) {
	//	_trucks[0].move();
	//	Sleep(500);
	//}
	drawBoardGame();
}

void Game::initGameData()
{
}

void Game::drawBoardGame()
{
	int left = 0, top = 0;
	int boxW = 40, boxH = 2;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
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
	putchar(201);
	Common::gotoXY(left + boxW, top);
	putchar(187);
	Common::gotoXY(left, top + boxH * _numOfLane);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane);
	putchar(188);
}

void Game::setLevel(int level)
{
	_level = level;
}

int Game::getLevel()
{
	return _level;
}
