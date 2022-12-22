#include "Menu.h"

Sound* Sound::instance = nullptr;

Menu::Menu() {
	game = nullptr;
	sound = Sound::getInstance();
	//loadSettings();
}

Menu::~Menu() {
	//saveSettings();
	delete game;
	game = nullptr;

	delete sound;
	sound = nullptr;
}

//##################################################//

void Menu::printTitle()
{
	int height = 8, left = 45, width = 57, top = 3;
	
	Common::gotoXY(84, 10);
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	cout <<char(167)<<"2022 From HCMUS.";

	std::ifstream in("ASCII\\Cross.txt");
	Common::setConsoleColor(BRIGHT_WHITE, GREEN);

	left = 48; top = 4;
	int i = 0;
	while (!in.eof())
	{
		string s;
		getline(in, s);
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();
	std::ifstream inf("ASCII\\Road.txt");

	Common().setConsoleColor(BRIGHT_WHITE, RED);
	left = 76;
	 i = 0;
	while (!inf.eof())
	{
		string s;
		getline(inf, s);
		Common::gotoXY(left, top+i);
		cout << s;
		i++;
	}
	inf.close();
	i = 0;
	left = 104;
	top = 0;
	ifstream tra("ASCII\\trafficlight.txt");
	Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	while (!tra.eof())
	{
		string temp;
		getline(tra, temp);
		Common::gotoXY(left, top + i);
		cout << temp;
		i++;

	}
	tra.close();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

}

void Menu::renderOptionsBox(int n)
{
	int boxW = 21, boxH = 2;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
	for (int i = 0; i < n; i++) {
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
	Common::gotoXY(left, top + boxH * n);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * n);
	putchar(188);
}

void Menu::renderOptionsText(vector<string>& text, int left, int top)
{
	int width = 41;
	for (int i = 0; i < text.size(); i++) {
		Common::gotoXY((width - text[i].length()) / 2 + left, top + i * 2);
		std::cout << text[i];
	}
}

void Menu::renderArrowsOpt(const int& n) {
	int top = this->top + 1;
	int left = this->left - 3;
	Common::gotoXY(left, top + 2 * n);
	putchar(62);				//left arrows
	putchar(62);
	Common::gotoXY(left + 26, top + 2 * n);
	putchar(60);				//right arrows
	putchar(60);
}

//##################################################//

void Menu::ArrowUp(int left, int top, int slt) {
	left -= 3;
	top += 1;

	Common::gotoXY(left, top + 2 * (slt + 1));
	cout << "  ";
	Common::gotoXY(left + 26, top + 2 * (slt + 1));
	cout << "  ";

	Common::gotoXY(left, top + 2 * slt);
	cout << ">>";
	Common::gotoXY(left + 26, top + 2 * slt);
	cout << "<<";
}

void Menu::ArrowDown(int left, int top, int slt) {
	left -= 3;
	top += 1;

	Common::gotoXY(left, top + 2 * (slt - 1));
	cout << "  ";
	Common::gotoXY(left + 26, top + 2 * (slt - 1));
	cout << "  ";

	Common::gotoXY(left, top + 2 * slt);
	cout << ">>";
	Common::gotoXY(left + 26, top + 2 * slt);
	cout << "<<";
}

//##################################################//

//Menu
void Menu::initMenu() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(menuOptions.size());
	renderOptionsText(menuOptions, left - 9, top + 1);
	renderArrowsOpt(menuSlt);
}

void Menu::renderMenuScreen()
{
	t_sound = thread(&Sound::runHandle, sound);

	initMenu();
	renderMenuCurOpt();

	if (t_sound.joinable()) t_sound.join();
}

void Menu::renderMenuCurOpt()
{
	int c;
	bool loadMenu = true;
	while (loadMenu) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (menuSlt == 0) break;
			menuSlt--;
			ArrowUp(left, top, menuSlt);
			break;
		case 5:								//move down
			if (menuSlt == menuOptions.size() - 1) break;
			menuSlt++;
			ArrowDown(left, top, menuSlt);
			break;
		case 6:								//enter
			switch (menuSlt) {
			case 0:					//Play
				renderPlayOptScreen();
				initMenu();
				break;
			case 1:					//Settings
				renderSettingScreen();
				initMenu();
				break;
			case 2:					//Leaderboard
				renderLeaderBoard();
				initMenu();
				break;
			case 3:
				sound->stopHandle();
				Common::clearConsole();
				return;
				break;
			}
		}
	}
}

