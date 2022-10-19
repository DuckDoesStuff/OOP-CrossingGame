#pragma once

#include "Common.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>

class Menu {
private:
	const int _opt = 4;			//number of options
	const std::string _selections[4] = { "Play", "Settings", "Leaderboard", "Exit" }; //selections
public:
	Menu();
	~Menu();
	static void renderMainScreen();//Render the title and menu options also setup console attributes
	static void printTitle();
	static void renderOptionsBox();
	static void renderOptionsText();
	static void renderCurOpt();	//hien thi lua chon hien tai
};