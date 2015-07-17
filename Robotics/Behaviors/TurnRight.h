#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behaviors.h"

class TurnRight : public Behaviors {
public:
	TurnRight(Robot* robot);
	TurnRight(Robot* robot, float turnAngle);
	void action();
	virtual ~TurnRight();
	bool startCond();
	bool stopCond();
	void stop();
private:
	int angle;
};

#endif
