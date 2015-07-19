/*
 * Point.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: Or Shainberg & Ori Damari
 */

#include "Point.h"
#include <cmath>

Point::Point()
{
    parent = NULL;
    closed = false;
    opened = false;

    x = y = f = g = h = 0;
}

Point::Point(int x, int y, bool w, bool isPointNearObsacles)
{
    Point();

    this->walkable = w;
    this->isPointNearObsacles = isPointNearObsacles;
    this->x = x;
    this->y = y;
}

Point::~Point()
{
}

Point* Point::getParent()
{
    return parent;
}

void Point::setParent(Point *p)
{
    parent = p;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

float Point::getXf()
{
    return (float)x;
}

float Point::getYf()
{
    return (float)y;
}

int Point::getGScore(Point *p)
{
	int extraCostForObstaclesCloseness = isPointNearObsacles ? 10 : 0;

    return p->g + ((x == p->x || y == p->y) ? 10 : 14) + extraCostForObstaclesCloseness;
}

int Point::getHScore(Point *p)
{
    return (fabs(p->x - x) + fabs(p->y - y)) * 10;
}

int Point::getGScore()
{
    return g;
}

int Point::getHScore()
{
    return h;
}

int Point::getFScore()
{
    return f;
}

void Point::computeScores(Point *end)
{
    g = getGScore(parent);
    h = getHScore(end);
    f = g + h;
}

bool Point::hasParent()
{
    return parent != NULL;
}

