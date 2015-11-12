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

// Mnemonic For Server Busy
#define BUSY 1  
// Mnemonic For Service IDLE
#define IDLE 0  
// Empty Spot
#define EMPTY (1.0e+30)

// Car Structure For All Automobile Information
class Car
{
public:
	Car();
	int carNumber;
	// Variable For Entrance Arrival Time (Enter Queue)
	float entranceArrivalTime;
	// Variable For Entrance Depart Time (Exit Queue To Look For Parking)
	float entranceDepartTime;
	// Increment Variable For Amount of Times Looking For Empty Parking Spot
	int numberOfTimesLooked;
	// Variable For Parking Spot
	int parkingSpotLocation;
	// Variable For Parking Time Length
	float parkingTimeLength;
	// Variable For Exit Arrival Time (Enter Queue To Leave Parking Lot)
	float exitArrivalTime;
	// Variable For Exit Depart Time (What Time They Left Exit Queue)
	float exitDepartTime;
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
	int nextEventType, numberOfCustomersDelayed, totalNumberOfCustomers, numberOfEvents,
		numberInEntranceQueue, numberInExitQueue, entranceServerStatus, leavingIndex,
		exitServerStatus, maxEntranceQueueSize, maxExitQueueSize, totalSearchTime, parked;
	float totalEntranceQueueDelayTime, totalExitQueueDelayTime, nextLeavingCar, timeSinceLastEvent,
		areaUnderEntranceQueue, areaUnderExitQueue, areaEntranceServerStatus, areaExitServerStatus;

	// Parking Lot Array. Initializing as a vector and will resize dynamically based on user input
	std::vector <float> parkingLotSpots;
	// Entrace And Exit Queue
	std::queue <Car> entranceQueue;
	std::queue <Car> exitQueue;
	// Car List
	std::vector <Car> arrayOfCars;

	// Time of Next Array Event That Will Tell Simulation When The Next Simulated Event Is.
	// Will Be A Constant Size 6 For Size of All Event Handling Functions for Simulation.  
	int timeOfNextEvent[NUMOFEVENTS];

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