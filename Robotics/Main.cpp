/*
 * Main.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <iostream>
#include "Robot.h"
#include "ObstacleAvoidPlan.h"

using namespace std;

int main(){
	//Robot robot("localhost", 6665,1);
	ObstacleAvoidPlan pln;

	//Manager manager(&robot, &pln);
	//manager.run();

	//Bonus
	pln.printAstarToPng();

	return 0;
}

