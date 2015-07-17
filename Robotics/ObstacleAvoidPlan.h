/*
 * ObstacleAvoidPlan.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef OBSTACLEAVOIDPLAN_H_
#define OBSTACLEAVOIDPLAN_H_

#include "Map.h"
#include "Utils.h"
#include "PathFinder.h"
#include "ConfigurationManager.h"
#include "WaypointsManager.h"

class ObstacleAvoidPlan {
private:
	Map* _map;
	vector<Position*> _astarPath;
	ConfigurationManager* _configurationManager;
	vector<Position*> _waypoints;
public:
	ObstacleAvoidPlan();
	virtual ~ObstacleAvoidPlan();

	vector<Position*> getWaypoints() const{ return _waypoints; };
	Map* getMap() const{ return _map; };
	ConfigurationManager* getCM() const{ return _configurationManager; };
	void printAstarToPng();
};

#endif /* OBSTACLEAVOIDPLAN_H_ */
