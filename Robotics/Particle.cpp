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
	this->location = new Location(*location);

	this->belief = bel;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

double Particle::update(int deltaX, int deltaY, int deltaYaw,
		Robot* robot) {

	location->x += deltaX;
	location->y += deltaY;
	location->yaw += deltaYaw;

	double probByMovement = this->probByMove(deltaX, deltaY, deltaYaw);
	double probByMeasure = this->probByMeasure(robot);
	double newBelief = belief * 1.15 * probByMeasure * probByMovement;

	//cout << " x: " << loc->x << " y: " << loc->y << "before: " << belief << " after: " << newBelief <<
		//	" measure: "<< probByMeasure << " movement: " << probByMovement << endl;

	belief = newBelief;

	if (belief > 1){
		belief = 1;
	}

	return belief;
}

Particle* Particle::createParticle() {
	Location* newLocation = location;

	// Randomize the location of the new cell to be around the current cell
	newLocation->x += pow(-1, rand());
	newLocation->y += pow(-1, rand());
	newLocation->yaw += (rand() % 30 - 15);

	return new Particle(newLocation, this->belief-0.01);
}

double Particle::probByMove(int deltaX, int deltaY, int deltaYaw) {
	double prob;
	double deltaDistance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	double realDeltaYaw = 0;
	int absDeltaYaw = fabs(deltaYaw);

	// Fix the angle reading
	if (absDeltaYaw > 180) {
		realDeltaYaw = 360 - absDeltaYaw;
	} else {
		realDeltaYaw = absDeltaYaw;
	}

	// Check the probability of the robot real location
	if ((deltaDistance < 0.2) && (realDeltaYaw < 0.01)) {
		prob = Utils::PERFECT_PROB;
	} else if ((deltaDistance < 0.2) && (realDeltaYaw < 20)) {
		prob = Utils::HIGH_PROB;
	} else if ((deltaDistance > 0.2) && (realDeltaYaw > 20)) {
		prob = Utils::LOW_PROB;
	} else {
		prob = Utils::MEDIUM_PROB;
	}

	return prob;
}

double Particle::probByMeasure(Robot* robot) {
	double missesCount = 0;
	double hitsCount = 0;

	double currentYaw = Utils::convertDegreeToRadian(location->yaw);
	Matrix<Utils::CELL_STATUS>* map = Map::getInstance()->getOriginalMap();

	for (int i = 0; i <= Utils::MAX_LASER_INDEX; i += 20) {
		double laserAngle = convertLaserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserScan(i);
		double measuredDistance = Utils::convertMeterToPixel(disFromObstacle);

		bool isObstacleHit = false;

		// check the distance
		if (disFromObstacle < 4.0 && disFromObstacle > 0.2) {
			double cosinus = cos(currentYaw + laserAngle);
			double sinus = sin(currentYaw + laserAngle);

			// check if the obstacle is in the right place
			for (int j=0; j<measuredDistance; j++){

				int xToCheck= location->x +  (j * cosinus);
				int yToCheck = location->y - (j * sinus);

				if (xToCheck > map->getRows() || yToCheck > map->getColumns()) {
					isObstacleHit = true;
					break;
				}

				if (map->get(yToCheck, xToCheck) == Utils::OCCUPIED) {
					double realDistanceFromObstacle = sqrt(pow(yToCheck - location->y,2) + pow(xToCheck - location->x,2));
					double disAbs = fabs(
							realDistanceFromObstacle - measuredDistance);

					if (disAbs < 1)
					{
						isObstacleHit = true;
					}
					break;
				}
			}

			if (!isObstacleHit) {
				missesCount++;
			}
			else {
				hitsCount++;
			}
		}
	}

	if (hitsCount + missesCount == 0){
		return 1;
	}

	return (hitsCount / (hitsCount + missesCount));
}

double Particle::convertLaserIndexToLaserAngle(int index)
{
	return ((index * Utils::ANGULAR_RESULUTION - 120.0) / 180.0) * M_PI;
}
