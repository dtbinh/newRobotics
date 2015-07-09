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
	Matrix<Utils::CELL_STATUS>* blownMap = map.getBlownMap();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(blownMap);
	vector<Point*> path = pathFinder->aStar(305, 362,138,169);

	// Bonus
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = originalMap;

	mapToPrintAstarOn->set(305,362, Utils::OCCUPIED);
	for(int i=0; i < path.size(); i++){
		mapToPrintAstarOn->set(path[i]->y, path[i]->x, Utils::OCCUPIED);
	}
	mapToPrintAstarOn->set(138,169, Utils::OCCUPIED);
	map.saveMapToPng(mapToPrintAstarOn, "/home/colman/Desktop/smoothedBlownMap.png");

	std::cout<<"success";

	return 0;
}

