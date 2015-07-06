/*
 * PathFinder.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: colman
 */

#include "PathFinder.h"

PathFinder::PathFinder(Matrix<Utils::CELL_STATUS>* originalMap) {
	_originalMap = originalMap;
	_robotsGrid = new Matrix<Point*>(_originalMap->getRows(), _originalMap->getColumns());
}

PathFinder::~PathFinder() {
	// TODO Auto-generated destructor stubb
}

Point* PathFinder::getPoint(int x, int y){

	if (_robotsGrid->get(x, y) == NULL){
		_robotsGrid->set(x,y,new Point(x,y, _originalMap->get(x,y) != Utils::OCCUPIED));
	}

	return _robotsGrid->get(x,y);
}


vector<Point*> PathFinder::aStar(float x1, float y1, float x2, float y2){

    vector<Point*> path;

    // Define points to work with
    Point *start = new Point(x1, y1, true);// getPointFromCoord(x1, y1);
    Point *end = new Point(x2, y2, true);// getPointFromCoord(x2, y2);
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

    while (n == 0 || (current != end && n < 50))
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
        for (int x = -1; x < 2; x ++)
        {
            for (int y = -1; y < 2; y ++)
            {
                // If it's current point then pass
                if (x == 0 && y == 0)
                {
                    continue;
                }

                // Get this point
                child = getPoint(current->getX() + x, current->getY() + y);

                // If it's closed or not walkable then pass
                if (child->closed || !child->walkable)
                {
                    continue;
                }

                // If we are at a corner
                if (x != 0 && y != 0)
                {
					Point* nextYPoint = getPoint(current->getX(),
							current->getY() + y);
                    // if the next horizontal point is not walkable or in the closed list then pass

                    if (!nextYPoint->walkable || nextYPoint->closed)
                    {
                        continue;
                    }

                    Point* nextXPoint = getPoint(current->getX() + x, current->getY());
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
        path.push_back(current);
        current = current->getParent();
        n ++;
    }

    return path;
}

