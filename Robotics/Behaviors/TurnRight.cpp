#include "TurnRight.h"

bool TurnRight::startCond()
{
	// Turn right only if none of the right side laser indexes found obstacle
	for(int i=0; i<CENTER_LASER_INDEX; i++)
	{
		if(_robot->getLaserScan(i) < MIN_SIDE_DISTANCE)
			return false;
	}
	return true;
}

void TurnRight::action()
{
	_robot->setSpeed(0.0,-ROTATION_SPEED);
}

double TurnRight::availableSpace()
{
	double totalDistance = 0;
	for(int i=0; i<CENTER_LASER_INDEX; i++)
	{
		totalDistance += _robot->getLaserScan(i);
	}

	return totalDistance;
}

bool TurnRight::stopCond()
{
	// Stop turning if there's no obstacle in front
	for(int i=RIGHT_LIMIT_LASER_INDEX; i<LEFT_LIMIT_LASER_INDEX; i++)
	{
		if (_robot->getLaserScan(i) <= MIN_FRONT_DISTANCE)
			return false;
	}

	return true;
}

TurnRight::~TurnRight()
{
}
