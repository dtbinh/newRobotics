#include "Behavior.h"

class TurnRight: public Behavior {
public:
	TurnRight(Robot* robot) : Behavior(robot) {}
	virtual ~TurnRight();
	void action();
	bool startCond();
	bool stopCond();
	double availableSpace();
};
