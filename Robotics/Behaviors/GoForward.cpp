#include "GoForward.h"

bool GoForward::startCond()
{
	// Move forward only if none of the front laser indexes found obstacle
	for(int i=RIGHT_LIMIT_LASER_INDEX; i<LEFT_LIMIT_LASER_INDEX; i++)
	{
		if(_robot->getLaserScan(i) < MIN_FRONT_DISTANCE)
			return false;
	}

	return true;
}

void GoForward::action()
{
	_robot->setSpeed(FORWARD_SPEED,0.0);
}

double GoForward::getPriority()
{
	return 1000.0;
}

bool GoForward::stopCond()
{
	// stop if there is obstacle or we reached way point
	if (!startCond()){
		return false;
	}
	_robot->Read();
	_robot->Read();
	return (_waypointMgr->isInWayPoint(_robot->getXPos(), _robot->getYPos()));
}

GoForward::~GoForward()
{
}
