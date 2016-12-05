/*
 * GOLSwarm.h
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#ifndef GOLSWARM_H_
#define GOLSWARM_H_
#include <vector>

class GOLSwarm {
private:
	std::vector< std::vector<bool> > grid;
	std::vector< std::vector<bool> > temp;
	int GRID_WIDTH;
	int GRID_HEIGHT;
	double prevElapsed;
public:
	GOLSwarm(int p, int W, int H);
	bool checkLive(int x, int y);
	bool makeLive(int x, int y);
	void nextGen();
	virtual ~GOLSwarm();
};

#endif /* GOLSWARM_H_ */
