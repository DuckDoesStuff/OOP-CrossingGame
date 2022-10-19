#include <iostream>
#include "Common.h"
#include "Menu.h"

using namespace std;

int main() {
	//std::cout << "Hello, world!" << endl;
	//Menu test;
	//test.renderMainScreen();
	
	std::thread th1(Menu::renderMainScreen);
	th1.join();

	//Common::clearConsole();
	system("pause");
	return 0;
}