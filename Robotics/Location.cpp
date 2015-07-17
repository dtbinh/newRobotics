/*
 * Location.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#include "Location.h"

Location::Location(int x, int y, int yaw){
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

Location::Location(Location& location){
	this->x = location.x;
	this->y = location.y;
	this->yaw = location.yaw;
}

Location::~Location() {
	// TODO Auto-generated destructor stub
}

