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
#include "../Position.h"
#include "../Utils.h"

class WaypointsManager {
private:
	std::vector <Position*> _waypointVector;
	int _wpIndex = 0;
public:
	Position* currWP;

	WaypointsManager();
	WaypointsManager(std::vector <Position*> path);
	std::vector <Position*>  getWayPoints() const {return _waypointVector; };
	Position* getCurrWayPoint();
	Position* getNextWayPoint();
	bool isInWayPoint(double x,double y);
	virtual ~WaypointsManager();
};

#endif /* WAYPOINTSMANAGER_H_ */

