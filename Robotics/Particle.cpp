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

	loc->x += deltaX;
	loc->y += deltaY;
	loc->yaw += deltaYaw;

	double probByMovement = this->probByMove(deltaX, deltaY, deltaYaw);
	double probByMeasure = this->probByMeasure(robot);
	double newBelief = belief * 1.25 * probByMeasure * probByMovement;

	cout << " x: " << loc->x << " y: " << loc->y << "before: " << belief << " after: " << newBelief <<
			" measure: "<< probByMeasure << " movement: " << probByMovement << endl;

	belief = newBelief;

	if (belief > 1){
		belief = 1;
	}

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
	cout << "deltaX: " << deltaX << " deltaY: " << deltaY << " deltaYaw: " << deltaYaw << endl;
	double prob = 0.25;
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


//	if (deltaDistance < 0.1)
//		prob = 1;
//	else if (deltaDistance < 0.3)
//		prob = 0.8;
//	else if (deltaDistance < 0.5)
//			prob = 0.6;
//	else if (deltaDistance < 0.7)
//			prob = 0.4;
//	else if (deltaDistance >= 0.7)
//			prob = 0.2;

	return prob;
}

double Particle::probByMeasure(Robot* robot) {
	double numOfWrongMapCells = 0;
	double numOfRightMapCells = 0;
	double currentYaw = Utils::convertDegreeToRadian(loc->yaw);
	Matrix<Utils::CELL_STATUS>* map = Map::getInstance()->getOriginalMap();

	for (int i = 0; i <= Utils::MAX_LASER_INDEX; i += 10) {
		double laserAngle = laserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserScan(i);
		double measuredDistance = Utils::convertMeterToPixel(disFromObstacle);

		// if the distance is too large, assume that there is no obstacle in this index
		// and if the distance is too short don't consider it as an obstacle because its the robot itself
		bool isObstacleHit = false;

		if (disFromObstacle < 4.0 && disFromObstacle > 0.2) {
			double cosinus = cos(currentYaw + laserAngle);
			double sinus = sin(currentYaw + laserAngle);

			for (int j=0; j<measuredDistance; j++){

				int xToCheck= loc->x +  (j * cosinus);
				int yToCheck = loc->y - (j * sinus);

				if (xToCheck > map->getRows() || yToCheck > map->getColumns()) {
					isObstacleHit = true;
					break;
				}

				if (map->get(yToCheck, xToCheck) == Utils::OCCUPIED) {
					double realDistanceFromObstacle = sqrt(pow(yToCheck - loc->y,2) + pow(xToCheck - loc->x,2));

					if (fabs(realDistanceFromObstacle - measuredDistance) < 0.01)
					{
						isObstacleHit = true;
					}
					break;
				}
			}

			if (isObstacleHit) {
				numOfWrongMapCells++;
			}
			else {
				numOfRightMapCells++;
			}

		}
	}

	if (numOfRightMapCells + numOfWrongMapCells == 0){
		cout<< "000000000000000000"<<endl;
		return 1;
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
