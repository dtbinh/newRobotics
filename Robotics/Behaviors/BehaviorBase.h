#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#define RIGHT_LIMIT_LASER_INDEX 260
#define LEFT_LIMIT_LASER_INDEX 406
#define CENTER_LASER_INDEX 333
#define MIN_FRONT_DISTANCE 0.6
#define MIN_SIDE_DISTANCE 0.2
#define FORWARD_SPEED 0.4
#define ROTATION_SPEED 0.3

#include "../Robot.h"
#include "../Utils.h"

class Behavior {
	Behavior** _nextBehaviors;
	int _nextBehaviorsCount;
protected:
	Robot* _robot;
public:
	Behavior(Robot* robot): _nextBehaviors(NULL),_nextBehaviorsCount(0),_robot(robot){}
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	//virtual double availableSpace() = 0;
	bool addNextBehavior(Behavior* behaviorToAdd);
	Behavior* selectNextBehavior();
};

#endif /* BEHAVIOR_H_ */
