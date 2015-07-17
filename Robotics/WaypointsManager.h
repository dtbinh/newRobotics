/*
 * WaypointsManager.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>
#include <iostream>
#include "Point.h"

class WaypointsManager {
private:
	std::vector <Point*> _waypointVector;

public:
	WaypointsManager();
	WaypointsManager(std::vector <Point*> path);
	std::vector <Point*> getWayPoints();
	virtual ~WaypointsManager();
};

#endif /* WAYPOINTSMANAGER_H_ */

