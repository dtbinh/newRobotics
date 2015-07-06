/*
 * Map.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h";
#include "Matrix.h"
#include "Utils.h"
#include "Point.h"

class Map {
	Matrix<Utils::CELL_STATUS>* _originalMap;
	int _height, _width;
public:
	Map(char* mapPath);
	virtual ~Map();

	void loadPng(char* mapPath);
	void blowMap();
	void printOriginalMap() const{
		_originalMap->print();
	}
	Matrix<Utils::CELL_STATUS>* getOriginalMap() const{
		return _originalMap;
	}
};

#endif /* MAP_H_ */
