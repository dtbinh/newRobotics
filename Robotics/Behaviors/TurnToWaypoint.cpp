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

	std::cout<<"startconD"<<std::endl;

	/*if (_waypointMgr->isClearPath(currWayPoint->getX(), currWayPoint->getY(),
							  _robot->getXPos(), _robot->getYPos())){*/

		std:cout<<"clear!"<<std::endl;

		if (currWayPoint->getX() - _robot->getXPos() == 0){
			_nextWaypointYaw = _robot->getYPos() - currWayPoint->getY() ? 180 : 0;
		}
		else{
			double tan = atanh((currWayPoint->getY() - _robot->getYPos()) / (currWayPoint->getX() - _robot->getXPos()));
			_nextWaypointYaw = 180 -
				Utils::convertRadianToDegree(tan);
		}

		_isRightTurn = _robot->getYaw() - _nextWaypointYaw > 0 ? -1 : 1;

		std::cout<<"robotYaw: "<< _robot->getYaw() <<"nextYaw: "<< _nextWaypointYaw<<std::endl;

		return !stopCond();
	//}

	return false;
}

void TurnToWaypoint::action()
{
	_robot->setSpeed(0.0,_isRightTurn * 0.3);
}

double TurnToWaypoint::availableSpace()
{
	return 1000.0;
}

bool TurnToWaypoint::stopCond()
{
	// stop if we reached way point yaw
	std::cout<<"difference: "<<_nextWaypointYaw - _robot->getYaw()<<std::endl;
	return fabs(_nextWaypointYaw - _robot->getYaw()) < 2;
}

TurnToWaypoint::~TurnToWaypoint()
{
}
