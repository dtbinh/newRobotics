/*
 * Point.h
 *
 *  Created on: Jun 29, 2015
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include "Location.h"
#include <cstddef>

class Point {
public:
	Point();
	Point(int x, int y, bool w);
	virtual ~Point();

	Point* parent;
	bool opened;
	bool closed;
	bool walkable;
	int x,  y,  f,  g,  h;

	//Location* getPosition();
	Point* getParent();
	void setParent(Point *p);
	int getX();
	int getY();
	float getXf();
	float getYf();
	int getGScore(Point *p)	;
	int getHScore(Point *p)	;
	int getGScore();
	int getHScore();
	int getFScore();
	void computeScores(Point *end);
	bool hasParent();
};

#endif /* POINT_H_ */
