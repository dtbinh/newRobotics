/*
 * ObstacleAvoidPlan.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "ObstacleAvoidPlan.h"

ObstacleAvoidPlan::ObstacleAvoidPlan() {
	const char* CONFIGURATION_PATH = "parameters.txt";
	_configurationManager = new ConfigurationManager(CONFIGURATION_PATH);

	_map = new Map(_configurationManager->mapPath);

	// Path Finding
	PathFinder* pathFinder = new PathFinder(_map->getBlownMap());
	_astarPath = pathFinder->aStar(_configurationManager->yStartLocation, _configurationManager->xStartLocation,
								   _configurationManager->yTarget, _configurationManager->xTarget);

	// Get way points
	WaypointsManager* waypointMgr = new WaypointsManager(_astarPath);
	_waypoints = waypointMgr->getWayPoints();
}

void ObstacleAvoidPlan::printAstarToPng(){
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = _map->getOriginalMap();

	for(unsigned int i=0; i < _astarPath.size(); i++){
		mapToPrintAstarOn->set(_astarPath[i]->y, _astarPath[i]->x, Utils::OCCUPIED);
	}

	char* imgPath = "/home/colman/Desktop/astar.png";
	_map->saveMapToPng(mapToPrintAstarOn, imgPath);
}

ObstacleAvoidPlan::~ObstacleAvoidPlan() {
	delete _map;
	delete _configurationManager;
}
