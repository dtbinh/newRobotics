/*
 * TurnToWaypoint.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef TURNTOWAYPOINT_H_
#define TURNTOWAYPOINT_H_

#include "BehaviorBase.h"
#include <cmath>

class TurnToWaypoint: public Behavior {
	double _nextWaypointYaw;
	int _isLeftTurn;
public:
	WaypointsManager* _waypointMgr;
	TurnToWaypoint(Robot* robot, WaypointsManager* wpManager) :
			Behavior(robot), _waypointMgr(wpManager), _nextWaypointYaw(0) {}
	virtual ~TurnToWaypoint();
	void action();
	bool startCond();
	double getPriority();
	bool stopCond();
};

#endif /* TURNTOWAYPOINT_H_ */
