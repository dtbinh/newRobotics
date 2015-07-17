/*
 * ObstacleAvoidPlan.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "ObstacleAvoidPlan.h"

ObstacleAvoidPlan::ObstacleAvoidPlan() {
	const char* path = "/home/colman/Desktop/newRobotics/Robotics/parameters.txt";
	ConfigurationManager* configurationManager = new ConfigurationManager(path);

	char* mapFilePath = configurationManager->mapPath;

	_map = new Map(mapFilePath);

	Matrix<Utils::CELL_STATUS>* originalMap = _map->getOriginalMap();
	Matrix<Utils::CELL_STATUS>* blownMap = _map->getBlownMap();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(blownMap);
	vector<Point*> mapPath =
			pathFinder->aStar(configurationManager->yStartLocation, configurationManager->xStartLocation,
							  configurationManager->yTarget, configurationManager->xTarget);

	// Get way points
	WaypointsManager* waypointMgr = new WaypointsManager(mapPath);
	_waypoints = waypointMgr->getWayPoints();

	// Bonus
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = originalMap;

	mapToPrintAstarOn->set(configurationManager->yStartLocation, configurationManager->xStartLocation, Utils::OCCUPIED);
	for(unsigned int i=0; i < mapPath.size(); i++){
		mapToPrintAstarOn->set(mapPath[i]->y, mapPath[i]->x, Utils::OCCUPIED);
	}
	mapToPrintAstarOn->set(configurationManager->yTarget, configurationManager->xTarget, Utils::OCCUPIED);
	_map->saveMapToPng(mapToPrintAstarOn, "/home/colman/Desktop/waypointss.png");
}

ObstacleAvoidPlan::~ObstacleAvoidPlan() {
	// TODO Auto-generated destructor stub
}

