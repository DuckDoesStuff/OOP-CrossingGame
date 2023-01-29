#include "Sound.h"

Sound::Sound() {
	loadSettings();
}

Sound::~Sound() {
	saveSettings();
}

void Sound::openSound() {
	mciSendString(L"open \"Sound/dumb_ways2die.mp3\" type mpegvideo alias theme", NULL, 0, NULL);
	mciSendString(L"open \"Sound/truck_sound.mp3\" type mpegvideo alias truck", NULL, 0, NULL);
	mciSendString(L"open \"Sound/car_sound.mp3\" type mpegvideo alias car", NULL, 0, NULL);
	mciSendString(L"open \"Sound/camel_sound.mp3\" type mpegvideo alias camel", NULL, 0, NULL);
	mciSendString(L"open \"Sound/duck_sound.mp3\" type mpegvideo alias duck", NULL, 0, NULL);
}

void Sound::playBg() {//need more testing
	mciSendString(L"play theme from 0 repeat", NULL, 0, NULL);
}

void Sound::stopBg() {
	mciSendString(L"stop theme", NULL, 0, NULL);
}

void Sound::setVolume() {
	wstring cmd = L"setaudio theme volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, 0);
	cmd = L"setaudio truck volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, 0);
	cmd = L"setaudio duck volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, 0);
	cmd = L"setaudio car volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, 0);
	cmd = L"setaudio camel volume to " + to_wstring(volume);
	mciSendString(cmd.c_str(), NULL, 0, 0);
}

void Sound::loadSettings() {
	ifstream in("settings.txt");

	in >> bg_theme;
	in >> animal_eff;
	in >> vehicle_eff;
	in >> volume;

	in.close();
}

void Sound::saveSettings() {
	ofstream out("settings.txt");

	out << bg_theme << endl;
	out << animal_eff << endl;
	out << vehicle_eff << endl;
	out << volume;

	out.close();
}

void Sound::runHandle() {
	bool BgOff = false;
	openSound();
	playBg();
	while (sound_running) {

		if (changeVolume) {
			changeVolume = false;
			setVolume();
		}

		if (bg_theme == true && BgOff == true) {
			playBg();
			BgOff = false;
		}
		else if (bg_theme == false && BgOff == false) {
			stopBg();
			BgOff = true;
		}
		switch (soundSelector)
		{
		case CAR:
			if (vehicle_eff)
				mciSendString(L"play car from 0", NULL, 0, NULL);
			soundSelector = NONE;
			break;
		case TRUCK:
			if (vehicle_eff)
				mciSendString(L"play truck from 0", NULL, 0, NULL);
			soundSelector = NONE;
			break;
		case DUCK:
			if (animal_eff)
				mciSendString(L"play duck from 0", NULL, 0, NULL);
			soundSelector = NONE;
			break;
		case CAMEL:
			if (animal_eff)
				mciSendString(L"play camel from 0", NULL, 0, NULL);
			soundSelector = NONE;
			break;
		default:
			break;
		}
	}
}

void Sound::stopHandle() {
	sound_running = false;
}