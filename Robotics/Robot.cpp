#include "Robot.h"
#include "math.h"

using namespace std;

Robot::Robot(char* host, int port):_pc(host,port), _pp(&_pc),_lp(&_pc)
{
}

double Robot::getLaserScan(int index)
{
	return _lp[index];
}

void Robot::Read()
{
	_pc.Read();
}

void Robot::setSpeed(double forwardSpeed, double rotationSpeed)
{
	_pp.SetSpeed(forwardSpeed,rotationSpeed);
	_pp.SetMotorEnable(true);
}

double Robot::getXPos()
{
	return _pp.GetXPos();
}

double Robot::getYPos()
{
	return _pp.GetYPos();
}

double Robot::getYaw()
{
	return _pp.GetYaw();
}

Robot::~Robot()
{
	delete &_pc;
	delete &_pp;
	delete &_lp;
}
