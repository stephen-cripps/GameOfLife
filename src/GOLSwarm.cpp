/*
 * GOLSwarm.cpp
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#include "GOLSwarm.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>
using namespace std;


GOLSwarm::GOLSwarm(int p, int W, int H) :
	GRID_WIDTH(0), GRID_HEIGHT(0), prevElapsed(0) {
	GRID_WIDTH = W;
	GRID_HEIGHT = H;
	grid.resize(H, vector<bool> (W, 0)); //new game grid size of window

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) { //sets number of alive cells based on probability

			double rNum = ((double) rand() / (RAND_MAX)) * 100;

			if (rNum < p) {
				grid[y][x] = 1;

			}
		}
	}

}

bool GOLSwarm::checkLive(int x, int y) {

	return grid[y][x];
}

bool GOLSwarm::makeLive(int x, int y){
	grid [y][x] = !grid[y][x];

	return grid[y][x];
}

void GOLSwarm::nextGen() {
	temp = grid;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) { // for every cell{
			int count = 0; //count of live neighbours

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {//for every cell in grid of 9 surrounding

					if (row != 0 || col != 0) { //not including current cell
						int currentX = x + col;
						int currentY = y + row;

						if (currentY >= 0 && currentY < GRID_HEIGHT
								&& currentX >= 0 && currentX < GRID_WIDTH) { //off screen = dead (for now)

							if (grid[currentY][currentX]) {
								count++;

							}
						}
					}
				}
			}
			//sets alive or dead based on no. alive neighbours
			if (count == 3)
				temp[y][x] = 1;
			else if (count < 2 || count > 3)
				temp[y][x] = 0;

		}

	}

	grid = temp;
}

GOLSwarm::~GOLSwarm() {
}
