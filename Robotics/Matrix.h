/*
 * Matrix.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include "Utils.h"
#include "Point.h"

using namespace std;

template<class T>
class Matrix {
private:
	/**
	 * Declare the matrix
	 */
	T** _matrix;
	int _rows;
	int _columns;

public:
	virtual ~Matrix();

	/**
	 * Constrator - Create new Matrix with the specified size
	 */

	Matrix(int xSize, int ySize);

	T get(int x, int y) const{
		if (x < _rows && y < _columns){
			return _matrix[x][y];
		}

		T value = T();
		return value;
	};

	int getRows() const{
		return _rows;
	};

	int getColumns() const{
		return _columns;
	};

	void set(int x, int y, T value);
	void init(T value);

	void print() const{
		for (int i = 0; i < _rows; i++){
				for (int j = 0; j < _columns; j++){
					cout << get(i, j) << "";
				}
				cout << "\n";
			}
	}
};

#endif /* MATRIX_H_ */
