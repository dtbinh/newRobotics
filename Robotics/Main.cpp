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
#include "ConfigurationManager.h"

using namespace std;

int main(){
	const char* path = "/home/colman/Desktop/newRobotics/Robotics/parameters.txt";
	ConfigurationManager* configurationManager = new ConfigurationManager(path);


	char* mapFilePath = configurationManager->mapPath;

	Map map = Map(mapFilePath);

	map.printOriginalMap();

	Matrix<Utils::CELL_STATUS>* originalMap = map.getOriginalMap();

	// Path Finding
	PathFinder* pathFinder = new PathFinder(map.getBlownMap());
	vector<Point*> mapPath = pathFinder->aStar(305, 362,138,169);

	// Bonus
	originalMap->set(305,362, Utils::OCCUPIED);
	for(int i=0; i < mapPath.size(); i++){
		originalMap->set(mapPath[i]->y, mapPath[i]->x, Utils::OCCUPIED);
	}
	originalMap->set(138,169, Utils::OCCUPIED);
	map.saveOrignialMapToPng("/home/colman/Desktop/newMap.png");

	return 0;
}

