#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behaviors.h"

class TurnLeft : public Behaviors{
private:
	int angle;
public:
	TurnLeft(Robot* robot);
	TurnLeft(Robot* robot, float turnAngle);
	void action();
	virtual ~TurnLeft();
	bool startCond();
	bool stopCond();
	void stop();
};

#endif
