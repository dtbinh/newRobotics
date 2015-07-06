/*
 * Location.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
	int _x;
	int _y;
	int _yaw;

public:
	Location(int x, int y, int yaw);
	Location(float x, float y);
	virtual ~Location();
};

#endif /* LOCATION_H_ */
