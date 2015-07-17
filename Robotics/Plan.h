/*
 * Plan.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "Behaviors/Behaviors.h"
#include "Robot.h"
class Plan {

protected:
	Behaviors* _start;
public:
	Plan(Robot* robot);
	virtual Behaviors* getStartPoint(){return _start;}
	virtual ~Plan();
};

#endif /* PLAN_H_ */
