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
	Matrix<Utils::CELL_STATUS>* blownMap = map.getBlownMap();

	// Path Finding

	PathFinder* pathFinder = new PathFinder(blownMap);
	vector<Point*> mapPath =
			pathFinder->aStar(configurationManager->yStartLocation, configurationManager->xStartLocation,
							  configurationManager->yTarget, configurationManager->xTarget);

	// Bonus
	Matrix<Utils::CELL_STATUS>* mapToPrintAstarOn = originalMap;

	mapToPrintAstarOn->set(configurationManager->yStartLocation, configurationManager->xStartLocation, Utils::OCCUPIED);
	for(int i=0; i < mapPath.size(); i++){
		mapToPrintAstarOn->set(mapPath[i]->y, mapPath[i]->x, Utils::OCCUPIED);
	}
	mapToPrintAstarOn->set(configurationManager->yTarget, configurationManager->xTarget, Utils::OCCUPIED);
	map.saveMapToPng(mapToPrintAstarOn, "/home/colman/Desktop/smoothedBlownMap.png");

	std::cout<<"success";

	return 0;
}

