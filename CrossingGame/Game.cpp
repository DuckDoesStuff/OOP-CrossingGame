#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	Common::clearConsole();
	_level = 1;
	_numOfLane = 2;
	initGameData();
}

Game::~Game()
{
}

void Game::playGame()
{
	drawBoardGame();
	for (int i = 0; i < _lane.size(); i++)
		_lane[i].printLane();

	while (true) {
		for (int i = 0; i < _lane.size(); i++)
			for (int j = 0; j < _lane[i].getNumOfTrucks(); j++)
				_lane[i].moveLane();
	}
}

void Game::initGameData()
{
	for (int i = 0; i < _numOfLane; i++) {
		_lane.push_back(Lane(3, i));
	}
}

void Game::drawBoardGame()
{
	int left = 0, top = 0;
	int boxW = 80, boxH = 5;

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
