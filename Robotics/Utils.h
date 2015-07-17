/*
 * Utils.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */
#ifndef UTILS_H_
#define UTILS_H_

class Utils {
public:
	Utils();
	virtual ~Utils();
	enum CELL_STATUS {FREE, OCCUPIED, BLOWN};
	static char* pngPath;

	// Laser Proxy
	#define FORWARD_LASER_PROXY_VALUE 332
	#define RIGHT_LASER_PROXY_VALUE 50
	#define LEFT_LASER_PROXY_VALUE 614

	// Behavior
	static const float SPEED = 0.40;
	static const int   FORWARD_WALL_HITS = 7;
	static const float RIGHT_ANGLE = 80;
	static const float LEFT_ANGLE = 280;
	static const float YAW_SPEED = 0.3;
	static const float SAFE_DISTANCE = 0.65;
	static const float DISTANCE_TOLERANCE = 0.3;
};

#endif /* UTILS_H_ */
