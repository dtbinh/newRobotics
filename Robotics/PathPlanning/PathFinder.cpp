/*
 * PathFinder.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: colman
 */

#include "PathFinder.h"

PathFinder::PathFinder(Matrix<Utils::CELL_STATUS>* map) {
	_map = map;
	_robotsGrid = new Matrix<Point*>(map->getRows(), map->getColumns());
}

PathFinder::~PathFinder() {
	delete _robotsGrid;
}

Point* PathFinder::getPoint(int row, int col){
	if (_robotsGrid->get(row, col) == NULL){
		bool isPointWalkable = _map->get(row,col) != Utils::OCCUPIED;
		bool isPointNearObsacles = false;

		// Check if the point is near obstacles
		if (isPointWalkable){
			int halfRadius = 5;
			for (int y = -halfRadius; y <= halfRadius && !isPointNearObsacles; y++){
				for (int x = -halfRadius; x <= halfRadius; x++){
					if (_map->get(row+y,col+x) != Utils::FREE){
						isPointNearObsacles = true;
						break;
					}
				}
			}
		}

		Point* newPoint = new Point(col,row, isPointWalkable, isPointNearObsacles);
		_robotsGrid->set(row,col, newPoint);
	}

	return _robotsGrid->get(row,col);
}


vector<Position*> PathFinder::aStar(float row1, float col1, float row2, float col2){
    vector<Position*> path;

    // Define points to work with
    Point *start = getPoint(row1, col1);
    Point *end = getPoint(row2, col2);
    Point *current;
    Point *child;

    // Define the open and the close list
    list<Point*> openList;
    list<Point*> closedList;
    list<Point*>::iterator i;

    unsigned int n = 0;

    // Add the start point to the openList
    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (n < 1000 && (current->x != end->x || current->y != end->y)))
    {
        // Look for the smallest F value in the openList and make it the current point
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
            {
                current = (*i);
            }
        }

        // Stop if we reached the end
        if (current == end)
        {
            break;
        }

        // Remove the current point from the openList
        openList.remove(current);
        current->opened = false;

        // Add the current point to the closedList
        closedList.push_back(current);
        current->closed = true;

        // Get all current's adjacent walkable points
        for (int x = -1; x <= 1; x ++)
        {
            for (int y = -1; y <= 1; y ++)
            {
                // If it's current point then pass
                if (x == 0 && y == 0)
                {
                    continue;
                }

                // Get this point
                child = getPoint(current->getY() + y, current->getX() + x);

                // If it's closed or not walkable then pass
                if (child->closed || !child->walkable)
                {
                    continue;
                }

                // If we are at a corner
                if (x != 0 && y != 0)
                {
					Point* nextYPoint = getPoint(current->getY() + y, current->getX());
                    // if the next horizontal point is not walkable or in the closed list then pass

                    if (!nextYPoint->walkable || nextYPoint->closed)
                    {
                        continue;
                    }

                    Point* nextXPoint = getPoint(current->getY(), current->getX() + x);
                    // if the next vertical point is not walkable or in the closed list then pass
                    if (!nextXPoint->walkable || nextXPoint->closed)
                    {
                        continue;
                    }
                }

                // If it's already in the openList
                if (child->opened)
                {
                    // If it has a wroste g score than the one that pass through the current point
                    // then its path is improved when it's parent is the current point
                    if (child->getGScore() > child->getGScore(current))
                    {
                        // Change its parent and g score
                        child->setParent(current);
                        child->computeScores(end);
                    }
                }
                else
                {
                    // Add it to the openList with current point as parent
                    openList.push_back(child);
                    child->opened = true;

                    // Compute it's g, h and f score
                    child->setParent(current);
                    child->computeScores(end);
                }
            }
        }

        n ++;
    }

    // Reset
    for (i = openList.begin(); i != openList.end(); ++ i)
    {
        (*i)->opened = false;
    }
    for (i = closedList.begin(); i != closedList.end(); ++ i)
    {
        (*i)->closed = false;
    }

    // Resolve the path starting from the end point
    while (current->hasParent() && current != start)
    {
        path.push_back(new Position(current->x, current->y));
        current = current->getParent();
        n ++;
    }

    return path;
}

