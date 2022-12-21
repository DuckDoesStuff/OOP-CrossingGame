#include "Game.h"
string Game::getName() {
	return name;
}
Game::Game()
{
	srand((unsigned)time(0));
	name = "";
	filename = "";
	level = 1;
	human = new People;
	numOfObjs = 0;
	frame = 0;
	laneOpt = nullptr;
	t_running = true;
	pass = false;
	gameResult = LOSE;
	quit = false;
	sound = Sound::getInstance();
}

Game::~Game()
{
	delete human;
	human = nullptr;

	resetData();

	delete[]laneOpt;
	laneOpt = nullptr;
}

//******************************************//

void Game::runGame() {

	while (!quit) {
		Common::clearConsole();
		initGameData();
		displayInfo();
		gameHandle();
	}

	if (gameResult == WIN) {
		//endGame screen
		Common::clearConsole();
		cout << "YAY";
	}
}

void Game::continueGame(string fileName) {
	Common::clearConsole();

	filename = fileName;
	initGameFromFile();
	while (!quit) {
		Common::clearConsole();
		displayInfo();
		gameHandle();
		initGameData();
	}

	if (gameResult == WIN) {
		//endGame screen
		Common::clearConsole();
		cout << "YAY";
	}
}

void Game::gameHandle()
{
	t_game = thread(&Game::playGame, this);
	t_running = true;

	while (!quit) {
		if (Common::pressedKey(VK_ESCAPE)) {
			if (t_running) {
				t_running = false;
				t_game.join();

				pauseGame();
				t_game = thread(&Game::playGame, this);
			}
			else {
				t_running = true;

				while (_kbhit())				//clear up buffer 
					char c = _getch();
				t_game = thread(&Game::playGame, this);
			}
		}

		//player cross the street successfully
		if (human->getmY() == 2) {
			t_running = false;
			pass = true;

			// if (level == 10) {
			// 	gameResult = WIN;
			// 	quit = true;
			// 	break;
			// }
			level++;
			break;
		}

		if (human->checkImpact()) {
			human->setAlive(false);
			t_running = false;
			pass = false;

			t_game.join();

			human->dieAnimation();
			if (askPlayer() == 0)
				gameResult = REPLAY;
			else {
				quit = true;
				gameResult = LOSE;
				if (level < 8)
					Deathscreen();
				else
					Winscreen();
			}
			break;
		}
	}

	if (t_game.joinable()) t_game.join();
}
void Game::Winscreen(){
	Common::clearConsole();
	Common::fillConsole(BLACK);
	ifstream fin("ASCII\\winScreen.txt");
	int cnt = 0;
	Common::setConsoleColor(BLACK, YELLOW);
	while (!fin.eof())
	{
		string temp;
		getline(fin, temp);
		Common::gotoXY(15, 2 + cnt);
		cout << temp;
		cnt++;
	}

	drawSquare(63, 29, 40, 2);
	Common::gotoXY(70, 30); cout << " Press anykey to continue!!";
	fin.close();
	bool ask = true;
	int c;
		c = Common::getConsoleInput();
		while (ask) {
			c = getch();

			ask = false;
		}

}
void Game::Deathscreen() {
	Common::clearConsole();
	Common::fillConsole(BLACK);
	int cnt = 0;
	ifstream fin("ASCII\\deathscreen.txt");
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	while (!fin.eof())
	{
		string temp;
		getline(fin, temp);
		Common::gotoXY(1, 0 + cnt);
		cout << temp;
		cnt++;
	}
	fin.close();
	bool ask = true;
	int c;
	while (ask) {
		c = getch();

		ask = false;
	}
}

void Game::playGame() {
	drawBoardGame();
	drawTraffic();
	drawPeople();
	DrawObj(vh);
	DrawObj(an);

	while (t_running && human->isAlive()) {
		updateVehicle();
		updateAnimal();
		human->move();


		Sleep(frame);
	}
}

