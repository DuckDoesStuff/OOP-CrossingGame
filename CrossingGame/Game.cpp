#include "Game.h"

Game::Game()
{
	srand((unsigned)time(0));
	name = "";
	filename = "";
	level = 0;
	human = nullptr;
	numOfObjs = 0;
	frame = 0;
	laneOpt = nullptr;
	running = true;
}

Game::~Game()
{
	delete human;
	human = nullptr;

	for (int i = 0; i < vh.size(); i++) {
		delete vh[i];
		vh[i] = nullptr;
	}

	for (int i = 0; i < an.size(); i++) {
		delete an[i];
		an[i] = nullptr;
	}
	delete[]laneOpt;
	laneOpt = nullptr;
}

//******************************************//

void Game::runGame() {
	inputName();
	Common::clearConsole();
	initGameData(1);
	displayInfo();
	gameHandle();
}

void Game::continueGame(string fileName) {
	Common::clearConsole();
	filename = fileName;
	initGameFromFile();
	displayInfo();
	gameHandle();
}

void Game::gameHandle()
{
	t_game = thread(&Game::playGame, this);
	running = true;

	while (human->isAlive()) {
		if (Common::pressedKey(P)) {
			if (running) {
				running = false;
				t_game.join();

				pauseGame();
				t_game = thread(&Game::playGame, this);
			}
			else {
				running = true;

				while (_kbhit())				//clear up buffer 
					char c  = _getch();
				t_game = thread(&Game::playGame, this);
			}
		}
	}
	if (t_game.joinable()) t_game.join();
}

void Game::playGame() {
	drawBoardGame();
	drawTraffic();
	drawPeople();
	DrawObj(vh);
	DrawObj(an);

	int a, b; //nhunnhun de tam de check cai hop ask hoi
	a = human->getCoords().first; //nhunnhun de tam de check cai hop ask hoi
	b = human->getCoords().second; //nhunnhun de tam de check cai hop ask hoi
	int check = 0; //nhunnhun de tam de check cai hop ask hoi

	while (running) {
		updateVehicle();
		updateAnimal();
		human->move();

		if (human->checkImpact()) {
			human->dieAnimation();

			//nhunnhun de tam de check cai hop ask hoi
			if (askPlayer() == 0) {
				Common::clearConsole();
				check = 1;
			}
			else {
				break;
			}

		}

		//nhunnhun de tam de check cai hop ask hoi
		if (check == 1) {
			drawBoardGame();
			human->loadImage(1);
			human->setCoords(a, b);
			human->drawToScreen();
			check = 0;
		}

		Sleep(frame);
	}
}

void Game::pauseGame() {
	int left = WIDTH_GAMEBOARD + LEFT_GAMEBOARD + 5;
	int top = TOP_GAMEBOARD + 15;
	int width = 30, height = 10;

	drawPauseMenu(left, top, width, height, options);
	renderPauseCurOpt(left, top, width, height);
	erasePauseMenu(left, top, width, height);
}

void Game::displayInfo() {
	int left = LEFT_GAMEBOARD + WIDTH_GAMEBOARD + 5;
	int top = TOP_GAMEBOARD - 5;

	int width = 30, height = 10;

	drawSquare(left, top, width, height);

	Common::gotoXY(left + 1, top + 1);
	cout << "Player: " << name;
	Common::gotoXY(left + 1, top + 2);
	cout << "Level: " << level;
}

//******************************************//

template <class T>
void Game::initLane(vector<T*>& v, T* obj, int numOfObjs, int rowSpacing, int laneSpacing, int i) {
	rowSpacing = (WIDTH_GAMEBOARD - numOfObjs * obj->getWidth()) / numOfObjs;
	obj->setCoords(LEFT_GAMEBOARD + 1 + i * (obj->getWidth() + rowSpacing), TOP_GAMEBOARD + 1 + laneSpacing);
	v.push_back(obj);
}

