/*
 * ObstacleAvoidPlan.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "ObstacleAvoidPlan.h"

ObstacleAvoidPlan::ObstacleAvoidPlan() {
	const char* path = "/home/colman/Desktop/newRobotics/Robotics/parameters.txt";
	_configurationManager = new ConfigurationManager(path);

	char* mapFilePath = _configurationManager->mapPath;

	_map = new Map(mapFilePath);

	Matrix<Utils::CELL_STATUS>* originalMap = _map->getOriginalMap();
	Matrix<Utils::CELL_STATUS>* blownMap = _map->getBlownMap();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(blownMap);
	_astarPath = pathFinder->aStar(_configurationManager->yStartLocation, _configurationManager->xStartLocation,
								   _configurationManager->yTarget, _configurationManager->xTarget);

	// Get way points
	WaypointsManager* waypointMgr = new WaypointsManager(_astarPath);
	_waypoints = waypointMgr->getWayPoints();

	// Bonus
}

ObstacleAvoidPlan::~ObstacleAvoidPlan() {
	// TODO Auto-generated destructor stub
	delete _map;
	delete _configurationManager;
}

void ObstacleAvoidPlan::printAstarToPng(){
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = _map->getOriginalMap();

	for(unsigned int i=0; i < _astarPath.size(); i++){
		mapToPrintAstarOn->set(_astarPath[i]->y, _astarPath[i]->x, Utils::OCCUPIED);
	}

	_map->saveMapToPng(mapToPrintAstarOn, "/home/colman/Desktop/waypointss.png");
}
