/*
 * TurnToWaypoint.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef TURNTOWAYPOINT_H_
#define TURNTOWAYPOINT_H_

#include "BehaviorBase.h"

class TurnToWaypoint: public Behavior {
public:
	WaypointsManager* _waypointMgr;
	TurnToWaypoint(Robot* robot, WaypointsManager* wpManager) : Behavior(robot), _waypointMgr(wpManager) {}
	virtual ~TurnToWaypoint();
	void action();
	bool startCond();
	bool stopCond();
	double availableSpace();
};

#endif /* TURNTOWAYPOINT_H_ */
