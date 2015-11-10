/*
Class: CS 558
Project: Parking Lot Project For Assignment #1
Descripition: Parking Lot With One Entrance and One Exit System
Group Members:
Haval Ahmed
Ryan Stevens
Lauren Peppard
Sami Badra
Geoff Crews
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include "Simulation.h"

// Main Function
int main(int argc, char * argv[])
{
	// Random See With Time. Need For Random Variates
	srand(static_cast<unsigned> (time(NULL)));

	// Create A Simulation Instance
	Simulation_Information firstSimulation = Simulation_Information(argc, argv);

	// Simulation Loop. Run Simulation Until Exit Parameter is met.
	/*while (firstSimulation.numberOfCustomersDelayed < firstSimulation.totalNumberOfCustomers)
	{
		// Call Timing, Arrival, Exit, and Report Functions within simulation class. 
		// Will either be switch case or something else?
	}*/

	std::cout << "Test to see if update reflected instance of class: " << firstSimulation.totalNumberOfCustomers << std::endl;

	return 0;
}