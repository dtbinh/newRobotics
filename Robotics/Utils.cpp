/*
 * Utils.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "Utils.h"

ConfigurationManager* Utils::configurationManager = new ConfigurationManager("parameters.txt");

double Utils::convertDegreeToRadian(double degree){
	 return ((degree) * (M_PI / 180.0));
}

double Utils::convertRadianToDegree(double radian){
	 return ((radian) * (180.0 / M_PI));
}

double Utils::convertPixelToMeter(double inPixel)
{
	return inPixel*Utils::configurationManager->mapResolution/100;
}
double Utils::convertMeterToPixel(double inMeter)
{
	return inMeter*100/Utils::configurationManager->mapResolution;
}

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

