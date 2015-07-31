/*
 * Main.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <iostream>
#include "Robot.h"
#include "PathPlanning/PathPlanner.h"
#include "Manager.h"

using namespace std;

int main(){

	Robot robot("10.10.245.65", 6665);
	PathPlanner* pathPlanner = new PathPlanner();
	AvoidObstaclesPlan* avoidObstaclesPlan = new AvoidObstaclesPlan(&robot, pathPlanner->getWaypointsMgr());
	vector<Position*> points = pathPlanner->getWaypointsMgr()->getWayPoints();
	Manager manager(&robot, pathPlanner, avoidObstaclesPlan);
	manager.run();

	//Bonus
	pathPlanner->printAstarToPng();

	cout << "finished running";

	return 0;
}

