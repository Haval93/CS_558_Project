/*
Simulation Source File
Assignment #1
Group Members:
Haval Ahmed
Ryan Stevens
Lauren Peppard
Sami Badra
Geoff Crews
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Simulation.h"

// Default Initialize Method. Initializes All Simulation Variables
void Simulation::initialize(int argumentCount, char * fileNames[])
{

}


// Timing Method. Used To Determined Next Event
void Simulation::timing(void)
{

}


// Arrival Function For Entrance Gate
void Simulation::entranceArrive(void)
{

}


// Depart Function For Entrance Gate
void Simulation::entranceDepart(void)
{

}


// Arrival Function For Exit Gate
void Simulation::exitArrive(void)
{

}


// Depart Function For Exit Gate
void Simulation::exitDepart(void)
{

}


// Function to handle car leaving lot event
void Simulation::leaveSpot(void)
{

}


// Update Average Time Stats
void Simulation::updateAverageTimeStats(void)
{

}


// Report Statisical Data
void Simulation::report(void)
{

}


float massDensityFunction()
{
	// F(X) = 24 * 3(1 - X)
	// X is a Random Value Between 0-1 Not Including 1
	float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	// If Random Number is 1 Call Method Again
	if (randomNumber == 1.0)
		return massDensityFunction();

	// Return F(X) = 72(1-X). We should be getting from 0-72
	return 72 * (1 - randomNumber);

}

void Simulation Simulation::initialize(int argumentCount, char * fileNames[])
{
	return void Simulation();
}
