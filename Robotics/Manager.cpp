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

	double prevX = Utils::configurationManager->xStartLocation,
		   prevY = Utils::configurationManager->yStartLocation,
		   prevYaw = Utils::configurationManager->yawStartLocation;
	double newX, newY, newYaw;

	while (_curr != NULL) {
		while (!_curr->stopCond()) {
			_curr->action();
			_robot->Read();

			// Get the robot's new location
			newX = _robot->getXPos();
			newY = _robot->getYPos();
			newYaw = _robot->getYaw();

			double deltaX = newX - prevX;
			double deltaY = newY - prevY;
			double deltaYaw = newYaw - prevYaw;
			if (deltaX == 0 &&  deltaY == 0 && deltaYaw == 0)
				continue;

			// Update particles
			_localizationManager.updateParticles(_robot, deltaX, deltaY, deltaYaw);
			Particle* best = _localizationManager.getBestParticle();

			//cout << "Robot's position: " << newX << ", " << newY << ", "
			//		<< newYaw << endl;


			//cout << "Robot's position by particles: " << best->loc->x << ", "
			//		<< best->loc->y << ", " << best->loc->yaw << ", " << best->belief << endl;

			prevX = newX;
			prevY = newY;
			prevYaw = newYaw;
		}

		_robot->setSpeed(0.0,0.0);
		_curr = _curr->selectNextBehavior();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
