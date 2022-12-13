#pragma once

#include "Common.h"
#include "Game.h"
#include "Sound.h"
#include <fstream>
#include <string>
#include <iostream>

struct player {
	string name = "";
	int score = 0;
};

class Menu {
private:
	int left = 69, top = 17;
	int menuSlt = 0;

	vector<string> menuOptions = { "Play", "Settings", "Leaderboard", "Exit" }; 
	vector<string> playOptions = { "New game", "Continue game", "Back"}; 
	vector<string> settingsOptions = { "Volume", "Background music","Vehicle sound", "Animal sound", "Moving sound", "Back" }; 
	vector<string> fileData;
	vector<player> toplayers;
	Game* game;
	bool runGame = false;

	thread t_sound;
	Sound* sound;
public:
	Menu();
	~Menu();

	//##################################################//

	void printTitle();
	void renderOptionsBox(int);
	void renderOptionsText(vector<string>&, int, int);
	void renderArrowsOpt(const int&);

	//##################################################//

	void ArrowUp(int, int, int);
	void ArrowDown(int, int, int);

	//##################################################//

	void initMenu();
	void renderMenuCurOpt();
	void renderMenuScreen();

	//##################################################//

	void initSettings();
	void renderLeaderBox();
	void RenderLeaderBoard();
	void Toplayers();
	void renderSettCurOpt();
	void renderSettingScreen();
	void renderVolume();

	//##################################################//

	void initPlayOpt();
	bool validates(string username);
	void renderPlayOpt();
	void renderPlayOptScreen();

	//##################################################//

	void renderContinueTexts(vector<string>, int, int);
	void initContinueOpt();
	void renderContinueOpt();
	void renderContinueOptScreen();

	//##################################################//
	
	void loadFileData(string);

	//##################################################//

	void initLeaderBoard();
	void renderLeaderText();
};