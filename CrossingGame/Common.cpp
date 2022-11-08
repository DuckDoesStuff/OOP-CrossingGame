#include "Common.h"

HWND Common::consoleWindow = GetConsoleWindow();
HANDLE Common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Common::setupConsole(int fontSize, int background, int text)
{
	setFontInfo(fontSize, fontSize);
	setAndCenterWindow();
	disableMaximize();
	setConsoleTitle();
	setConsoleColor(background, text);
	disableMouseInput();
	hideScrollBars();
	hideCursor();
}

void Common::gotoXY(int left, int top)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ short(left), short(top) });
}

void Common::setConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Common::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void Common::setAndCenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1152;
	int height = 648;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Common::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);

	// get handle to the console window
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// retrieve screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	// current screen buffer size
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	// to remove the scrollbar, make sure the window height matches the screen buffer height
	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	// set the new screen buffer dimensions
	int Status = SetConsoleScreenBufferSize(hOut, newSize);
}

void Common::hideCursor()
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(consoleOutput, &cursorInfo);
	cursorInfo.bVisible = 0; // set the cursor visibility
	SetConsoleCursorInfo(consoleOutput, &cursorInfo);
}

void Common::setConsoleTitle()
{
	SetConsoleTitle(L"Crossing Game");
}

void Common::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Common::setFontInfo(int sizeX, int sizeY)
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = sizeX;
	info.dwFontSize.Y = sizeY;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void Common::clearConsole()
{
	system("cls");
}

bool Common::pressedKey(int n)
{
	return GetAsyncKeyState(n);
}

int Common::getConsoleInput()
{
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (c)
		{
		case 72:				//lên
			return 2;
		case 75:				//trái
			return 3;
		case 77:				//phải
			return 4;
		case 80:				//xuống
			return 5;
		default:				//nút khác
			return 1;
		}
	}
	else
	{
		if (c == 27)                  //esc
			return 0;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 74 || c == 106) //J, j
			return 7;
		else if (c == 75 || c == 107) //K, k
			return 8;
		else if (c == 76 || c == 108) //K, k
			return 9;
		else
			return 0;                 //nút khác
	}
}
