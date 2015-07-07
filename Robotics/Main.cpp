/*
 * Main.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <iostream>
#include "Map.h"
#include "Utils.h"
#include "PathFinder.h"

using namespace std;

int main(){
	char* mapPath = "/home/colman/Desktop/newRobotics/Robotics/roboticLabMap.png";

	Map map = Map(mapPath);

	//map.printOriginalMap();

	Matrix<Utils::CELL_STATUS>* originalMap = map.getOriginalMap();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(map.getBlownMap());
	vector<Point*> path = pathFinder->aStar(305, 362,138,169);

	// Bonus
	originalMap->set(305,362, Utils::OCCUPIED);
	for(int i=0; i < path.size(); i++){
		originalMap->set(path[i]->y, path[i]->x, Utils::OCCUPIED);
	}
	originalMap->set(138,169, Utils::OCCUPIED);
	map.saveOrignialMapToPng("/home/colman/Desktop/newMap.png");

	return 0;
}

