#include "Behavior.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot) : Behavior(robot) {}
	virtual ~TurnLeft();
	void action();
	bool startCond();
	bool stopCond();
	double availableSpace();
};
