#include "Game.h"

Game::Game()
{
	Common::clearConsole();
	_level = 1;
	_numOfLane = 1;
	tr = new Truck();
}

Game::~Game()
{
	delete tr;
}

void Game::playGame()
{
	tr->drawToScreen();
}

void Game::setLevel(int level)
{
	_level = level;
}

int Game::getLevel()
{
	return _level;
}
