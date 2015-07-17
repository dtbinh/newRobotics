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

/*double GoForward::availableSpace()
{
	double totalDistance = 0;
	for(int i=RIGHT_LIMIT_LASER_INDEX; i<LEFT_LIMIT_LASER_INDEX; i++)
	{
		totalDistance += _robot->getLaserScan(i);
	}

	return totalDistance;
}*/

bool GoForward::stopCond()
{
	return !startCond();
}

GoForward::~GoForward()
{
}
