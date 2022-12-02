#pragma once
#include <thread>
#include <mutex>
#include <unordered_map>
#include "Common.h"
#include "People.h"

#include "Car.h"
#include "Truck.h"
#include "Camel.h"
#include "Horse.h"

#define _numOfLane 5

class Game {
private:
	int level;
	int frame;
	bool running;
	string name;							//username
	string filename;						//save filename
	vector<pair<int, int>> trafficTimer;	//{timer}
	vector<string> options = { "Back to game", "Settings", "Back to menu"};
	string* laneOpt;						//save lane

	int numOfObjs;
	People* human;
	vector<Vehicle*> vh;
	vector<Animal*> an;
	
	thread t_game;
public:
	Game();
	~Game();

	int check = 0 ;

	//******************************************//

	void start();
	bool runGame(int );
	void continueGame(string);
	void gameHandle();
	void playGame();
	void pauseGame();
	void displayInfo();

	//******************************************//

	template <class T> 
	void initLane(vector<T*>&, T*, int, int, int, int);
	void initGameData(int);
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

	void savePosVehicle(ofstream&);
	void savePosAnimal(ofstream&);
	void saveLane(ofstream&);
	void saveTraffic(ofstream&);


	//******************************************//

	void setLevel(int n) { level = n; }
	int getLevel() { return level; }

	//******************************************//

	void renderPauseCurOpt(int, int, int, int);
	void drawPauseMenu(int, int, int, int, vector<string>&);
	void erasePauseMenu(int, int, int, int);

	//******************************************//
	
	int askPlayer();
	void arrowLeft(int, int, int);
	void arrowRight(int, int, int);

	//******************************************//

	void deleteVe(vector<Vehicle*>& vh);
	void deleteAn(vector<Animal*>& an);

};
