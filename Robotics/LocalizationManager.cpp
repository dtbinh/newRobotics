/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager()
{

	// Create the first particle in the middle of the map with some default angle
	Location* firstParticleLoc = new Location(/*Map::getInstance()->configM.getStartLocationX(),
											  Map::getInstance()->configM.getStartLocationY(),
											  Map::getInstance()->configM.getStartLocationYaw()*/1,2,3);

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

void LocalizationManager::UpdateParticles(Robot* robot, double deltaX, double deltaY, double deltaYaw)
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


Particle* LocalizationManager::GetBestParticle()
{
	int bestParticle = 0;

	// Run over the particles vector
	for(unsigned int i = 0; i < particleVec.size(); i++)
	{
		// If the current particle got higher belief then the best particle
		if (particleVec[bestParticle]->belief < particleVec[i]->belief)
		{
			bestParticle = i;
		}
	}

	return particleVec[bestParticle];
}
