/*
 * PathPlanner.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner() {
	_map = Map::getInstance();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(_map->getBlownMap());
	_astarPath = pathFinder->aStar(Utils::configurationManager->yStartLocation, Utils::configurationManager->xStartLocation,
			Utils::configurationManager->yTarget, Utils::configurationManager->xTarget);

	// Get way points
	WaypointsManager* waypointMgr = new WaypointsManager(_astarPath);
	_waypointsMgr = waypointMgr;
}

void PathPlanner::printAstarToPng(){
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = _map->getOriginalMap();

	for(unsigned int i=0; i < _astarPath.size(); i++){
		mapToPrintAstarOn->set(_astarPath[i]->getY(), _astarPath[i]->getX(), Utils::OCCUPIED);
	}

//	for(unsigned int i=0; i < _waypointsMgr->getWayPoints().size(); i++){
//		mapToPrintAstarOn->set(_waypointsMgr->getWayPoints()[i]->getY(), _waypointsMgr->getWayPoints()[i]->getX(), Utils::OCCUPIED);
//	}

	char* imgPath = "/home/colman/Desktop/astar.png";
	_map->saveMapToPng(mapToPrintAstarOn, imgPath);
}

PathPlanner::~PathPlanner() {
	delete _map;
}
