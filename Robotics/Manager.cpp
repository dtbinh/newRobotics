/*
 * Manager.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager(Robot* robot, PathPlanner* pathPlanner,
		AvoidObstaclesPlan* avoidObstaclesPlan) {
	_robot = robot;
	_pathPlanner = pathPlanner;
	_avoidObstaclesPlan = avoidObstaclesPlan;
	_curr = _avoidObstaclesPlan->startBehavior();
}

void Manager::run() {
	for (int i = 0; i < 15; i++) {
		_robot->Read();
	}

	_robot->Read();
	if (!_curr->startCond()){
		_curr->selectNextBehavior();
	}

	double prevX = 0, prevY = 0, prevYaw = 0;
	double newX, newY, newYaw;

	while (_curr != NULL) {
		while (!_curr->stopCond()) {
			_curr->action();
			_robot->Read();

			// Get the robot's new location
			newX = _robot->getXPos();
			newY = _robot->getYPos();
			newYaw = _robot->getYaw();

			// Use some noise to simulate real world wrong reads.
			// TODO: get rid of it in production----------------------------------------------------------
			//newX = newX + ((double) rand() / (RAND_MAX)) * 2 * NOISE_POSITION_FACTOR - NOISE_POSITION_FACTOR;
			//newY = newY + ((double) rand() / (RAND_MAX)) * 2 * NOISE_POSITION_FACTOR - NOISE_POSITION_FACTOR;
			//newYaw = newYaw + ((double) rand() / (RAND_MAX)) * 2 * NOISE_YAW_FACTOR - NOISE_YAW_FACTOR;

			// Update particles
			_localizationManager.updateParticles(_robot, newX - prevX,
					newY - prevY, newYaw - prevYaw);

			//cout << "Robot's position: " << newX << ", " << newY << ", "
				//	<< newYaw << endl;

			//Particle* best = _localizationManager.getBestParticle();
			//cout << "Robot's position by particles: " << best->loc->x << ", "
					//<< best->loc->y << ", " << best->loc->yaw << endl;

			prevX = newX;
			prevY = newY;
			prevYaw = newYaw;
		}

		_curr = _curr->selectNextBehavior();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
