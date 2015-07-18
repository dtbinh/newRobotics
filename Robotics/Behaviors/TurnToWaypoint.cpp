/*
 * TurnToWaypoint.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "TurnToWaypoint.h"

bool TurnToWaypoint::startCond()
{
	// Turn to waypoint if we have eye contect to it

	return true;
}

void TurnToWaypoint::action()
{
	_robot->setSpeed(0.0,FORWARD_SPEED);
}

double TurnToWaypoint::availableSpace()
{
	return 1000.0;
}

bool TurnToWaypoint::stopCond()
{
	// stop if we reached way point yaw
	_robot->Read();
	return (_waypointMgr->isInWayPoint(_robot->getXPos(), _robot->getYPos()));
}

TurnToWaypoint::~TurnToWaypoint()
{
}
