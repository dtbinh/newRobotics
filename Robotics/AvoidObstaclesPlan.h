/*
 * AvoidObstaclesPlan.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef AVOIDOBSRACLESPLAN_H_
#define AVOIDOBSRACLESPLAN_H_

#include "Behaviors/BehaviorBase.h"
#include "Behaviors/GoForward.h"
#include "Behaviors/TurnLeft.h"
#include "Behaviors/TurnRight.h"
#include "Behaviors/TurnToWaypoint.h"
#include "PathPlanning/WaypointsManager.h"

class AvoidObstaclesPlan {
	Robot* _robot;
	Behavior** _behaviorsArr;
	Behavior* _startBehavior;
public:
	AvoidObstaclesPlan(Robot* robot, WaypointsManager* waypointsMgr);
	Behavior* startBehavior();
	virtual ~AvoidObstaclesPlan();
};

#endif /* AVOIDOBSRACLESPLAN_H_ */
