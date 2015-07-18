/*
 * AvoidObstaclesPlan.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "AvoidObstaclesPlan.h"

AvoidObstaclesPlan::AvoidObstaclesPlan(Robot* robot, WaypointsManager* waypointsMgr)
{
	_robot = robot;
	_behaviorsArr = new Behavior*[3];

	// Create the behaviors
	_behaviorsArr[0] = new GoForward(_robot, waypointsMgr);
	_behaviorsArr[1] = new TurnRight(_robot, waypointsMgr);
	_behaviorsArr[2] = new TurnLeft(_robot, waypointsMgr);

	// Set the possible next behaviors for each behavior
	_behaviorsArr[0]->addNextBehavior(_behaviorsArr[1]);
	_behaviorsArr[0]->addNextBehavior(_behaviorsArr[2]);
	_behaviorsArr[1]->addNextBehavior(_behaviorsArr[0]);
	_behaviorsArr[2]->addNextBehavior(_behaviorsArr[0]);
	_startBehavior = _behaviorsArr[0];
}

Behavior* AvoidObstaclesPlan::startBehavior()
{
	return _startBehavior;
}

AvoidObstaclesPlan::~AvoidObstaclesPlan() {
}
