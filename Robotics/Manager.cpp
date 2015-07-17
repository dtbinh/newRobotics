/*
 * Manager.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager(Robot* robot, PathPlanner* pathPlanner) {
	_robot = robot;
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
