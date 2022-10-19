#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	Common::clearConsole();
	_level = 1;
	_numOfLane = 1;
	_trucks = new Truck[_numOfTrucks];
}

Game::~Game()
{
	delete _trucks;
}

void Game::playGame()
{
}

void Game::initGameData()
{
}

void Game::setLevel(int level)
{
	_level = level;
}

int Game::getLevel()
{
	return _level;
}
