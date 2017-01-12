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
#include<time.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <limits>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	cout << "Welcome To The Game of Life" << endl;
	int GRID_HEIGHT;
	int CELL_SIZE;
	int GRID_WIDTH;
	//screen resolution
	DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);

	//initialising width
	Width_set: cout << "Enter grid width: ";
	cin >> GRID_WIDTH;
	fflush(stdin);
	if (cin.fail()) {
		cout << "\n \n **Invalid input; please re-enter** \n" << endl;
		std::cin.clear();
		goto Width_set;
	}

	// initialising screen height
	Height_set: cout << "Enter grid height: ";
	cin >> GRID_HEIGHT;
	fflush(stdin);
	if (cin.fail()) {
		cout << "\n \n **Invalid input; please re-enter** \n" << endl;
		std::cin.clear();
		goto Height_set;
	}

	Cell_set: cout << "Enter Cell size in Pixels: ";
	cin >> CELL_SIZE;
	fflush(stdin);
	if (cin.fail()) {
		cout << "\n \n **Invalid input; please re-enter** \n" << endl;
		std::cin.clear();
		goto Cell_set;
	}

	if (GRID_HEIGHT * CELL_SIZE < 100 || GRID_WIDTH * CELL_SIZE < 100) {
		cout << "Please ensure window is larger than 100x100 pixels" << endl;
		goto Width_set;
	} else if (GRID_HEIGHT * CELL_SIZE > dwHeight || GRID_WIDTH * CELL_SIZE
			> dwWidth) {
		cout << "Please ensure window is smaller than your screen resolution ("
				<< dwWidth << "x" << dwHeight << ")" << endl;
		goto Width_set;
	}


	int pAlive = 200;
	while (pAlive < 0 || pAlive > 100) {// initialising alive cells
		cout << "Enter the percentage of cells initially alive: " << endl;
		cin >> pAlive;
	}
	cout << "Enter the time in milliseconds between Generations: " << endl;
	double speed;
	cin >> speed;

	cout << "Press space to pause, click to create/kill cells" << endl;

	GOLScreen screen;
	if (!screen.init(GRID_WIDTH, GRID_HEIGHT, CELL_SIZE)) {
		cout << "screen initialisation failed" << endl;
		return 0;
	}

	GOLSwarm swarm(pAlive, GRID_WIDTH, GRID_HEIGHT); // initialise swarm;

	//Game Loop

	bool pause = 0; //initially not paused
	double prevElapsed = 0; //setting interval time
	double elapsed = 0;
	while (true) {

		if (!pause) {
			swarm.nextGen();// calculates who is alive next generation
			for (int y = 0; y < GRID_HEIGHT; y++) { // for every cell, check if alive and colour appropriately
				for (int x = 0; x < GRID_WIDTH; x++) {

					switch (swarm.checkLive(x, y)) {
					case false:
						screen.setPixel(x, y, 0x00000000);
						break;
					case true:
						screen.setPixel(x, y, 0xffffffff);
					}
				}
			}
			screen.update();//updates screen (duh)


		}

		do {// While the time between game loops is less than the set interval
			elapsed = SDL_GetTicks(); //time since game has been running
			switch (screen.processEvents()) {
			case 1:
				goto end;
				break;
			case 2:
				pause = !pause;
				break;
			case 3: {//on click & drag
				int Tx = screen.getX() / CELL_SIZE; //get mouse pos and convert to grid pos
				int Ty = screen.getY() / CELL_SIZE;

				switch (swarm.makeLive(Tx, Ty)) {//make alive or dead, return value, set pixel.
				case 0:
					screen.setPixel(Tx, Ty, 0x00000000);
					break;
				case 1:
					screen.setPixel(Tx, Ty, 0xffffffff);
					break;
				}

				screen.update();
			}

			}
		} while (elapsed - prevElapsed < speed);

		prevElapsed = elapsed;
	}
	end: screen.close();

	return 0;
}
