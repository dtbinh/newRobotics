/*
 * Matrix.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#include "Matrix.h"

template<class T>
Matrix<T>::Matrix(int xSize, int ySize) {

	_matrix = new T*[xSize];
	for (int i = 0; i < xSize; i++){
		_matrix[i] = new T[ySize];
	}

	_rows = xSize;
	_columns = ySize;
}

template<class T>
void Matrix<T>::init(T value) {
	for (int r = 0; r < _rows; r++){
		for (int c = 0; c < _columns; c++){
			_matrix[r][c] = value;
		}
	}
}

template<class T>
void Matrix<T>::set(int x, int y, T value) {
	_matrix[x][y] = value;
}

template<class T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < _rows; i++){
		delete [] _matrix[i];
	}
	delete [] _matrix;
}


template class Matrix<Utils::CELL_STATUS>;
template class Matrix<Point*>;
