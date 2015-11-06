/*
Simulation Header File
Members:
Haval Ahmed
Ryan Stevens
Lauren Peppard
Sami Badra
Geoff Crews
*/

#ifndef Simulation
#define Simulation

// First Queue Limit 
// #define Q_LIMIT 500  
// Second Queue Limit
// #define Q_LIMIT2 500
// Mnemonic For Server Busy
#define BUSY 1  
// Mnemonic For Service IDLE
#define IDLE 0  
// Empty Spot
#define EMPTY 1.0e+30

// Simulation Info Structure
class Simulation
{
public:
	// Default Initialize Method. Initializes All Simulation Variables
	void Simulation initialize(int argumentCount, char * fileNames[]);
	// Timing Method. Used To Determined Next Event
	void Simulation timing(void);
	// Arrival Function For Entrance Gate
	void Simulation entranceArrive(void);
	// Depart Function For Entrance Gate
	void Simulation entranceDepart(void);
	// Arrival Function For Exit Gate
	void Simulation exitArrive(void);
	// Depart Function For Exit Gate
	void Simulation exitDepart(void);
	// Function to handle car leaving lot event
	void Simulation leaveSpot(void);
	// Update Average Time Stats
	void Simulation updateAverageTimeStats(void);
	// Report Statisical Data
	void Simulation report(void);
};

// Structure For All Automobile Information
class Car
{
public:
	// Variable For Car Number
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

// Mass Density Function 
float massDensityFunction();

#endif