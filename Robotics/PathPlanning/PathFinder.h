/*
 * PathFinder.h
 *
 *  Created on: Jun 29, 2015
 *      Author: colman
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <list>
#include <vector>
#include <cstddef>
#include "Point.h"
#include "../Position.h"
#include "../Location.h"
#include "../Matrix.h"

using namespace std;

class PathFinder {
public:
	PathFinder();
	PathFinder(Matrix<Utils::CELL_STATUS>* map);
	virtual ~PathFinder();
	vector<Position*> aStar(float x1, float y1, float x2, float y2);
	Matrix<Point*>* _robotsGrid;
	Matrix<Utils::CELL_STATUS>* _map;
	Point* getPoint(int x, int y);
};

#endif /* PATHFINDER_H_ */
