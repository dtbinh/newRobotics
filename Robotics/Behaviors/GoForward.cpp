#include "GoForward.h"

GoForward::GoForward(Robot* robot) : Behaviors(robot) {
}

bool GoForward::startCond()
{
	return (_robot->isForwardFree());
}

bool GoForward::stopCond()
{
	// if forward not free or way point achieved
	return false;
}

void GoForward::action()
{
	_robot->setSpeed(0.3, turnAngle);
	turnAngle = 0.0;
}

void GoForward::stop()
{
	_robot->setSpeed(0, turnAngle);
	turnAngle = 0.0;
}

GoForward::~GoForward() {
}
