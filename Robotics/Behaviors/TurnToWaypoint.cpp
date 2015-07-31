/*
 * TurnToWaypoint.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "TurnToWaypoint.h"

bool TurnToWaypoint::startCond()
{
	// Turn to waypoint if we have eye contact to it
	Position* currWayPoint = _waypointMgr->getCurrWayPoint();

	// Check if it's the last waypoint
	if (currWayPoint == NULL){
		return false;
	}

	if (currWayPoint->getX() - _robot->getXPos() == 0){
		_nextWaypointYaw = _robot->getYPos() - currWayPoint->getY() ? 180 : 0;
	}
	else{
		double arctan = atan((currWayPoint->getY() - _robot->getYPos()) / (currWayPoint->getX() - _robot->getXPos()));
		_nextWaypointYaw = 180 -
			Utils::convertRadianToDegree(arctan);
	}

	_isLeftTurn = _robot->getYaw() - _nextWaypointYaw < 0 ? 1 : -1;

	return true;
}

void TurnToWaypoint::action()
{
	_robot->setSpeed(0.0,_isLeftTurn * 0.2);
}

double TurnToWaypoint::getPriority()
{
	return 99999.0;
}

bool TurnToWaypoint::stopCond()
{
	// stop if we reached way point yaw
	return fabs(_nextWaypointYaw - _robot->getYaw()) < 2;
}

TurnToWaypoint::~TurnToWaypoint()
{
}
