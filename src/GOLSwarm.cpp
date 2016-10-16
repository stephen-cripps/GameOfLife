/*
 * GOLSwarm.cpp
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#include "GOLSwarm.h"
#include <stdlib.h>
#include <iostream>
using namespace std; //for cout debug

GOLSwarm::GOLSwarm(int p, int W, int H) {
	SCREEN_WIDTH = W;
	SCREEN_HEIGHT = H;
	m_pGrid = new GOLGrid[W * H]; //new game grid size of window
	int count = 0;
	for (int i = 0; i < W * H; i++) { //sets number of alive cells based on probability

		double rNum = ((double) rand() / (RAND_MAX)) * 100;

		if (rNum < p) {
			m_pGrid[i].setStatus(3);
			count ++;

		}
	}

}

bool GOLSwarm::checkLive(int x, int y) {
	int i = y * SCREEN_WIDTH + x; //converts cell coords to position in array

	bool status = m_pGrid[i].checkStatus();

	return status;
}

void GOLSwarm::nextGen() {
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) { // for every cell{
			int count = 0; //count of live neighbours

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {//for every cell in grid of 9 surrounding

					if (row != 0 || col != 0) { //not including current cell
						int currentX = x + col;
						int currentY = y + row;

						if (currentY >= 0 && currentY < SCREEN_HEIGHT
								&& currentX >= 0 && currentX < SCREEN_WIDTH) { //off screen = dead (for now)
							int i = currentY * SCREEN_WIDTH + currentX; //converts cell coords to position in array

							if (m_pGrid[i].checkStatus()) {
								count++;
							}
						}
					}
				}
			}
			int j = y * SCREEN_WIDTH + x;
			m_pGrid[j].setStatus(count); //sets alive or dead based on no. alive neighbours
		}

	}
}

GOLSwarm::~GOLSwarm() {
	delete[] m_pGrid;
}
