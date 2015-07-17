/*
 * Particle.h
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include "Location.h"
#include "Robot.h"
#include "Utils.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include "Map.h"

class Particle {
public:
	Location* loc;
	double belief;

	Particle();
	Particle(Location* location, double bel);
	virtual ~Particle();

	double getBeliefAndUpdate(int deltaX, int deltaY, int deltaYaw, Robot* robot);
	Particle* getSon();
	double probByMove(int deltaX, int deltaY, int deltaYaw);
	double probByMeasure(Robot* robot);
	double getAngleByIndex(int index);
	double getRadianByIndex(int index);
	double laserIndexToLaserAngle(int index);
};

#endif /* PARTICLE_H_ */
