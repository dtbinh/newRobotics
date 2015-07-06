/*
 * Point.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: Or Shainberg & Ori Damari
 */

#include "Point.h"


Point::Point()
{
    parent = NULL;
    closed = false;
    opened = false;

    x = y = f = g = h = 0;
}

Point::Point(int x, int y, bool w)
{
    Point();

    this->walkable = w;
    this->x = x;
    this->y = y;
}

Point::~Point()
{
}

//Location* Point::getPosition()
//{
//    return new Location((float)(x * 64), (float)(y * 64));
//}

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
    return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}

int Point::getHScore(Point *p)
{
	int absX = p->x - x;

	if (absX < 0){
	 absX = absX * -1;
	}
	int absY = p->y - y;

	if (absY < 0){
		absY = absY * -1;
	}
    return (absX + absY) * 10;
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

