/*
 * PathPlanner.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(ConfigurationManager* configurationManager) {
	_map = new Map(configurationManager->mapPath);

	// Path Finding
	PathFinder* pathFinder = new PathFinder(_map->getBlownMap());
	_astarPath = pathFinder->aStar(configurationManager->yStartLocation, configurationManager->xStartLocation,
								   configurationManager->yTarget, configurationManager->xTarget);

	// Get way points
	WaypointsManager* waypointMgr = new WaypointsManager(_astarPath);
	_waypoints = waypointMgr->getWayPoints();
}

void PathPlanner::printAstarToPng(){
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = _map->getOriginalMap();

	for(unsigned int i=0; i < _astarPath.size(); i++){
		mapToPrintAstarOn->set(_astarPath[i]->getY(), _astarPath[i]->getX(), Utils::OCCUPIED);
	}

	char* imgPath = "/home/colman/Desktop/astar.png";
	_map->saveMapToPng(mapToPrintAstarOn, imgPath);
}

PathPlanner::~PathPlanner() {
	delete _map;
}
