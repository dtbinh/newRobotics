/*
 * Main.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <iostream>
#include "Robot.h"
#include "PathPlanning/PathPlanner.h"
#include "Manager.h"

using namespace std;

int main(){

	Robot robot("localhost", 6665);
	PathPlanner* pathPlanner = new PathPlanner();

	Manager manager(&robot, pathPlanner);
	manager.run();
	/*
	//Robot robot("localhost", 6665,1);
	//const char* CONFIGURATION_PATH = "parameters.txt";
	//Utils::configurationManager = new ConfigurationManager(CONFIGURATION_PATH);
	PathPlanner pathPlanner;

	//Manager manager(&robot, &pathPlanner);
	//manager.run();

	//Bonus
	pathPlanner.printAstarToPng();

	cout << "finished running";
*/
	return 0;
}