void Game::pauseGame() {
	renderPauseMenu();
	erasePauseMenu();
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

void Game::initGameData()
{
	if (gameResult == REPLAY) {
		level = 1;
		gameResult = LOSE;
	}
	pass = false;
	resetData();

	int animalCount = 0;
	int vehicleCount = 0;

	switch (level) {
		case 1: 
			numOfObjs = 2;
			frame = 60;

			animalCount = 1;
			vehicleCount = 4;
			break;
		case 2: 
			numOfObjs = 3;
			frame = 60;

			animalCount = 1;
			vehicleCount = 4;
			break;
		case 3: 
			numOfObjs = 3;
			frame = 50;

			animalCount = 1;
			vehicleCount = 4;
			break;
		case 4: 
			numOfObjs = 3;
			frame = 50;

			animalCount = 2;
			vehicleCount = 3;
			break;
		case 5: 
			numOfObjs = 3;
			frame = 50;

			animalCount = 3;
			vehicleCount = 2;
			break;
		case 6: 
			numOfObjs = 3;
			frame = 45;

			animalCount = 2;
			vehicleCount = 3;
			break;
		case 7: 
			numOfObjs = 3;
			frame = 45;

			animalCount = 3;
			vehicleCount = 2;
			break;
		case 8: 
			numOfObjs = 2;
			frame = 40;

			animalCount = 2;
			vehicleCount = 3;
			break;
		case 9: 
			numOfObjs = 2;
			frame = 40;

			animalCount = 2;
			vehicleCount = 3;
			break;
		case 10: 
			numOfObjs = 3;
			frame = 40;

			animalCount = 3;
			vehicleCount = 2;
			break;
		default:
			numOfObjs = 3;
			frame = 57-level;

			animalCount = 3;
			vehicleCount = 2;
			break;
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
	delete human;
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
	if (!fin.is_open()) {
		filename = "";
		initGameData();
		return;
	}

	int mX, mY;
	fin >> name;
	fin >> level;
	switch (level) {
	case 1:
		numOfObjs = 2;
		frame = 60;
		break;
	case 2:
		numOfObjs = 3;
		frame = 60;
		break;
	case 3:
		numOfObjs = 3;
		frame = 50;
		break;
	case 4:
		numOfObjs = 3;
		frame = 50;
		break;
	case 5:
		numOfObjs = 3;
		frame = 50;
		break;
	case 6: 
		numOfObjs = 3;
		frame = 45;
		break;
	case 7: 
		numOfObjs = 3;
		frame = 45;
		break;
	case 8: 
		numOfObjs = 2;
		frame = 40;
		break;
	case 9: 
		numOfObjs = 2;
		frame = 40;
		break;
	case 10: 
		numOfObjs = 3;
		frame = 40;
		break;
	default:
		numOfObjs = 3;
		frame = 57-level;
		break;
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
	//Init vehicles
	for (auto& it:vh) {
		int coords;
		fin >> coords;
		it->setmX(coords);
	}
	for (auto& it:vh) {
		int speed;
		fin >> speed;
		it->setSpeed(speed);
	}

	//Init animals
	for (auto& it:an) {
		int coords;
		fin >> coords;
		it->setmX(coords);
	}
	for (auto& it:an) {
		int speed;
		fin >> speed;
		it->setSpeed(speed);
		if (speed > 0)
			it->setImage(0);
		else
			it->setImage(1);
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
	//Common::setConsoleColor( BRIGHT_WHITE, BLACK );
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
	name.clear();
	Common::setConsoleColor(BRIGHT_WHITE, RED);
	Common::gotoXY(60, 21);
	cout <<"!) Can contain Number";
	Common::gotoXY(60, 22);
	cout<<"!) No special Characters";
	Common::gotoXY(60, 23);
	cout<< "!) Length must >3 and < 15";
	Common::gotoXY(60, 24);
	cout<< "!) Can have only 1[.] or [_]";

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	drawSquare(60, 18, 35, 2);
	Common::gotoXY(62, 19);
	char temp;
	cout << "Enter your name: ";
	while (1)
	{
		temp = getch();
		if ((int)temp == 13)
			break;
		if (name.size() >= 15)
		{ 
			if ((int)temp == 8)
				name.erase(name.end() - 1);
		}
		else {

			if ((int)temp == 8)
				name.erase(name.end() - 1);

			else {
				name += temp;

			}

		}
		for (int i = 0; i < 15; i++)
		{
			Common::gotoXY(79 + i, 19);
			cout << " ";
		}

		Common::gotoXY(79, 19);
		cout << name;
	}
	
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
		cout << char(219);
	}
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
}

void Game::updateAnimal() {
	for (int i = 0; i < an.size(); i++) 
	{
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
bool isValidFilename(const string& filename) {
	// Kiểm tra xem tên file có bắt đầu bằng ký tự . (dấu chấm) hoặc ký tự trắng hay không
	if (filename[0] == '.' || isspace(filename[0])) {
		return false;
	}

	// Duyệt qua từng ký tự trong tên file
	for (char c : filename) {
		// Nếu tên file chứa ký tự đặc biệt, trả về false
		if (!isalnum(c) && c != '.' && c != '_') {
			return false;
		}
	}

	// Nếu tên file không chứa ký tự đặc biệt, trả về true
	return true;
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
	bool isnotValid = true;
	while (isnotValid) {
		
		Common::gotoXY(left + 2, top + 2);
		cout << ">>                       ";
		Common::gotoXY(left + 5, top + 2);
		cin >> file;
		if (file.length() > 10)
			file = file.substr(0, 10);


		if (!isValidFilename(file))
		{
			isnotValid = true;
			Common::gotoXY(left + 7, top + 3);
			Common::setConsoleColor(BRIGHT_WHITE, RED);
			cout << "Invalid file name!!";
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		}
		else
			isnotValid = false;

		file = "Data\\" + file + ".txt";
		for (int i = 0; i < fileList.size(); i++) {
			if (file == fileList[i]) 
			{
				isnotValid = true;
				Common::gotoXY(left + 7, top + 3);
				Common::setConsoleColor(BRIGHT_WHITE, RED);
				cout << "File already exist!";
				Common::gotoXY(left + 7, top + 2);
				cout << ">>                       ";
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				break;
			}
		}
		
	}

	return file;
}

void Game::saveGame() {
	if (askToSave()) {
		human->setAlive(false);
		return;
	}
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
		if (tmp != filename)
			fileList.push_back(tmp);
	}
	fin.close();

	ofstream fout("listData.txt");
	for (int i = 0; i < fileList.size(); i++) {
		fout << fileList[i] << endl;
	}
	fout.close();

	fout.open(filename);


	if (name == "")
		fout << "Unknown" << endl;
	else
		fout << name << endl;
	fout << level << endl;
	fout << human->getCoords().first << " " << human->getCoords().second << endl;
	saveLane(fout);
	saveVehicle(fout);
	saveAnimal(fout);
	saveTraffic(fout);


	fout.close();
}

//******************************************//

void Game::saveVehicle(ofstream& fout) {
	for (auto& it:vh) 
		fout << it->getX() << " ";
	fout << endl;

	for (auto& it : vh)
		fout << it->getSpeed() << " ";
	fout << endl;
}

void Game::saveAnimal(ofstream& fout) {
	for (auto& it:an)
		fout << it->getX() << " ";
	fout << endl;

	for (auto& it : an)
		fout << it->getSpeed() << " ";
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

void Game::renderPauseMenu() {
	drawSquare(left, top, width, height);

	for (int i = 0; i < pauseOptions.size(); i++) {
		Common::gotoXY((int)((width - pauseOptions[i].length()) / 2 + left),(int)(2 + top + i * 2));
		cout << pauseOptions[i];
	}

	int pauseSlt = 0;
	int top = this->top;
	top += 2;

	Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
	cout << ">>";
	Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
	cout << "<<";

	int c = -1;
	while (!t_running) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (pauseSlt == 0) break;
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
			cout << "  ";
			top -= 2;
			pauseSlt--;
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 5:								//move down
			if (pauseSlt == pauseOptions.size() - 1) break;
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
			cout << "  ";
			top += 2;
			pauseSlt++;
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 6:								//enter
			switch (pauseSlt) {
			case 0:
				t_running = true;				//Back to game
				break;
			case 1:							//Open sound settings
				erasePauseMenu();
				renderSettingMenu();
				eraseSettingMenu();
				Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 3), top);
				cout << ">>";
				Common::gotoXY((int)(left + (width - pauseOptions[pauseSlt].length()) / 2 - 1 + pauseOptions[pauseSlt].length() + 2), top);
				cout << "<<";
				break;
			default:						//Main menu
				human->setAlive(false);
				saveGame();
				quit = true;
				t_running = false;
				return;
				break;
			}
		}
	}
}

void Game::erasePauseMenu() {
	for (int i = 0; i <= height; i++) 
		for (int j = 0; j <= width; j++) {
			Common::gotoXY(left + j, top + i);
			putchar(' ');
		}
}

//******************************************//

void Game::renderSettingMenu() {

	drawSquare(left, top, width, height + 6);

	for (int i = 0; i < settingsOptions.size(); i++) {
		Common::gotoXY((int)((width - settingsOptions[i].length()) / 2 + left), (int)(2 + top + i * 2));
		cout << settingsOptions[i];
	}

	int pauseSlt = 0;
	int top = this->top;
	top += 2;

	Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 3), top);
	cout << ">>";
	Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 1 + settingsOptions[pauseSlt].length() + 2), top);
	cout << "<<";

	int c = -1;
	bool settingMenu = true;
	while (settingMenu) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:								//move up
			if (pauseSlt == 0) break;
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 1 + settingsOptions[pauseSlt].length() + 2), top);
			cout << "  ";
			top -= 2;
			pauseSlt--;
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 1 + settingsOptions[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 5:								//move down
			if (pauseSlt == settingsOptions.size() - 1) break;
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 3), top);
			cout << "  ";
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 1 + settingsOptions[pauseSlt].length() + 2), top);
			cout << "  ";
			top += 2;
			pauseSlt++;
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 3), top);
			cout << ">>";
			Common::gotoXY((int)(left + (width - settingsOptions[pauseSlt].length()) / 2 - 1 + settingsOptions[pauseSlt].length() + 2), top);
			cout << "<<";
			break;
		case 6:								//enter
			switch (pauseSlt) {
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
			default:
				settingMenu = false;
				break;
			}
		}
	}
}

