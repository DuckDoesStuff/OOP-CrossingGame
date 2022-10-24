#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <thread>
#include <queue>

using namespace std;

#pragma comment(lib, "Winmm.lib")

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define LEFT_GAMEBOARD 5
#define TOP_GAMEBOARD 4

#define GAMEBOARD_WIDTH 100

class Common {
private:
	static HWND consoleWindow;
	static HANDLE consoleOutput;
	
public:
	static void setupConsole(int fontSize, int background, int text);
	static void gotoXY(int, int);
	static void setConsoleColor(int, int);//change background and text color
	static void disableMouseInput();
	static void setAndCenterWindow();
	static void hideScrollBars();
	static void hideCursor();
	static void setConsoleTitle();
	static void disableMaximize();
	static void setFontInfo(int sizeX, int sizeY);
	static void clearConsole();
	static int getConsoleInput();
	//static void playSound(int);
};