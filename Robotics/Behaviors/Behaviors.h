#ifndef BEHAVIORS_H_
#define BEHAVIORS_H_

#include "../Robot.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

class Behaviors {
protected:
	Robot* _robot;
	vector<Behaviors *> nextBehavior;
public:
	Behaviors(Robot* robot);

	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	virtual void stop() = 0;
	virtual Behaviors* getNextBehavior();

	Behaviors* addNextBehavior(Behaviors* behavior);

	~Behaviors();

	static int degreeToIndex(int deg)
	{
		return round((deg+120)/0.36);
	}
};

#endif
