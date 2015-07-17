/*
 * Robot.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, int grid_rows) {
	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_grid_rows = grid_rows;

	_pp->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();

	//_pp->SetOdometry(((double)Map::getInstance()->configM.getStartLocationX() / (Map::getInstance()->configM.getGridResolutionCM() / Map::getInstance()->configM.getMapResolutionCM())/ (Map::getInstance()->configM.getGridResolutionCM())), ((_grid_rows / Map::getInstance()->configM.getGridResolutionCM()) - (((double)Map::getInstance()->configM.getStartLocationY()) / (Map::getInstance()->configM.getGridResolutionCM() / Map::getInstance()->configM.getMapResolutionCM())/ (Map::getInstance()->configM.getGridResolutionCM()))) ,Map::getInstance()->configM.getStartLocationYaw()*M_PI/180);
}

void Robot::Read()
{
	//_pc->Read();
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

bool Robot::isRightFree() {
	if ((*_lp)[RIGHT_LASER_PROXY_VALUE] > Utils::DISTANCE_TOLERANCE)
		return true;
	else
		return false;
}

bool Robot::isLeftFree() {
	if ((*_lp)[LEFT_LASER_PROXY_VALUE] > Utils::DISTANCE_TOLERANCE)
		return true;
	else
		return false;
}

bool Robot::isForwardFree() {
	if ((*_lp)[FORWARD_LASER_PROXY_VALUE] > Utils::DISTANCE_TOLERANCE)
		return true;
	else
		return false;
}

double Robot::getXpos()
{
	//return ((_pp->GetXPos()) * Map::configM.getGridResolutionCM());
	return 1;
}

double Robot::getYpos()
{
	//return (((_grid_rows / Map::getInstance()->configM.getGridResolutionCM()) - _pp->GetYPos()) * Map::getInstance()->configM.getGridResolutionCM());
	return 1;
}

double Robot::getYaw()
{
	double yaw = 180*(_pp->GetYaw())/M_PI;
	if(yaw >= 0)
	{
		return (yaw);
	}
	else
	{
		return (360+yaw);
	}
}

LaserProxy* Robot::getLaser()
{
	return (_lp);
}

float Robot::getLaserDistance(int index)
{
    return _lp->GetRange(index);
}

bool Robot::checkRange(int nStart, int nEnd)
{
    bool is_dis_Good = true;

    for (int index = nStart; (index <= nEnd) && (is_dis_Good); index++)
    {
    	is_dis_Good = (this->getLaserDistance(index) > Utils::DISTANCE_TOLERANCE);
    }

    return (is_dis_Good);
}


double Robot::getLaserSpec()
{
	return(((_lp->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}

Robot::~Robot()
{
	delete _pc;
	delete _pp;
	delete _lp;
}
