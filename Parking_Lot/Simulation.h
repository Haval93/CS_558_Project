/*
Simulation Header File
Members:
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
#include <vector>
#include <queue>

#ifndef Simulation
#define Simulation

// Car Structure For All Automobile Information
class Car
{
public:
	int carNumber;
	// Variable For Entrance Arrival Time (Enter Queue)
	float entranceArrivalTime;
	// Variable For Entrance Depart Time (Exit Queue To Look For Parking)
	float entranceDepartTime;
	// Increment Variable For Amount of Times Looking For Empty Parking Spot
	int numberOfTimesLooked;
	// Time Spent Looking For Spot
	float timeSpentLooking;
	// Variable For Parking Spot
	int parkingSpotLocation;
	// Variable For Parking Time Length
	float parkingTimeLength;
	// Variable For Exit Arrival Time (Enter Queue To Leave Parking Lot)
	float exitArrivalTime;
	// Variable For Exit Depart Time (What Time They Left Exit Queue)
	float exitDepartTime;
	// Total Time In System
	float totalTimeInSystem;
	// time it takes to get to the exit
	float exitTime;

	// Default Constructor
	Car() 
	{
		int carNumber = 0;
		// Variable For Entrance Arrival Time (Enter Queue)
		float entranceArrivalTime = 0.0;
		// Variable For Entrance Depart Time (Exit Queue To Look For Parking)
		float entranceDepartTime = 0.0;
		// Increment Variable For Amount of Times Looking For Empty Parking Spot
		int numberOfTimesLooked = 0;
		// Time Spent Looking For Spot
		float timeSpentLooking = 0.0;
		// Variable For Parking Spot
		int parkingSpotLocation = 0;
		// Variable For Parking Time Length
		float parkingTimeLength = 0.0;
		// Variable For Exit Arrival Time (Enter Queue To Leave Parking Lot)
		float exitArrivalTime = 0.0;
		// Variable For Exit Depart Time (What Time They Left Exit Queue)
		float exitDepartTime = 0.0;
		// Total Time In System
		float totalTimeInSystem = 0.0;
	}
};


// Simulation Info Structure
class Simulation_Information
{
public:
	// Variables For Simulation
	const static int NUMOFEVENTS = 6;
	int parkingSpots, numberOfCars; 
	float arrivalRate, parkIntervalHigh, parkIntervalLow, exitGate, simulationTime, timeOfLastEvent;

	// Statistical Counter Variables
	int nextEventType, numberOfCustomersDelayed, totalNumberOfCustomers,
		numberInEntranceQueue, numberInExitQueue, entranceServerStatus, leavingIndex,
		exitServerStatus, maxEntranceQueueSize, maxExitQueueSize, parked;
	float totalEntranceQueueDelayTime, totalExitQueueDelayTime, nextLeavingCar, timeSinceLastEvent,
		areaUnderEntranceQueue, areaUnderExitQueue, areaEntranceServerStatus, areaExitServerStatus, totalSearchTime, exitTime;

	// Parking Lot Array. Initializing as a vector and will resize dynamically based on user input
	std::vector <float> parkingLotSpots;
	// Entrace And Exit Queue
	std::queue <Car> entranceQueue;
	std::queue <Car> exitQueue;
	// Car List
	std::vector <Car> arrayOfCars;

	// Time of Next Array Event That Will Tell Simulation When The Next Simulated Event Is.
	// Will Be A Constant Size 6 For Size of All Event Handling Functions for Simulation.  
	float timeOfNextEvent[NUMOFEVENTS];

	// Overloaded Constructor. Overloaded Initialization Method
	Simulation_Information(int argc, char * argv[]);
	// Timing Method. Used To Determined Next Event
	void timing(void);
	// Event Function. Chose next event type
	void chooseNextEvent(void);
	// Arrival Function For Entrance Gate
	void entranceArrive(void);
	// Depart Function For Entrance Gate
	void entranceDepart(void);
	// Arrival Function For Exit Gate
	void exitArrive(void);
	//push onto the exit queue
	void exitQueueHelper(int);
	// Depart Function For Exit Gate
	void exitDepart(void);
	// Function to handle car leaving lot event
	void leaveSpot(void);
	// Update Average Time Stats
	void updateAverageTimeStats(void);
	// Report Statisical Data
	void report(void);
};


// Mass Density Function 
float massDensityFunction();
float ParkingTime(float parkIntervalLow, float parkIntervalHigh);


#endif