#include "TurnLeft.h"

TurnLeft::TurnLeft(Robot* robot) : Behaviors(robot)
{
	angle = Utils::LEFT_ANGLE;
}

TurnLeft::TurnLeft(Robot* robot, float turnAngle) : Behaviors(robot)
{
	angle = turnAngle;
}

void TurnLeft::action() {
	_robot->setSpeed(0.0, Utils::YAW_SPEED);
}

void TurnLeft::stop()
{
	_robot->setSpeed(0, 0);
}

TurnLeft::~TurnLeft() {
}


bool TurnLeft::startCond() {
	return _robot->isLeftFree();
}

bool TurnLeft::stopCond() {
	return _robot->isForwardFree();
}
