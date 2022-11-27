#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	name = "";
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

void Game::runGame(int mode, string fileName) {
	Common::clearConsole();
	if (mode == 1) {
		initGameData(1);
	}
	else {
		initGameFromFile(fileName);
	}
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

				t_game = thread(&Game::pauseGame, this);
			}
			else {
				running = true;
				t_game.join();

				while (_kbhit())//clear up buffer 
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

	while (running) {
		updateVehicle();
		updateAnimal();
		human->move();

		if (human->checkImpact()) {
			break;
		}

		Sleep(frame);
	}
}

void Game::pauseGame() {
	drawPauseMenu(options);


	while (!running) {
		//handling user's input here
	}
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

void Game::initGameFromFile(string fileName) {
	laneOpt = new string[5];
	int rowSpacing = 0;
	int laneSpacing = 0;
	ifstream fin;
	fin.open(fileName);
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
	Common::gotoXY(80, 40);
	cout << "Enter your name: ";
	cin >> name;
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

void Game::saveGame() {
	string dataName;
	string temp;

	dataName = "Data\\" + name + ".txt";
	temp = "Data\\" + name;

	ifstream fin;
	fin.open("listData.txt");

	bool appeared = 0;
	string temp1;
	while (!fin.eof()) {
		getline(fin, temp1, '\n');
		if (temp1 == temp) {
			appeared = 1;
		}
	}
	fin.close();
	ofstream fout;

	if (appeared == 0) {
		fout.open("listData.txt", ios::app);
		fout << temp << ".txt" << endl;
		fout.close();
	}

	fout.open(dataName);
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
	for (int i = 0; i < vh.size(); i++) {
		fout << vh[i]->getX() << " ";
	}
	fout << endl;

}

void Game::savePosAnimal(ofstream& fout) {
	for (int i = 0; i < an.size(); i++) {
		fout << an[i]->getX() << " ";
	}
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

void Game::renderPauseCurOpt() {
	int c = -1, pauseSlt = 0;
	bool loadPause = true;
	while (loadPause) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (pauseSlt == 0) break;
			pauseSlt--;
			//ArrowUp(pauseSlt);
			break;
		case 5:								//move down
			if (pauseSlt == options.size() - 1) break;
			pauseSlt++;
			//ArrowDown(pauseSlt);
			break;
		case 6:								//enter
			switch (pauseSlt) {
			case 0:							//Continue

				break;
			case 1:							//Save
				break;
			case 2:							
				break;
			case 3:
				break;
			}
		}
	}
}

void Game::drawPauseMenu(vector<string>& options) {
	int width = 30, height = 10;

	int left = WIDTH_GAMEBOARD + LEFT_GAMEBOARD + 5;
	int top = TOP_GAMEBOARD + 15;

	drawSquare(left, top, width, height);

	for (int i = 0; i < options.size(); i++) {
		Common::gotoXY((width - options[i].length()) / 2 + left, 2 + top + i * 2);
		cout << options[i];
	}
}