//============================================================================
// Name        : GameOfLife.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include "GOLScreen.h"
using namespace std;

int main(int argc, char* argv[]) {

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	cout << "Enter screen width: ";
	cin >> SCREEN_WIDTH;
	cout << "Enter screen height: ";
	cin >> SCREEN_HEIGHT;

	GOLScreen screen;
	if (!screen.init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
			cout << "screen initialisation failed" << endl;
		}


	//Game Loop
		while (true) {

			for(int y=1; y<SCREEN_HEIGHT; y++){
				for(int x=1; x<SCREEN_WIDTH; x++){
			// for every cell
			// Check if live or dead
					Uint32 colour = 0x0000000000;
			screen.setPixel(x,y,colour);// set pixel colour, need to pass in screen width as it is initialised by user
			}}
			screen.update();

	if (!screen.processEvents()) {
				break;
			}
		}
	screen.close();

	return 0;
}
