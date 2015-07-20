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
#include <algorithm>
#include "Point.h"
#include "../Position.h"
#include "../Utils.h"
#include "../Map.h"

class WaypointsManager {
private:
	std::vector <Position*> _waypointVector;
	int _wpIndex = 0;
	void fillWayPointsVectorByPath(std::vector <Position*> path);
	void optimizePath();
public:
	Position* currWP;

	WaypointsManager();
	WaypointsManager(std::vector <Position*> path);
	std::vector <Position*>  getWayPoints() const {return _waypointVector; };
	Position* getCurrWayPoint();
	Position* getNextWayPoint();
	bool isLastWayPoint();
	bool isInWayPoint(double x,double y);
	bool isClearPath(int x1, int y1, int x2, int y2);
	virtual ~WaypointsManager();
};

#endif /* WAYPOINTSMANAGER_H_ */

