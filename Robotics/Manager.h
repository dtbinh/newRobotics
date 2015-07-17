/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Robot.h"
#include "Behaviors/Behavior.h"
#include "PathPlanning/PathPlanner.h"

class Manager {
	Behavior* _curr;
	Robot* _robot;
public:
	Manager(Robot* robot, PathPlanner* pathPlanner);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
