#include "Behavior.h"

class GoForward : public Behavior {
public:
	GoForward(Robot* robot) : Behavior(robot) {}
	virtual ~GoForward();
	void action();
	bool startCond();
	bool stopCond();
	double availableSpace();
};
