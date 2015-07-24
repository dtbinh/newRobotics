/*
 * Location.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
public:
	int x;
	int y;
	int yaw;

	Location(int x, int y, int yaw);
	Location(Location& location);
	virtual ~Location();
};

#endif /* LOCATION_H_ */