void Game::initGameData(int l)
{
	level = l;

	int animalCount = 0;
	int vehicleCount = 0;

	if (level == 1) {
		numOfObjs = 2;
		frame = 60;

		animalCount = 1;
		vehicleCount = 4;
	}
	else {
		numOfObjs = 3;
		frame = 45;

		animalCount = 2;
		vehicleCount = 3;
	}

	int rowSpacing = 0;
	int laneSpacing = 0;
	unordered_map<int, string> lane;
	laneOpt = new string[5];

	//Picking animal lane
	for (int i = 0; i < animalCount; i++) {
		int randomIndex;
		do {
			randomIndex = rand() % _numOfLane;
		} while (lane.find(randomIndex) != lane.end());
		lane.insert({ randomIndex, "animal" });
		laneOpt[randomIndex] = "animal";
	}

	//Picking vehicle lane
	for (int i = 0; i < vehicleCount; i++) {
		int randomIndex;
		do {
			randomIndex = rand() % _numOfLane;
		} while (lane.find(randomIndex) != lane.end());
		lane.insert({ randomIndex, "vehicle" });
		laneOpt[randomIndex] = "vehicle";
	}

	for (int i = 0; i < _numOfLane; i++) {
		if (lane[i] == "animal")
			for (int j = 0; j < numOfObjs; j++) {
				Animal* obj;
				if (i % 2 == 0)
					obj = new Horse(0);
				else
					obj = new Camel(0);
				initLane(an, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		else if (lane[i] == "vehicle") {
			int laneTimer = rand() % (frame - (frame + 30) + 1) + frame;
			trafficTimer.push_back({ laneTimer, laneTimer });
			for (int j = 0; j < numOfObjs; j++) {
				Vehicle* obj;
				if (i % 2 == 0)
					obj = new Car(0);
				else
					obj = new Truck(0);
				initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		}
		laneSpacing += 5;
	}

	human = new People(LEFT_GAMEBOARD + WIDTH_GAMEBOARD / 2, HEIGHT_GAMEBOARD + 6);
	human->setVehicle(vh);
	human->setAnimal(an);
}

void Game::initGameFromFile() {
	laneOpt = new string[5];
	int rowSpacing = 0;
	int laneSpacing = 0;
	ifstream fin;
	fin.open(filename);
	int mX, mY;
	fin >> name;
	fin >> level;
	if (level == 1) {
		numOfObjs = 2;
		frame = 60;
	}
	else {
		numOfObjs = 3;
		frame = 45;
	}

	fin >> mX;
	fin >> mY;
	for (int i = 0; i < _numOfLane; i++) {
		fin >> laneOpt[i];
	}

	for (int i = 0; i < _numOfLane; i++) {
		if (laneOpt[i] == "animal")
			for (int j = 0; j < numOfObjs; j++) {
				Animal* obj;
				if (i % 2 == 0)
					obj = new Horse(0);
				else
					obj = new Camel(0);
				initLane(an, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		else if (laneOpt[i] == "vehicle") {
			int laneTimer = rand() % (frame - (frame + 30) + 1) + frame;
			trafficTimer.push_back({ laneTimer, laneTimer });
			for (int j = 0; j < numOfObjs; j++) {
				Vehicle* obj;
				if (i % 2 == 0)
					obj = new Car(0);
				else
					obj = new Truck(0);
				initLane(vh, obj, numOfObjs, rowSpacing, laneSpacing, j);
			}
		}
		laneSpacing += 5;
	}
	for (int i = 0; i < vh.size(); i++) {
		int temp;
		fin >> temp;
		vh[i]->setmX(temp);
	}
	for (int i = 0; i < an.size(); i++) {
		int temp;
		fin >> temp;
		an[i]->setmX(temp);
	}
	for (int i = 0; i < trafficTimer.size(); i++) {
		fin >> trafficTimer[i].first >> trafficTimer[i].second;
	}
	for (int i = 0; i < vh.size(); i++) {
		int temp;
		fin >> temp;
		vh[i]->setMoving(temp);
	}
	human = new People(mX, mY);
	human->setVehicle(vh);
	human->setAnimal(an);

	fin.close();
}

//******************************************//

template <class T>
void Game::DrawObj(vector<T*> v) {
	for (int i = 0; i < v.size(); i++)
		v[i]->drawToScreen();
}

void Game::drawBoardGame()
{
	int left = LEFT_GAMEBOARD, top = TOP_GAMEBOARD;
	int boxW = WIDTH_GAMEBOARD, boxH = 5;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int box;
	for (int j = 0; j < boxW; j++) {
		Common::gotoXY(left + j, top - boxH);
		putchar(205);
	}
	for (int j = 0; j < boxH; j++) {
		Common::gotoXY(left, top - boxH + j);
		putchar(186);
		Common::gotoXY(left + boxW, top - boxH + j);
		putchar(186);
	}

	Common::gotoXY(left, top - boxH);
	putchar(201);
	Common::gotoXY(left + boxW, top - boxH);
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
		Common::gotoXY(left + j, top + boxH * _numOfLane + boxH);
		putchar(205);
	}
	for (int j = 0; j < boxH; j++) {
		Common::gotoXY(left, top + boxH * _numOfLane + j);
		putchar(186);
		Common::gotoXY(left + boxW, top + boxH * _numOfLane + j);
		putchar(186);
	}

	Common::gotoXY(left, top + boxH * _numOfLane + boxH);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane + boxH);
	putchar(188);

	Common::gotoXY(left, top + boxH * _numOfLane);
	putchar(204);
	Common::gotoXY(left + boxW, top + boxH * _numOfLane);
	putchar(185);
}

void Game::drawPeople() {
	human->drawToScreen();
}

void Game::drawSquare(const int& left, const int& top, const int& width, const int& height) {
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Common::gotoXY(left + j, top + i);
			putchar(' ');
		}
	}

	Common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < width; i++) {
		Common::gotoXY(left + i, top);
		putchar(205);
		Common::gotoXY(left + i, top + height);
		putchar(205);
	}
	Common::gotoXY(left + width, top);
	putchar(187);

	Common::gotoXY(left, top + height);
	putchar(200);
	for (int i = 1; i < height; i++) {
		Common::gotoXY(left, top + i);
		putchar(186);
		Common::gotoXY(left + width, top + i);
		putchar(186);
	}
	Common::gotoXY(left + width, top + height);
	putchar(188);
}

