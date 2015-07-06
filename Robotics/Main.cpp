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
	char* mapPath = "/home/colman/Desktop/robotics/Robotics/Robotics/roboticLabMap.png";

	Map map = Map(mapPath);

	//map.printOriginalMap();

	Matrix<Utils::CELL_STATUS>* originalMap = map.getOriginalMap();
	PathFinder* pathFinder = new PathFinder(originalMap);
	vector<Point*> path = pathFinder->aStar(362,305,169,138);

	// TODO: check if astar is correct, by printing the map, Ori: somehow the x and y is opposite again...(305,362) in file
//	originalMap->set(305,362, Utils::BLOWN);
//	for(int i=0; i < path.size(); i++){
//		originalMap->set(path[i]->y, path[i]->x, Utils::BLOWN);
//	}
//	originalMap->set(138,169, Utils::BLOWN);
//
//	originalMap->print();

	return 0;
}