//##################################################//

//Settings
void Menu::initSettings() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(settingsOptions.size());
	renderOptionsText(settingsOptions, left - 9, top + 1);
	renderArrowsOpt(0);
}

void Menu::renderSettCurOpt() {
	int c, slt = 0;
	bool loadSett = true;
	while (loadSett) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:			//move up
			if (slt == 0) break;
			slt--;
			ArrowUp(left, top, slt);
			break;
		case 5:			//move down
			if (slt == settingsOptions.size() - 1) break;
			slt++;
			ArrowDown(left, top, slt);
			break;
		case 6:			//enter
			switch (slt) {
			case 0:
				renderVolume();
				break;
			case 1:
				sound->toggleTheme();
				break;
			case 2:
				sound->toggleVehicle();
				break;
			case 3:
				sound->toggleAnimal();
				break;
			case 4:
				sound->toggleMoving();
				break;
			default:				//back to menu
				loadSett = false;
				break;
			}
			break;
		}
	}
}

void Menu::renderSettingScreen() {
	initSettings();
	renderSettCurOpt();
}

void Menu::renderVolume() {
	Common::gotoXY(left + 3, top + 1);
	cout << "             ";
	bool render = true;
	while (render) {
		Common::gotoXY(left + 10, top + 1);
		cout << sound->getVolume() << " ";
		int c = Common::getConsoleInput();
		wstring cmd;
		switch (c)
		{
		case 6:
			render = false;
			break;
		case 3:
			sound->volumeDown();
			break;
		case 4:
			sound->volumeUp();
			break;
		default:
			break;
		}
	}
	Common::gotoXY(left + 3, top + 1);
	cout << "             ";
	Common::gotoXY(left + 8, top + 1);
	cout << "Volume";
}

//##################################################//

//Play
void Menu::initPlayOpt() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderOptionsBox(playOptions.size());
	renderOptionsText(playOptions, left - 9, top + 1);
	renderArrowsOpt(0);
}
bool Menu::validates(string username)
{
	int special = 0, l = username.length();
	for (int i = 0; i < l; i++)
	{
		char s = username.at(i);

		//no spaces allowed
		if (s == ' ')
			return 0;

		//characters other than alphabets and numbers
		if (isalnum(s))
			continue;
		else
		{
			//periods and underscore allowed but only one
			if (s == '_' || s == '.')
			{
				special++;
				if (special > 1)
					return 0;
			}
			else
				return 0;
		}
	}
	return 1;
}

void Menu::renderPlayOpt() {
	int c, slt = 0;
	bool loadPlayOpt = true;
	while (loadPlayOpt) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:			//move up
			if (slt == 0) break;
			slt--;
			ArrowUp(left, top, slt);
			break;
		case 5:			//move down
			if (slt == playOptions.size() - 1) break;
			slt++;
			ArrowDown(left, top, slt);
			break;
		case 6:			//enter
			switch (slt) {
			case 0:
				delete game;
				runGame = true;
				game = new Game();
				do {
					Common::clearConsole();
					printTitle();
					game->inputName();
				} while (!validates(game->getName())||game->getName().size()<3);
				game->runGame();
				
				runGame = false;
				loadPlayOpt = false;
				break;
			case 1:
				renderContinueOptScreen();
				runGame = false;
				loadPlayOpt = false;
				return;
			case 2:
				return;
			}
			break;
		}
	}
}

void Menu::renderPlayOptScreen() {
	initPlayOpt();
	renderPlayOpt();
}

//###############################################//

//Continue
void Menu::renderContinueTexts(vector<string> text, int left, int top) {
	int width = 41;
	for (int i = 0; i < fileData.size()-1; i++) {
		Common::gotoXY((width - (text[i].length()-9)) / 2 + left, top + i * 2);
		cout << text[i].substr(5, text[i].length() - 9);
	}
	Common::gotoXY((width - text[fileData.size() - 1].length()) / 2 + left, top + (fileData.size()-1)  * 2);
	cout << text[fileData.size() - 1];
}

