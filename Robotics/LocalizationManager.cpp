/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager()
{
	int xStartLocation = Utils::configurationManager->xStartLocation;
	int yStartLocation = Utils::configurationManager->yStartLocation;
	int yawStartLocation = Utils::configurationManager->yawStartLocation;

	// Create the first particle
	Location* firstParticleLoc = new Location(xStartLocation,yStartLocation, yawStartLocation);

	Particle* firstParticle = new Particle(firstParticleLoc, 1);
	particles.push_back(firstParticle);
	particlesCount = 1;

	// Create all particles
	for(int i = 1; i < Utils::PARTICLES_NUMBER; i++)
	{
		Particle* currentParticle = firstParticle->createParticle();
		particles.push_back(currentParticle);
		firstParticle = currentParticle;
		particlesCount++;
	}
}

LocalizationManager::~LocalizationManager()
{
	// TODO Auto-generated destructor stub
}

void LocalizationManager::updateParticles(Robot* robot, double deltaX, double deltaY, double deltaYaw)
{
	int currBelief;

	for(unsigned int i = 0; i < this->particles.size(); i++)
	{
		currBelief =
			this->particles[i]->update(deltaX, deltaY, deltaYaw, robot);

		//If the belief of the particle is too low - delete the current particle
		if(currBelief < Utils::MIN_BELIEF_THRESHOLD)
		{
			particles.erase(particles.begin() + i);
			particlesCount--;
		}
	}

	for (unsigned int i = 0; i < this->particles.size(); i++){
		// create new one
		if ((particles[i]->belief > Utils::GOOD_BELIEF_THRESHOLD) &&
				(particlesCount < Utils::PARTICLES_NUMBER))
		{
			Particle* son = particles[i]->createParticle();
			particles.push_back(son);
			particlesCount++;
		}
	}
}


Particle* LocalizationManager::getBestParticle()
{
	int bestParticle = 0;

	for(unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles[bestParticle]->belief < particles[i]->belief)
		{
			bestParticle = i;
		}
	}

	return particles[bestParticle];
}
