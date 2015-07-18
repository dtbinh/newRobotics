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

	if (currWayPoint == NULL){
		return false;
	}

	std::cout<<"startconD"<<std::endl;

	/*if (_waypointMgr->isClearPath(currWayPoint->getX(), currWayPoint->getY(),
							  _robot->getXPos(), _robot->getYPos())){*/

		std:cout<<"clear!"<<std::endl;

		if (currWayPoint->getX() - _robot->getXPos() == 0){
			_nextWaypointYaw = _robot->getYPos() - currWayPoint->getY() ? 180 : 0;
		}
		else{
			double tan = atan((currWayPoint->getY() - _robot->getYPos()) / (currWayPoint->getX() - _robot->getXPos()));
			_nextWaypointYaw = 180 -
				Utils::convertRadianToDegree(tan);
		}

		_isRightTurn = _robot->getYaw() - _nextWaypointYaw > 0 ? -1 : 1;

		std::cout<<"robotYaw: "<< _robot->getYaw() <<"nextYaw: "<< _nextWaypointYaw<<std::endl;

		return true;
	//}

	return false;
}

void TurnToWaypoint::action()
{
	_robot->setSpeed(0.0,_isRightTurn * 0.3);
}

double TurnToWaypoint::availableSpace()
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
