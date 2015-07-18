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
	particleVec.push_back(firstParticle);
	particlesCount = 1;

	// Create all other particles. Each time we create the particle
	// as the son of the last one we created.
	for(int i = 1; i < Utils::PARTICLES_NUMBER; i++)
	{
		Particle* currentParticle = firstParticle->getSon();
		particleVec.push_back(currentParticle);
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

	for(unsigned int i = 0; i < this->particleVec.size(); i++)
	{
		currBelief =
			this->particleVec[i]->getBeliefAndUpdate(deltaX, deltaY, deltaYaw, robot);

		//If the belief of the particle is too low - delete the current particle
		if(currBelief < Utils::MIN_BELIEF_THRESHOLD)
		{
			particleVec.erase(particleVec.begin() + i);

			particlesCount--;
		}
		// If the belief of the particle is good and we're missing
		// some particles - create new one
		else if ((currBelief > Utils::GOOD_BELIEF_THRESHOLD) &&
				(particlesCount < Utils::PARTICLES_NUMBER))
		{
			Particle *son = particleVec[i]->getSon();
			particleVec.push_back(son);
			particlesCount++;
		}
	}
}


Particle* LocalizationManager::getBestParticle()
{
	int bestParticle = 0;

	// Run over the particles vector
	for(unsigned int i = 0; i < particleVec.size(); i++)
	{
		//cout << i <<" : " << particleVec[i]->belief << endl;
		// If the current particle got higher belief then the best particle
		if (particleVec[bestParticle]->belief < particleVec[i]->belief)
		{
			bestParticle = i;
		}
	}

	return particleVec[bestParticle];
}
