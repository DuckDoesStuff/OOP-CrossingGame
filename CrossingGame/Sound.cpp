#include "Sound.h"

Sound::Sound() {
	loadSettings();
}

Sound::~Sound() {
	saveSettings();
}

void Sound::openSound() {
	mciSendString(L"open \"Sound/dumb_ways2die.mp3\" type mpegvideo alias theme", NULL, 0, NULL);
}

void Sound::playBg() {
	mciSendString(L"play theme from 0 repeat", NULL, 0, NULL);
}

void Sound::stopBg() {
	mciSendString(L"stop theme", NULL, 0, NULL);
}

void Sound::setVolume(const int& v) {
	volume = v;
	wstring cmd = L"setaudio theme volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
	//cmd = L"setaudio theme volume to " + to_wstring(volume);
	//mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void Sound::loadSettings() {
	ifstream in("settings.txt");

	in >> bg_theme;
	in >> sound_eff;
	in >> animal_eff;
	in >> vehicle_eff;
	in >> volume;

	in.close();
}

void Sound::saveSettings() {
	ofstream out("settings.txt");

	out << bg_theme << endl;
	out << sound_eff << endl;
	out << animal_eff << endl;
	out << vehicle_eff << endl;
	out << volume;

	out.close();
}

void Sound::runHandle() {
	bool BgOff = false;
	openSound();
	setVolume(volume);
	playBg();
	while (sound_running) {
		if (bg_theme == true && BgOff == true) {
			playBg();
			BgOff = false;
		}
		else if (bg_theme == false && BgOff == false) {
			stopBg();
			BgOff = true;
		}
	}
	stopBg();
}