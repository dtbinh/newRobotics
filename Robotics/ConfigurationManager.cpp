/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include <iostream>

ConfigurationManager::ConfigurationManager(const char* configurationFilePath) {
	char file_data[10][100];
	char attribute_name[200];
	ifstream inputFile;
	inputFile.open(configurationFilePath, ios::in);
	int counter = 0;

	while (!inputFile.eof()){
		inputFile.getline(attribute_name, 100, ' ');
		inputFile.getline(file_data[counter],100, '\n');
		counter++;
	}

	inputFile.close();

	string mapString = file_data[0];
	if (!mapString.empty() && mapString[mapString.size() - 1] == '\r'){
		mapString.erase(mapString.size() - 1);
	}
	this->mapPath = new char[1024];
	strcpy(this->mapPath, mapString.c_str());
	string startLocation = file_data[1];
	this->xStartLocation = atoi(startLocation.substr(0, startLocation.find_first_of(' ')).c_str());
	startLocation = startLocation.substr(startLocation.find_first_of(' ') + 1);
	this->yStartLocation = atoi(startLocation.substr(0, startLocation.find_first_of(' ')).c_str());
	startLocation = startLocation.substr(startLocation.find_first_of(' ') + 1);
	this->yawStartLocation = atoi(startLocation.c_str());
	string goal = file_data[2];
	this->xTarget = atoi(goal.substr(0, goal.find_first_of(' ')).c_str());
	goal = goal.substr(goal.find_first_of(' ') + 1);
	this->yTarget = atoi(goal.c_str());
	string robotSize = file_data[3];
	this->robotLength = atoi(robotSize.substr(0, robotSize.find_first_of(' ')).c_str());
	robotSize = robotSize.substr(robotSize.find_first_of(' ') + 1);
	this->robotWidth = atoi(robotSize.c_str());
	string MapResolutionCM = file_data[4];
	this->mapResolution = atof(MapResolutionCM.c_str());
	string GridResolutionCM = file_data[5];
	this->gridResolution = atof(GridResolutionCM.c_str());

	this->robotLength = this->robotLength / this->mapResolution;
	this->robotWidth = this->robotWidth / this->mapResolution;
}

ConfigurationManager::~ConfigurationManager() {
	delete [] this->mapPath;
}