void Game::inputName() {
	Common::gotoXY(70, 20);
	cout << "Enter your name: ";
	getline(cin, name);
}

//******************************************//

void Game::updateVehicle() {
	for (int i = 0; i < vh.size(); i++) {
		vh[i]->updatePos();
	}
	setTraffic();
}

void Game::setTraffic() {
	int index = 0;
	for (int j = 0; j <= vh.size() - numOfObjs; j += numOfObjs) {
		//int index = (vh[j]->getY() - 1 - TOP_GAMEBOARD) / 5;
		if (trafficTimer[index].first > 0)
			trafficTimer[index].first--;
		else {
			for (int i = 0; i < numOfObjs; i++) {
				vh[j + i]->startORstop();
				drawTraffic();
				trafficTimer[index].first = trafficTimer[index].second;
			}
		}
		index++;
	}
}

void Game::drawTraffic() {
	for (int j = 0; j <= vh.size() - numOfObjs; j += numOfObjs) {
		if (vh[j]->getSpeed() > 0)
			Common::gotoXY(LEFT_GAMEBOARD + WIDTH_GAMEBOARD + 1, vh[j]->getY() + 1);
		else
			Common::gotoXY(LEFT_GAMEBOARD - 1, vh[j]->getY() + 1);


		if (vh[j]->isMoving())
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		else
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_RED);
		cout << "@";
	}
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
}

