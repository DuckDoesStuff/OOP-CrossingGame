#pragma once
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

class Sound {
private:
	bool sound_running = true;
	bool bg_theme = true;
	bool sound_eff = true;
	bool animal_eff = true;
	bool vehicle_eff = true;
	int volume = 100;

	bool changeVolume = false;
public:
	Sound();
	~Sound();

	void openSound();

	void playBg();
	void stopBg();

	void toggleTheme() { bg_theme = !bg_theme; }
	void toggleSound() { sound_eff = !sound_eff; }
	void toggleAnimal() { animal_eff = animal_eff; }
	void toggleVehicle() { vehicle_eff = vehicle_eff; }

	void volumeUp() { 
		changeVolume = true;
		volume = volume >= 100 ? 100 : volume + 5; 
		changeVolume = false;
	}
	void volumeDown() {
		changeVolume = true;
		volume = volume <= 0 ? 0 : volume - 5;
		changeVolume = false;
	}
	void setVolume();
	int getVolume() { return volume; }

	void loadSettings();
	void saveSettings();

	void runHandle();
	void stopHandle() { sound_running = false; }
};