void Menu::initContinueOpt() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	loadFileData("listData.txt");
	renderOptionsBox(fileData.size());
	renderContinueTexts(fileData, left - 9, top + 1);
	renderArrowsOpt(0);
}

void Menu::renderContinueOpt()
{
	int c, slt = 0;
	bool loadContinueOpt = true;
	while (loadContinueOpt) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:			//move up
			if (slt == 0) break;
			slt--;
			ArrowUp(left, top, slt);
			break;
		case 5:			//move down
			if (slt == fileData.size() - 1) break;
			slt++;
			ArrowDown(left, top, slt);
			break;
		case 6:			//enter
			if (slt != fileData.size()-1) {
				delete game;
				runGame = true;

				game = new Game();
				game->continueGame(fileData[slt]);

				runGame = false;
				loadContinueOpt = false;
				break;
			}
			else if (slt == fileData.size() - 1) {
				return;
			}
			break;
		}
	}
}

void Menu::renderContinueOptScreen() {
	initContinueOpt();
	renderContinueOpt();
}

//##################################################//

void Menu::loadFileData(string fileName) {
	ifstream fin(fileName);
	vector<string> fileDataTemp;
	fileData.clear();

	while (!fin.eof()) {
		string name;
		getline(fin, name, '\n');
		if (name == "") break;
		fileData.push_back(name);
	}

	fileData.push_back("Back");
	fin.close();
}

void Menu::initLeaderBoard() {
	Common::setupConsole(18, BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	printTitle();
	renderLeaderBox();
	renderLeaderText();
}

void Menu::renderLeaderText()
{
	topLeader();
	int x = 70, y = 19;
	Common::gotoXY(x + 1, y -2); cout << "NAME";
	Common::gotoXY(x + 14, y-2 ); cout << "LEVEL";
	for (int i = 1; i < 19; i++)
	{
		Common::gotoXY(x+i, y - 1); putchar(196);
	}

	int i = 0;
	for (auto& it:topSeven)
	{
		if (it.name == "") continue;
		Common::gotoXY(x + 1, y  + i);
		cout << it.name;
		Common::gotoXY(x + 17, y + i);
		cout << it.score;
		i++;
	}
}

void Menu::renderLeaderBox()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int x = 67, y = 13;
	Common::gotoXY(x, y); putchar(201);
	Common::gotoXY(x + 25, y); putchar(187);
	Common::gotoXY(x, y + 14); putchar(200);
	Common::gotoXY(x + 25, y + 14); putchar(188);
	for (int i = y + 1; i < y + 14; i++)
	{
		Common::gotoXY(x, i); putchar(186);
		Common::gotoXY(25 + x, i); putchar(186);

	}
	for (int i = x + 1; i < x + 25; i++)
	{
		Common::gotoXY(i, y); putchar(205);
		Common::gotoXY(i, y + 14); putchar(205);

	}

	Common::gotoXY(x + 4, y + 1); putchar(201);
	Common::gotoXY(x + 5, y + 1); putchar(205);
	Common::gotoXY(x + 20, y + 1); putchar(187);
	Common::gotoXY(x + 19, y + 1); putchar(205);
	Common::gotoXY(x + 4, y + 3); putchar(200);
	Common::gotoXY(x + 5, y + 3); putchar(205);
	Common::gotoXY(x + 20, y + 3); putchar(188);
	Common::gotoXY(x + 19, y + 3); putchar(205);

	Common::gotoXY(x + 6, y + 2); cout << "  HIGHSCORE";
	Common::gotoXY(x + 10, y + 13); cout << char(175)<<"EXIT"<<char(174);
}

void Menu::renderLeaderBoard() {
	initLeaderBoard();
	while (true) {
		if(Common::getConsoleInput() == 6) break;
	}
}

void Menu::topLeader()
{
	topSeven.clear();
	ifstream fin;
	fin.open("listData.txt");

	vector<string> tempList;

	while (!fin.eof())
	{
		string temp;
		getline(fin, temp);
		tempList.push_back(temp);
	}
	for (int i = 0; i < tempList.size(); i++)
	{
		ifstream data(tempList[i]);
		player temp;
		getline(data, temp.name);
		data >> temp.score;
		topSeven.push_back(temp);
		data.close();
	}

	sort(topSeven.begin(), topSeven.end(), 
		[](player p1, player p2) {
			return p1.score > p2.score;
		}
	);
}