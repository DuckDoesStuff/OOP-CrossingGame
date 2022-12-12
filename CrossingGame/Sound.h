#pragma once
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

#define NONE -1
#define THEME 0
#define CAR 1
#define TRUCK 2
#define CAMEL 3
#define DUCK 4
#define MOVE 5

class Sound {
private:
	bool bg_theme = true;
	bool move_eff = true;
	bool animal_eff = true;
	bool vehicle_eff = true;
	int volume = 100;

	bool sound_running = true;
	bool changeVolume = true;

	static Sound* instance;
	Sound();
public:
	int soundSelector = NONE;
	~Sound();
	static Sound* getInstance() {
		if (instance == nullptr)
			instance = new Sound;
		
		return instance;
	}

	void openSound();
	void playBg();
	void stopBg();

	void toggleTheme() { bg_theme = !bg_theme; }
	void toggleMoving() { move_eff = !move_eff; }
	void toggleAnimal() { animal_eff = !animal_eff; }
	void toggleVehicle() { vehicle_eff = !vehicle_eff; }

	void volumeUp() { 
		changeVolume = true;
		volume = volume >= 100 ? 100 : volume + 5; 
	}
	void volumeDown() {
		changeVolume = true;
		volume = volume <= 0 ? 0 : volume - 5;
	}
	void setVolume();
	int getVolume() { return volume; }

	void loadSettings();
	void saveSettings();

	void runHandle();
	void stopHandle();
};