void Game::updateAnimal() {
	for (int i = 0; i < an.size(); i++) {
		an[i]->updatePos();
	}
}

//******************************************//

bool Game::askToSave() {
	int width = 30, height = 7;
	int left = 65;
	int top = 14;

	drawSquare(left, top, width, height);
	Common::gotoXY(left + 3, top + 2);
	cout << "Do you want to save before";
	Common::gotoXY(left + 10, top + 3);
	cout << "you leave ?";
	Common::gotoXY(left + 8, top + 5);
	cout << "Yes";
	Common::gotoXY(left + 20, top + 5);
	cout << "No";
	int c = 0, slt = 0;
	arrowLeft(left + 8, top + 5, slt);
	

	while (true) {
		c = Common::getConsoleInput();
		switch (c) {
		case 3:					//move left
			if (slt == 0) break;
			slt--;
			arrowLeft(left + 8, top + 5, slt);
			break;
		case 4:					//move right
			if (slt == 1) break;
			slt++;
			arrowRight(left + 8, top + 5, slt);
			break;
		case 6:					//enter
			return slt;
		}
	}
	return 0;
}

string Game::inputSaveFile() {
	int width = 30, height = 7;
	int left = 65;
	int top = 14;
	drawSquare(left, top, width, height);
	

	ifstream fin("listData.txt");
	vector<string> fileList;
	while (!fin.eof()) {
		string tmp;
		getline(fin, tmp);
		fileList.push_back(tmp);
	}
	fin.close();

	string file;
	Common::gotoXY(left + 2, top + 1);
	cout << "Enter save file: (no space)";

	//need to check for valid input
	bool fileExist = true;
	while (fileExist) {
		Common::gotoXY(left + 2, top + 3);
		cin >> file;
		if (file.length() > 10)
			file = file.substr(0, 10);
		file = "Data\\" + file + ".txt";

		fileExist = false;
		for (int i = 0; i < fileList.size(); i++) {
			if (file == fileList[i]) {
				fileExist = true;
				Common::gotoXY(left + 7, top + 2);
				Common::setConsoleColor(BRIGHT_WHITE, RED);
				cout << "File already exist!";
				Common::gotoXY(left + 2, top + 3);
				cout << "                         ";
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				break;
			}
		}
	}

	return file;
}

void Game::saveGame() {
	if (askToSave()) return;
	//if opened from a save file then save and leave
	//if not then ask user's to input file name


	if (filename == "") 
		filename = inputSaveFile();


	ifstream fin("listData.txt");
	vector<string> fileList;
	fileList.push_back(filename);
	while (!fin.eof() && fileList.size() < 8) {
		string tmp;
		getline(fin, tmp);
		if (tmp == filename) continue;
		fileList.push_back(tmp);
	}
	fin.close();

	ofstream fout("listData.txt");
	for (int i = 0; i < fileList.size(); i++) {
		fout << fileList[i] << endl;
	}
	fout.close();

	fout.open(filename);
	fout << name << endl;
	fout << level << endl;
	fout << human->getCoords().first << " " << human->getCoords().second << endl;
	saveLane(fout);
	savePosVehicle(fout);
	savePosAnimal(fout);
	saveTraffic(fout);
	fout.close();
}


void Game::savePosVehicle(ofstream& fout) {
	for (int i = 0; i < vh.size(); i++) 
		fout << vh[i]->getX() << " ";
	
	fout << endl;

}

void Game::savePosAnimal(ofstream& fout) {
	for (int i = 0; i < an.size(); i++)
		fout << an[i]->getX() << " ";

	fout << endl;
}

void Game::saveLane(ofstream& fout) {
	for (int i = 0; i < _numOfLane; i++) {
		fout << laneOpt[i] << " ";
	}
	fout << endl;
}

