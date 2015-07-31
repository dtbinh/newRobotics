#ifndef ROBOT_H_
#define ROBOT_H_

#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Map.h"

using namespace std;
using namespace PlayerCc;

class Robot {
private:
	double _startYaw;
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
public:
	Robot(char* host, int port);
	virtual ~Robot();
	double getLaserScan(int index);
	void Read();
	void setSpeed(double linearSpeed, double angularSpeed);
	double getXPos();
	double getYPos();
	double getYaw();
	void setOdometry();
};

#endif /* ROBOT_H_ */
