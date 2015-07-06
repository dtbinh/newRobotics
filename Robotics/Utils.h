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
};

#endif /* UTILS_H_ */
