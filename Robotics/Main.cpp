/*
 * Main.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <iostream>
#include "Robot.h"
#include "PathPlanning/PathPlanner.h"

using namespace std;

int main(){
	//Robot robot("localhost", 6665,1);
	const char* CONFIGURATION_PATH = "parameters.txt";
	ConfigurationManager* cm = new ConfigurationManager(CONFIGURATION_PATH);
	PathPlanner pathPlanner(cm);

	//Manager manager(&robot, &pathPlanner);
	//manager.run();

	//Bonus
	pathPlanner.printAstarToPng();

	cout << "finished running";

	return 0;
}

