/*
 * Particle.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#include "Particle.h"
#include "Utils.h"

Particle::Particle() {
}

Particle::Particle(Location* location, double bel) {
	this->loc = new Location(*location);

	this->belief = bel;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

double Particle::getBeliefAndUpdate(int deltaX, int deltaY, int deltaYaw,
		Robot* robot) {
	double predBel;

	loc->x += deltaX * 4;
	loc->y += deltaY * 4;
	loc->yaw += deltaYaw;

	predBel = belief * (this->probByMove(deltaX, deltaY, deltaYaw));

	cout << "before " << belief << "predbel " << predBel << endl;
	belief = Utils::PROB_NORMAL_CONST * predBel * (this->probByMeasure(robot));
	cout << "after " << belief << endl;

	return belief;
}

Particle* Particle::getSon() {
	Location *newLoc = loc;

	// Randomize the location of the new cell to be around the current cell
	newLoc->x += pow(-1, rand());
	newLoc->y += pow(-1, rand());
	newLoc->yaw += (rand() % 30 - 15);

	return new Particle(newLoc, this->belief);
}

double Particle::probByMove(int deltaX, int deltaY, int deltaYaw) {
	double prob = 0;
	double deltaDistance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double realDeltaYaw = 0;

	// Fix the angle reading
	if (fabs(deltaYaw) > 180) {
		realDeltaYaw = 360 - fabs(deltaYaw);
	} else {
		realDeltaYaw = fabs(deltaYaw);
	}

	// Check the probability of the robot real location
	if ((deltaDistance < Utils::DISTANCE_PROB_THRESHOLD)
			&& (realDeltaYaw < 0.01)) {
		prob = Utils::PERFECT_PROB;
	} else if ((deltaDistance > Utils::DISTANCE_PROB_THRESHOLD)
			&& (realDeltaYaw > Utils::YAW_PROB_THRESHOLD)) {
		prob = Utils::LOW_PROB;
	} else if ((deltaDistance < Utils::DISTANCE_PROB_THRESHOLD)
			&& (realDeltaYaw < Utils::YAW_PROB_THRESHOLD)) {
		prob = Utils::HIGH_PROB;
	} else {
		prob = Utils::MEDIUM_PROB;
	}

	return prob;
}

double Particle::probByMeasure(Robot* robot) {
	double numOfWrongMapCells = 0;
	double numOfRightMapCells = 0;
	double currentYaw = Utils::convertDegreeToRadian(loc->yaw);
	Matrix<Utils::CELL_STATUS>* map = Map::getInstance()->getOriginalMap();

	for (int i = 0; i < Utils::MAX_LASER_INDEX; i += 10) {
		double laserAngle = laserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserScan(i);

		double obstacleXPos = loc->x
				+ Utils::convertMeterToPixel(
						(disFromObstacle * cos(currentYaw + laserAngle)));
		double obstacleYPos = loc->y
				- Utils::convertMeterToPixel(
						(disFromObstacle * sin(currentYaw + laserAngle)));

		// if the distance is too large, assume that there is no obstacle in this index
		// and if the distance is too short don't consider it as an obstacle because its the robot itself
		if (disFromObstacle < 2.0 && disFromObstacle > 0.2) {
			if (obstacleYPos < 0 || obstacleXPos < 0
					|| obstacleYPos > map->getRows()
					|| obstacleXPos > map->getColumns()) {
				continue;
			}

			// Get the value in the map's cell that represents the obstacle location
			int obstacleCurrCellValue =
					map->get(obstacleYPos, obstacleXPos) == Utils::OCCUPIED ? 1 : 0;

			if (obstacleCurrCellValue == 0) {
				numOfWrongMapCells++;
			}
			else {
				numOfRightMapCells++;
			}

		}
	}
	return (numOfRightMapCells / (numOfRightMapCells + numOfWrongMapCells));
}

double Particle::getAngleByIndex(int index)
{
	return ((double) index * Utils::ANGULAR_RESULUTION - 30);
}

double Particle::getRadianByIndex(int index)
{
	return (getAngleByIndex(index) * M_PI / 180);
}

double Particle::laserIndexToLaserAngle(int index)
{
	return ((index * Utils::ANGULAR_RESULUTION - 120.0) / 180.0) * M_PI;
}
