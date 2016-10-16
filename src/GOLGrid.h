/*
 * GOLGrid.h
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#ifndef GOLGRID_H_
#define GOLGRID_H_

class GOLGrid {
private:
	bool status;
public:
	GOLGrid();
	virtual ~GOLGrid();
	void alive(bool x);
	bool checkStatus();
	void setStatus(int count);

};

#endif /* GOLGRID_H_ */
