#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	name = "";
	level = 0;
	human = nullptr;
	numOfObjs = 0;
	frame = 0;
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
	delete []laneOpt;
	laneOpt = nullptr;

	trafficLane.clear();
}

//******************************************//

void Game::runGame() {
	Common::clearConsole();
	initGameData(1);
	playGame();
}

void Game::continueGame(string fileName) {
	Common::clearConsole();
	initGameFromFile(fileName);
	playGame();
}

void Game::playGame()
{
	drawBoardGame();
	drawTraffic();
	drawPeople();

	DrawObj(vh);
	DrawObj(an);

	Sleep(10);
	while (true) {
		updateVehicle();
		updateAnimal();

		human->move();
		quitGame();
		if (human->checkImpact()) {
			break;
		}
		if (Common::pressedKey(P)) {
			saveGame();
			break;
		}
		Sleep(frame);
	}
}

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
		if(vh[j]->getSpeed() > 0)
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

void Game::inputName() {
	Common::gotoXY(80, 40);
	cout << "Enter your name: ";
	cin >> name;
}

void Game::quitGame() {
	int c = Common::getConsoleInput();
	if (c == 6) out = true;
}


//******************************************//
void Game::saveGame() {
	string dataName;
	dataName = "Data\\" + name + ".txt";

	ofstream fout;

	fout.open("listData.txt", ios::app);
	fout << dataName << endl;
	fout.close();

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

void Game::saveLane(ofstream& fout) {
	for (int i = 0; i < _numOfLane; i++) {
		fout << laneOpt[i] << " ";
	}
	fout << endl;
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

//******************************************//