void Game::eraseSettingMenu() {
	for (int i = 0; i <= height + 6; i++)
		for (int j = 0; j <= width; j++) {
			Common::gotoXY(left + j, top + i);
			putchar(' ');
		}


	drawSquare(left, top, width, height);

	for (int i = 0; i < pauseOptions.size(); i++) {
		Common::gotoXY((width - pauseOptions[i].length()) / 2 + left, 2 + top + i * 2);
		cout << pauseOptions[i];
	}
}

void Game::renderVolume() {
	Common::gotoXY(left + 12, top + 2);
	cout << "      ";
	bool render = true;
	while (render) {
		Common::gotoXY(left + 14, top + 2);
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
	Common::gotoXY(left + 12, top + 2);
	cout << "      ";
	Common::gotoXY(left + 12, top + 2);
	cout << "Volume";
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
			if (slt == 1) break;
			slt++;
			arrowRight(left + 8, top + 5, slt);
			break;
		case 6:			//enter
			ask = false;
			break;
		}
	}
	return slt;
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

//******************************************//

void Game::resetData() {
	for (int i = 0; i < vh.size(); i++) {
		delete vh[i];
		vh[i] = nullptr;
	}
	vh.clear();

	for (int i = 0; i < an.size(); i++) {
		delete an[i];
		an[i] = nullptr;
	}
	an.clear();

	trafficTimer.clear();
}