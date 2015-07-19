/*
 * Utils.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "ConfigurationManager.h"
#include <cmath>

class Utils {
public:
	Utils();
	virtual ~Utils();
	enum CELL_STATUS {FREE, OCCUPIED, BLOWN};
	static ConfigurationManager* configurationManager;

	static double convertDegreeToRadian(double degree);
	static double convertRadianToDegree(double radian);
	static double convertPixelToMeter(double inPixel);
	static double convertMeterToPixel(double inMeter);

	// Particles
	static const int PARTICLES_NUMBER = 100;
	static const double MIN_BELIEF_THRESHOLD = 0.3;
	static const double GOOD_BELIEF_THRESHOLD = 0.7;

	// Probability
	static const double PERFECT_PROB = 1;
	static const double HIGH_PROB = 0.9;
	static const double MEDIUM_PROB = 0.6;
	static const double LOW_PROB = 0.4;
	static const double DISTANCE_PROB_THRESHOLD = 0.22;
	static const double YAW_PROB_THRESHOLD = 20;
	static const double PROB_NORMAL_CONST = 1.6;

	// Others
	static const double CELL_SIZE = 0.1;
	static const double ANGULAR_RESULUTION = 0.36;

	// Laser Proxy
	static const float FORWARD_LASER_PROXY_VALUE = 332;
	static const float RIGHT_LASER_PROXY_VALUE = 50;
	static const float LEFT_LASER_PROXY_VALUE = 614;

	// Behavior
	static const float DISTANCE_TOLERANCE = 10;
	static const float MAX_LASER_INDEX = 665;
};

#endif /* UTILS_H_ */
