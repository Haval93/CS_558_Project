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
#include <fstream>
#include "Simulation.h"

// Default Constructor. Initializes
Simulation_Information::Simulation_Information()
{
	// Default Initialization Variables. Will be Read In Exactly This Order
	numberOfCars = 60;
	arrivalRate = 60;
	parkIntervalHigh = 120;
	parkIntervalLow = 60;
	exitGate = 60;
	entranceQueueSize = 500;
	exitQueueSize = 500;

	// Statistical Counters. More Will Be Added
	nextEventType = 0;
	numberOfCustomersDelayed = 0;
	totalNumberOfCustomers = 0;
	numberOfEvents = 0;
	numberInEntranceQueue = 0;
	numberInExitQueue = 0;
	entranceServerStatus = 0;
	exitServerStatus = 0;
	serviceTime = 0;

	// Make Each Parking Spot Null or 0. We will add or replace the spot with zero after the spot is taken. 
	for (int i = 0; i < parkingSpots; i++)
		parkingLotSpots[i] = EMPTY;

}
// Overloaded Constructor. Initializes 
Simulation_Information::Simulation_Information(int argc, char * argv[])
{
	// Create A File Instance
	std::fstream simulationInput;

	// Open File
	simulationInput.open(argv[1]);

	while (simulationInput.is_open() && simulationInput.good())
	{
		// Number of cars
		simulationInput >> numberOfCars;
		// Arrival Rate
		simulationInput >> arrivalRate;
		// Interarrival High Rate
		simulationInput >> parkIntervalHigh;
		// Interarrival Low Rate
		simulationInput >> parkIntervalLow;
		// Exit Gate
		simulationInput >> exitGate;
		// Entrace Queue Size
		simulationInput >> entranceQueueSize;
		// Exit Queue Size 
		simulationInput >> exitQueueSize;
	}

	// Close File 
	simulationInput.close();


	// Statistical Counters. More Will Be Added
	nextEventType = 0;
	numberOfCustomersDelayed = 0;
	totalNumberOfCustomers = 0;
	numberOfEvents = 0;
	numberInEntranceQueue = 0;
	numberInExitQueue = 0;
	entranceServerStatus = 0;
	exitServerStatus = 0;
	serviceTime = 0;

}


// Timing Method. Used To Determined Next Event
void Simulation_Information::timing(void)
{

}


// Arrival Function For Entrance Gate
void Simulation_Information::entranceArrive(void)
{

}


// Depart Function For Entrance Gate
void Simulation_Information::entranceDepart(void)
{

}


// Arrival Function For Exit Gate
void Simulation_Information::exitArrive(void)
{

}


// Depart Function For Exit Gate
void Simulation_Information::exitDepart(void)
{

}


// Function to handle car leaving lot event
void Simulation_Information::leaveSpot(void)
{

}


// Update Average Time Stats
void Simulation_Information::updateAverageTimeStats(void)
{

}


// Report Statisical Data
void Simulation_Information::report(void)
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
