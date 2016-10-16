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
#include "GOLSwarm.h"
#include "GOLGrid.h"
#include<time.h>
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int SCREEN_WIDTH = 0;
	int SCREEN_HEIGHT = 0;
	while (SCREEN_WIDTH < 100) { //initialising screen width
		cout << "Enter screen width (min 100 px): ";
		cin >> SCREEN_WIDTH;
	}
	while (SCREEN_HEIGHT < 100) { // initialising scren height
		cout << "Enter screen height (min 100 px): ";
		cin >> SCREEN_HEIGHT;
	}

	GOLScreen screen;
	if (!screen.init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
		cout << "screen initialisation failed" << endl;
	}
	int pAlive = 200;
	while (pAlive < 0 || pAlive > 100) {// initialising alive cells
		cout << "Enter the percentage of cells initially alive: " << endl;
		cin >> pAlive;
	}

	GOLSwarm swarm(pAlive, SCREEN_WIDTH, SCREEN_HEIGHT); // initialise swarm;

	//Game Loop

	while (true) {

		for (int y = 0; y < SCREEN_HEIGHT; y++) { // for every cell, check if alive and colour appropriately
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				Uint32 colour;
				if (swarm.checkLive(x, y)) {
					colour = 0xffffffff;

				} else {
					colour = 0x0000000000;

				}

				screen.setPixel(x, y, colour);// set pixel colour


			}
		}
		screen.update();//updates screen (duh)

		swarm.nextGen();// calculates who is alive next generation

		if (!screen.processEvents()) {
			break;
		}
	}
	screen.close();

	return 0;
}