void Game::saveTraffic(ofstream& fout) {
	for (int i = 0; i < trafficTimer.size(); i++) {
		fout << trafficTimer[i].first << " " << trafficTimer[i].second << " ";
	}
	fout << endl;
	for (int i = 0; i < vh.size(); i++) {
		fout << vh[i]->isMoving() << " ";
	}
	fout << endl;
}

//******************************************//

void Game::renderPauseCurOpt(int left, int top, int width, int height) {
	int pauseSlt = 0;
	top += 2;

	Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 3), top);
	cout << ">>";
	Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 1 + options[pauseSlt].length() + 2), top);
	cout << "<<";

	int c = -1;
	while (!running) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (pauseSlt == 0) break;
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 1 + options[pauseSlt].length() + 2), top);
			cout << "  ";
			top -= 2;
			pauseSlt--;
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 1 + options[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 5:								//move down
			if (pauseSlt == options.size() - 1) break;
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 1 + options[pauseSlt].length() + 2), top);
			cout << "  ";
			top += 2;
			pauseSlt++;
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - options[pauseSlt].length()) / 2 - 1 + options[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 6:								//enter
			switch (pauseSlt) {
			case 0:
				running = true;				//Back to game
				break;
			case 1:							//Settings
				break;
			case 2:							//Main menu
				human->setAlive(false);
				saveGame();
				running = false;
				return;
				break;
			}
		}
	}
}

void Game::drawPauseMenu(int left, int top, int width, int height, vector<string>& options) {

	drawSquare(left, top, width, height);

	for (int i = 0; i < options.size(); i++) {
		Common::gotoXY((width - options[i].length()) / 2 + left, 2 + top + i * 2);
		cout << options[i];
	}
}

void Game::erasePauseMenu(int left, int top, int width, int height) {
	for (int i = 0; i <= height; i++) 
		for (int j = 0; j <= width; j++) {
			Common::gotoXY(left + j, top + i);
			putchar(' ');
		}
}

//******************************************//

int Game::askPlayer() {
	int width = 30, height = 7;
	int left = 65;
	int top = 14;
	drawSquare(left, top, width, height);
	Common::gotoXY(left + 3, top + 2);
	cout << "Do you want to play again?";
	Common::gotoXY(left + 8, top + 5);
	cout << "Yes";
	Common::gotoXY(left + 20, top + 5);
	cout << "No";
	int c, slt = 0;
	arrowLeft(left + 8, top + 5, slt);

	bool ask = true;
	while (ask) {
		c = Common::getConsoleInput();
		switch (c) {
		case 3:			//move up
			if (slt == 0) break;
			slt--;
			arrowLeft(left + 8, top + 5, slt);
			break;
		case 4:			//move down
			if (slt == 2 - 1) break;
			slt++;
			arrowRight(left + 8, top + 5, slt);
			break;
		case 6:			//enter
			switch (slt) {
			case 0:
				ask = false;
				return 0;
			case 1:
				ask = false;
				return 1;
			}
		}
	}
	return 0;
}

void Game::arrowLeft(int left, int top, int slt) {
	left -= 3;
	Common::gotoXY(left + 12 * (slt + 1), top);
	cout << "  ";
	Common::gotoXY(left + 12 * (slt + 1) + 6, top);
	cout << "  ";
	Common::gotoXY(left + 12 * (slt), top);
	cout << ">>";
	Common::gotoXY(left + 12 * (slt) + 7, top);
	cout << "<<";
}

void Game::arrowRight(int left, int top, int slt) {
	left -= 3;
	Common::gotoXY(left + 12 * (slt - 1), top);
	cout << "  ";
	Common::gotoXY(left + 12 * (slt - 1) + 7, top);
	cout << "  ";
	Common::gotoXY(left + 12 * (slt), top);
	cout << ">>";
	Common::gotoXY(left + 12 * (slt) + 6, top);
	cout << "<<";
}