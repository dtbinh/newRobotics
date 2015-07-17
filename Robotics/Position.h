/*
 * Position.h
 *
 *  Created on: Jun 22, 2015
 *      Author: colman
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
private:
	float _x;
	float _y;
public:
	Position(float x, float y);
	virtual ~Position();
	float getX(){return _x;}
	float getY(){return _y;}

};

#endif /* POSITION_H_ */
