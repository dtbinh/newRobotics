#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behaviors.h"

using namespace std;

class GoForward: public Behaviors {
	float turnAngle;
public:
	GoForward(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	void stop();
	virtual ~GoForward();
};

#endif
