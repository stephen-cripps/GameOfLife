/*
 * GOLGrid.cpp
 *
 *  Created on: 16 Oct 2016
 *      Author: user
 */

#include "GOLGrid.h"
#include <iostream>
using namespace std; //for cout debug
GOLGrid::GOLGrid() {
	// TODO Auto-generated constructor stub

}

bool GOLGrid::checkStatus(){
	return status;
}

void GOLGrid::setStatus(int count){

	switch (count) {
	  case 2: //if 2 do nothing
	    break;
	  case 3: //if 3 make alive
	    status = 1;
	    break;
	  default: // else dead
	    status = 0;
	  }
}

GOLGrid::~GOLGrid() {
	// TODO Auto-generated destructor stub
}
