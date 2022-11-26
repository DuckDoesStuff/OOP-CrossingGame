#pragma once

#include "Common.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>


class Menu {
private:
	int left = 69, top = 17;
	int opt = 4;	//number of options
	int playOpt = 3; //play new game or continue game
	int sett = 2;
	int menuSlt = 0;
	bool exitMenu = false;

	string menuOptions[4] = { "Play", "Settings", "Leaderboard", "Exit" }; //selections
	string playOptions[4] = { "New game", "Continue game", "Back"}; //selections
	string settingsOptions[4] = { "Background music", "Back" }; //selections

	Game* game;
	thread t_game;
	bool runGame = false;

	thread t_sound;
	bool sound = false;
public:
	Menu();
	~Menu();

	//##################################################//

	void printTitle();
	void renderOptionsBox(int);
	void renderOptionsText(string[], int, int);
	void renderArrowsOpt(const int&);

	//##################################################//

	void ArrowUp(int);
	void ArrowDown(int);

	//##################################################//

	void initMenu();
	void renderMenuCurOpt();
	void renderMenuScreen();

	//##################################################//

	void initSettings();
	void renderSettCurOpt();
	void renderSettingScreen();

	//##################################################//

	void initPlayOpt();
	void renderPlayOpt();
	void renderPlayOptScreen();

	//##################################################//

	void soundHandle();
	void playBg();
	void stopBg();
	void setVolume(int);

	//##################################################//

	void saveSettings();
	void loadSettings();

	//##################################################//

	void gameHandle();
};