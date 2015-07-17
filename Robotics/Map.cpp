/*
 * Map.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Ori Damari & Or Shainberg
 */

#include "Map.h"

Map* Map::_instance = NULL;

Map* Map::getInstance(){
	if (_instance == NULL){
		_instance = new Map();
	}

	return _instance;
}

Map::Map() {
	loadPng(Utils::configurationManager->mapPath);
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

void Map::saveMapToPng(Matrix<Utils::CELL_STATUS>* map, char* path){
	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(_width * _height * 4);
	unsigned char color;

	// Create the pixels from the map object
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++) {
			if (map->get(y,x) == Utils::FREE)
				color = 255;
			else
				color = 0;
			navImage[y * _width * 4 + x * 4 + 0] = color;
			navImage[y * _width * 4 + x * 4 + 1] = color;
			navImage[y * _width * 4 + x * 4 + 2] = color;
			navImage[y * _width * 4 + x * 4 + 3] = 255;
		}

	saveImageToPng(path,navImage);
}

void Map::saveImageToPng(char* path, std::vector<unsigned char> image){
	unsigned error = lodepng::encode(path, image, _width, _height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void Map::blowMap() {
	_blownMap = new Matrix<Utils::CELL_STATUS>(_height, _width);
	_blownMap->init(_originalMap);

	// Blow map obsticles by robot radius
	int buffer = 2.5;
	int robotRadius = ceil(
			(sqrt(pow(Utils::configurationManager->robotLength / 2, 2) +
				  pow(Utils::configurationManager->robotWidth / 2, 2))
					+ buffer) / Utils::configurationManager->mapResolution);

	// Blow map more softly
	//int robotRadius = ceil(((30/2 + 30/2)/2) / 2.5);

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (_originalMap->get(i,j) == 1) {
				for (int k = i - robotRadius; k <= i + robotRadius;
						k++) {
					for (int l = j - robotRadius; l <= j + robotRadius;
							l++) {
						if (k > 0 && l > 0 && k < _height && l < _width
								&& _originalMap->get(k,l) == 0) {
							_blownMap->set(k,l,Utils::OCCUPIED);
						}
					}
				}
			}
		}
	}
}

