#pragma once

#include "Common.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>


class Menu {
private:
	int left = 69, top = 17;
	int opt = 4;			//number of options
	int sett = 2;
	int menuSlt = 0;
	bool exitMenu = false;

	string menuOptions[4] = { "Play", "Settings", "Leaderboard", "Exit" }; //selections

	Game* game;
	bool runGame = false;

	thread t_sound;
	bool sound = false;
public:
	Menu();
	~Menu();

	//##################################################//

	void printTitle();
	void renderOptionsBox(int, int);
	void renderOptionsText(string[], int, int);
	void renderArrowsOpt(const int&);

	//##################################################//

	void ArrowUp(int);
	void ArrowDown(int);

	//##################################################//

	void initMenu();
	void renderMenuScreen();//Render the title and menu options also setup console attributes
	void renderMenuCurOpt();	//hien thi lua chon hien tai

	//##################################################//

	void renderSettingScreen();

	//##################################################//

	void soundHandle();
	void playBg();
	void stopBg();
	void setVolume(int);

	//##################################################//

	void saveSettings();
	void loadSettings();
};