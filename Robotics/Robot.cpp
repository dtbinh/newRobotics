#include "Robot.h"
#include "math.h"

using namespace std;

Robot::Robot(char* host, int port):_pc(host,port), _pp(&_pc),_lp(&_pc)
{
	_startYaw = Utils::convertDegreeToRadian(Utils::configurationManager->yawStartLocation);

	_pp.SetMotorEnable(true);
	_pp.SetOdometry(0,0,_startYaw); // do this to intialize the yaw in the robot's odometry
}

void Robot::setOdometry()
{
	_pp.SetOdometry(0,0,_startYaw);
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
}

double Robot::getXPos()
{
	return Utils::configurationManager->xStartLocation + Utils::convertMeterToPixel(_pp.GetXPos());
	//return _pp.GetXPos();
}

double Robot::getYPos()
{
	return Utils::configurationManager->yStartLocation - Utils::convertMeterToPixel(_pp.GetYPos());
	//return _pp.GetYPos();
}

double Robot::getYaw()
{
	return Utils::convertRadianToDegree(_pp.GetYaw());
}

Robot::~Robot()
{
	delete &_pc;
	delete &_pp;
	delete &_lp;
}
