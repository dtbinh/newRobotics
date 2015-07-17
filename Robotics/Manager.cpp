/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, PathPlanner* pathPlanner) : _robot(robot), _pathPlanner(pathPlanner) {
	//_curr = pln->getStartPoint();
}
void Manager::run()
{
	_robot->Read();
	if(!(_curr->startCond()))
		return;
	_curr->action();
	while(_curr !=NULL)
	{
		while(_curr->stopCond() == false)
		{
			_curr->action();
			_robot->Read();
		}
		_curr = _curr->selectNextBehavior();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
