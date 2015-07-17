/*
 * PathPlanner.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "../Map.h"
#include "../Utils.h"
#include "PathFinder.h"
#include "../ConfigurationManager.h"
#include "WaypointsManager.h"

class PathPlanner {
private:
	Map* _map;
	vector<Position*> _astarPath;
	vector<Position*> _waypoints;
public:
	PathPlanner(ConfigurationManager* configurationManager);
	virtual ~PathPlanner();

	vector<Position*> getWaypoints() const{ return _waypoints; };
	Map* getMap() const{ return _map; };
	void printAstarToPng();
};

#endif /* PATHPLANNER_H_ */
