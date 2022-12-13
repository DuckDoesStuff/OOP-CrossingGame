#pragma once
#include <thread>
#include <unordered_map>
#include "Common.h"
#include "Sound.h"
#include "People.h"
#pragma warning( disable : 4996 ) 

#include <conio.h> 
#include "Car.h"
#include "Truck.h"
#include "Camel.h"
#include "Horse.h"

#define LOSE 0
#define WIN 1
#define REPLAY 2

#define _numOfLane 5

class Game {
private:
	int level;
	int frame;
	bool t_running;
	bool pass;
	int gameResult;
	bool quit;

	string name;							//username
	string filename;						//save filename
	vector<pair<int, int>> trafficTimer;	//{timer}
	vector<string> pauseOptions = { "Back to game", "Settings", "Back to menu"};
	vector<string> settingsOptions = { "Volume", "Background music","Vehicle sound", "Animal sound", "Moving sound", "Back" };
	string* laneOpt;						//save lane

	int numOfObjs;
	People* human;
	vector<Vehicle*> vh;
	vector<Animal*> an;

	//Pause menu properties
	int left = WIDTH_GAMEBOARD + LEFT_GAMEBOARD + 5;
	int top = TOP_GAMEBOARD + 15;
	int width = 30, height = 8;

	thread t_game;
	Sound* sound;
public:
	Game();
	~Game();


	//******************************************//

	void runGame();
	void continueGame(string);
	void gameHandle();
	void playGame();
	void pauseGame();
	void displayInfo();

	//******************************************//

	template <class T>
	void initLane(vector<T*>&, T*, int, int, int, int);
	void initGameData();
	void initGameFromFile();

	//******************************************//

	template <class T>
	void DrawObj(vector<T*>);
	void drawBoardGame();
	void drawPeople();
	void drawSquare(const int&, const int&, const int&, const int&);

	void inputName();

	//******************************************//

	void updateVehicle();
	void updateAnimal();
	void setTraffic();
	void drawTraffic();

	//******************************************//
	//save game
	bool askToSave();
	string inputSaveFile();
	void saveGame();

	//******************************************//

	void savePosVehicle(ofstream&);
	void savePosAnimal(ofstream&);
	void saveLane(ofstream&);
	void saveTraffic(ofstream&);


	//******************************************//

	void setLevel(int n) { level = n; }
	int getLevel() { return level; }

	//******************************************//

	void renderPauseMenu();
	void erasePauseMenu();

	//******************************************//

	void renderSettingMenu();
	void eraseSettingMenu();
	void renderVolume();

	//******************************************//

	int askPlayer();
	void arrowLeft(int, int, int);
	void arrowRight(int, int, int);

	//******************************************//
	void resetData();
	//--------------
	void Deathscreen();
	void Winscreen();
	//----------
	string getName();
};
