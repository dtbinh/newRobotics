#include "Behaviors.h"

Behaviors::Behaviors(Robot* robot) : _robot(robot), nextBehavior(NULL){
}

// add behavior to the array
Behaviors* Behaviors::addNextBehavior(Behaviors* behavior)
{
	nextBehavior.push_back(behavior);
	return this;
}

Behaviors* Behaviors::getNextBehavior()
{
	for (int i = 0; i < nextBehavior.size(); i++)
	{
		if (nextBehavior[i]->startCond())
		{
			return nextBehavior[i];
		}
	}

	return NULL;
}

Behaviors::~Behaviors() {
	std::vector<Behaviors*>().swap(nextBehavior);
}
