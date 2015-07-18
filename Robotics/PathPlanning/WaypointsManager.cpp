/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"


WaypointsManager::WaypointsManager()
{

}

WaypointsManager::WaypointsManager(std::vector <Position*> path)
{
	currWP = new Position(0,0);

	// Check the direction of the first point
	int diffX = (path[1]->getX() - path[0]->getX());
	int diffY = (path[1]->getY() - path[0]->getY());

	for(int i = 2; i < path.size(); i++)
	{
		// Check the direction of the next point
		int nextDiffX = (path[i]->getX() - path[i-1]->getX());
		int nextDiffY = (path[i]->getY() - path[i-1]->getY());

		// If the direction changed
		if (diffX != nextDiffX || diffY != nextDiffY)
		{
			// Insert the point to the waypoints list
			_waypointVector.push_back(path[i-1]);

			diffX = nextDiffX;
		    diffY = nextDiffY;
		}
	}
	currWP = _waypointVector[0];
}

Position* WaypointsManager::getCurrWayPoint() {
	return _waypointVector[_wpIndex];
}

Position* WaypointsManager::getNextWayPoint() {
	Position* nextWP = NULL;

	if (_wpIndex < _waypointVector.size())
	{
		_wpIndex += 1;
		nextWP = _waypointVector[_wpIndex];
		currWP = nextWP;
	}

	return nextWP;
}

bool WaypointsManager::isInWayPoint(double x,double y)
{
	double dx = currWP->getX() - x;
	double dy = currWP->getY() - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	std::cout << "way point x"<< " " << currWP->getX() << " " << "x" << " " << x << std::endl;
	std::cout << "way point y" << " " << currWP->getY() << " " << "y" << " "  << y << std::endl;
	std::cout << "distance: " << distance << std::endl;

	if (distance/**Utils::configurationManager->gridResolution*/ <= Utils::DISTANCE_TOLERANCE)
	{
		std::cout << "waypoint achieved----------------------------------- " << std::endl;
		this->getNextWayPoint();
		return true;
	}
	return false;
}

bool WaypointsManager::isClearPath(int x1, int y1, int x2, int y2)
{
	bool isClear = true;

	int distance = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	if(distance < 20){
		return false;
	}

	int bigX,smallX;
	// find the bigger X's
	if(x1 > x2)
	{
		bigX 	= x1;
		smallX 	= x2;
	}
	else
	{
		bigX 	= x2;
		smallX 	= x1;
	}
	int bigY,smallY;
	// find the bigger Y's
	if(y1 > y2)
	{
		bigY 	= y1;
		smallY 	= y2;
	}
	else
	{
		bigY 	= y2;
		smallY 	= y1;
	}

	Matrix<Utils::CELL_STATUS>* map = Map::getInstance()->getOriginalMap();

	// Set a linear equation
	float a = (float)(y2 - y1) / (x2 - x1);
	for(double i = smallX; (i < bigX && isClear); i+=0.2)
	{
		int y = ((float)a*i) -((float)a*x1) + y1;
		if(map->get(y, i) == Utils::OCCUPIED) {
			isClear = false;
		}

	}
	return isClear;
}

WaypointsManager::~WaypointsManager()
{
	// TODO Auto-generated destructor stub
}

