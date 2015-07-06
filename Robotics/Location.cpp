/*
 * Location.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#include "Location.h"

Location::Location(int x, int y, int yaw){
	_x = x;
	_y = y;
	_yaw = yaw;
}

Location::Location(float x, float y){
	_x = x;
	_y = y;
}

Location::~Location() {
	// TODO Auto-generated destructor stub
}

