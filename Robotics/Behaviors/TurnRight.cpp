#include "TurnRight.h"

TurnRight::TurnRight(Robot* robot) : Behaviors(robot)
{
	angle = Utils::RIGHT_ANGLE;
}

TurnRight::TurnRight(Robot* robot, float turnAngle) : Behaviors(robot)
{
	angle = turnAngle;
}

void TurnRight::action()
{
	_robot->setSpeed(0.0, -1 * Utils::YAW_SPEED);
}
void TurnRight::stop()
{
	_robot->setSpeed(0, 0);
}

TurnRight::~TurnRight() {
}


bool TurnRight::stopCond()
{
	return _robot->isForwardFree();
}

bool TurnRight::startCond()
{
	return _robot->isRightFree();
}
