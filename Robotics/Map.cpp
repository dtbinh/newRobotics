/*
 * Map.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#include <cmath>
#include "Map.h"
#include "Utils.h"
#include "lodepng.h"

Map::Map(char* mapPath) {
	loadPng(mapPath);
	blowMap();
}

Map::~Map() {
	delete _originalMap;
}

void Map::loadPng(char* mapPath){

	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, mapPath);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
	else {
		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

		_originalMap = new Matrix<Utils::CELL_STATUS>(height, width);
		_originalMap->init(Utils::OCCUPIED);
		_height = height;
		_width = width;

		for (unsigned int y = 0; y < height; y++) {
			for (unsigned int x = 0; x < width; x++) {
				if (image[y * width * 4 + x * 4 + 0]
						|| image[y * width * 4 + x * 4 + 1]
						|| image[y * width * 4 + x * 4 + 2])
					_originalMap->set(y,x, Utils::FREE);
				else
					_originalMap->set(y,x, Utils::OCCUPIED);
			}
		}
	}
}

void Map::blowMap() {
	// Blow map obsticles by robot radius
	int buffer = 2.5;
	int robotRadius = ceil(
			(sqrt(pow(30 / 2, 2) + pow(30 / 2, 2))
					+ buffer) / 2.5);

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (_originalMap->get(i,j) == 1) {
				for (int k = i - robotRadius; k <= i + robotRadius;
						k++) {
					for (int l = j - robotRadius; l <= j + robotRadius;
							l++) {
						if (k > 0 && l > 0 && k < _height && l < _width
								&& _originalMap->get(k,l) == 0) {
							_originalMap->set(k,l,Utils::BLOWN);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (_originalMap->get(i,j) == Utils::BLOWN) {
				_originalMap->set(i,j,Utils::OCCUPIED);
			}
		}
	}
}

