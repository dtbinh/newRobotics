/*
 * LocalizationManager.h
 *
 *  Created on: Jun 25, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <vector>
#include "Particle.h"
#include "Location.h"
#include "Utils.h"
#include "ConfigurationManager.h"

class LocalizationManager {
public:
	LocalizationManager();
	virtual ~LocalizationManager();

	std::vector<Particle*> particles;
	void updateParticles(Robot* robot, double deltaX, double deltaY, double deltaYaw);
	Particle* getBestParticle();
	void createParticles();
};

#endif /* LOCALIZATIONMANAGER_H_ */
