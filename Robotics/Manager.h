/*
 * Manager.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Robot.h"
#include "Behaviors/BehaviorBase.h"
#include "PathPlanning/PathPlanner.h"
#include "LocalizationManager.h"
#include "AvoidObstaclesPlan.h"

// Noise to simulate real world wrong reads.
#define NOISE_POSITION_FACTOR 0.02
#define NOISE_YAW_FACTOR 0.01

class Manager {
	Behavior* _curr;
	Robot* _robot;
	PathPlanner* _pathPlanner;
	AvoidObstaclesPlan* _avoidObstaclesPlan;
	LocalizationManager _localizationManager;

public:
	Manager(Robot* robot, PathPlanner* pathPlanner, AvoidObstaclesPlan* avoidObstaclesPlan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
