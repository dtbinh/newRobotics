#include "TurnLeft.h"

bool TurnLeft::startCond()
{
	if (_waypointMgr->getCurrWayPoint() == NULL){
		return false;
	}

	// Turn left only if none of the left side laser indexes found obstacle
	for(int i=CENTER_LASER_INDEX; i<Utils::MAX_LASER_INDEX; i++)
	{
		if(_robot->getLaserScan(i) < MIN_SIDE_DISTANCE)
			return false;
	}
	return true;
}

void TurnLeft::action()
{
	_robot->setSpeed(0.0, ROTATION_SPEED);
}

double TurnLeft::getPriority()
{
	double totalDistance = 0;
	for(int i=CENTER_LASER_INDEX; i<Utils::MAX_LASER_INDEX; i++)
	{
		totalDistance += _robot->getLaserScan(i);
	}

	return totalDistance;
}

bool TurnLeft::stopCond()
{
	// Stop turning if there's no obstacle in front
	for(int i=RIGHT_LIMIT_LASER_INDEX; i<LEFT_LIMIT_LASER_INDEX; i++)
	{
		if (_robot->getLaserScan(i) <= MIN_FRONT_DISTANCE)
			return false;
	}

	return true;
}

TurnLeft::~TurnLeft()
{
}
