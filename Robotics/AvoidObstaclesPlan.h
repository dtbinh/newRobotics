#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "Plan.h"
#include "Behaviors.h"
#include "GoForward.h"
#include "TurnLeft.h"
#include "TurnRight.h"

class AvoidObstaclesPlan: public Plan
{
public:
	AvoidObstaclesPlan(Robot* robot);
	Behaviors* startBehavior();
	virtual ~AvoidObstaclesPlan();
};

#endif /* AVOIDOBSRACLESPLAN_H_ */
