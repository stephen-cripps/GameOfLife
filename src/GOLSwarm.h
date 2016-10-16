/*
 * GOLSwarm.h
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#ifndef GOLSWARM_H_
#define GOLSWARM_H_
#include "GOLGrid.h"

class GOLSwarm {
private:
	GOLGrid *m_pGrid;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
public:
	GOLSwarm(int p, int W, int H);
	bool checkLive(int y, int x);
	void nextGen();
	virtual ~GOLSwarm();
};

#endif /* GOLSWARM_H_ */
