#pragma once

#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>

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

#define LEFT_GAMEBOARD 18
#define TOP_GAMEBOARD 5

#define WIDTH_GAMEBOARD 100
#define HEIGHT_GAMEBOARD 26


enum Key {
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A
};


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
	static bool pressedKey(Key);
	static int getConsoleInput();
	//static void playSound(int);
};