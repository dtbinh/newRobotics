/*
 * Manager.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Robot.h"
#include "Behaviors/Behaviors.h"
#include "Plan.h"

class Manager {
	Behaviors* _curr;
	Robot* _robot;
public:
	Manager(Robot* robot, Plan* pln);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
