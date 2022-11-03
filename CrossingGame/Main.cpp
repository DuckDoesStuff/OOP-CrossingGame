#include <iostream>
#include "Common.h"
#include "Menu.h"

using namespace std;

int main() {
	//std::cout << "Hello, world!" << endl;
	//Menu test;
	//test.renderMainScreen();
	
	Menu::renderMainScreen();

	//Common::clearConsole();
	system("pause");
	return 0;
}