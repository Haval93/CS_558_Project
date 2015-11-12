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

#include "Simulation.h"

// Mnemonic For Server Busy
#define BUSY 1  
// Mnemonic For Service IDLE
#define IDLE 0  
// Empty Spot
#define EMPTY 1.0e+30

// Global Car Counter
int carsCounter = 0;

// Constructor that Initializes all Values
Simulation_Information::Simulation_Information(int argc, char * argv[])
{
	// Check Argument Count 
	if (argc > 1)
	{
		// Create A File Instance
		std::fstream simulationInput;

		// Open File
		simulationInput.open(argv[1]);

		while (simulationInput.is_open() && simulationInput.good())
		{
			// Number of Parking Spots
			simulationInput >> parkingSpots;
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
		}
		// Close File 
		simulationInput.close();
	}
	else
	{
		// Default Initialization Variables.
		parkingSpots = 60;
		numberOfCars = 60;
		arrivalRate = 60;
		parkIntervalHigh = 120;
		parkIntervalLow = 60;
		exitGate = 60;
	}

	// Statistical Counters.
	simulationTime = 0.0;
	nextEventType = 0;
	numberOfCustomersDelayed = 0;
	totalNumberOfCustomers = numberOfCars;
	numberInEntranceQueue = 0;
	numberInExitQueue = 0;
	entranceServerStatus = 0;
	exitServerStatus = 0;
	exitServerStatus = IDLE;
	entranceServerStatus = IDLE;
	maxEntranceQueueSize = 0;
	maxExitQueueSize = 0;
	totalEntranceQueueDelayTime = 0.0;
	totalExitQueueDelayTime = 0.0;
	totalSearchTime = 0.0;
	parked = 0;
	nextLeavingCar = 1.0e+29;
	leavingIndex = 0;
	timeSinceLastEvent = 0.0;
	areaUnderEntranceQueue = 0.0;
	areaUnderExitQueue = 0.0;
	areaEntranceServerStatus = 0.0;
	areaExitServerStatus = 0.0;

	// Make Parking Spot Array The Correct Size
	parkingLotSpots.resize(parkingSpots);

	// Make Each Parking Spot Null or 0. We will add or replace the spot with zero after the spot is taken. 
	for (int i = 0; i < parkingSpots; i++)
		parkingLotSpots[i] = EMPTY;

	// Resize The Vector To The Number Of Cars in the simulation
	arrayOfCars.resize(numberOfCars);

	// Initialization the Cars into the car arrays
	for (int i = 0; i < numberOfCars; i++)
	{
		arrayOfCars[i] = Car();
		arrayOfCars[i].carNumber = i;
	}
	
	// Initialize event list. Since no customers are present, the departure (service completion) event is eliminated from consideration
	// First arrival
	timeOfNextEvent[1] = simulationTime + massDensityFunction();

	// Schedule First Event
	arrayOfCars[0].entranceArrivalTime = timeOfNextEvent[1];

	// Depart entrance queue
	timeOfNextEvent[2] = EMPTY;

	// Leave parking space
	timeOfNextEvent[3] = EMPTY;

	// Arrive at exit queue
	timeOfNextEvent[4] = EMPTY;

	// Leave Exit Queue
	timeOfNextEvent[5] = EMPTY;
}

// Car Constructor
Car::Car()
{
	int carNumber = 0;
	// Variable For Entrance Arrival Time (Enter Queue)
	float entranceArrivalTime = 0.0;
	// Variable For Entrance Depart Time (Exit Queue To Look For Parking)
	float entranceDepartTime = 0.0;
	// Increment Variable For Amount of Times Looking For Empty Parking Spot
	int numberOfTimesLooked = 0;
	// Variable For Parking Spot
	int parkingSpotLocation = 0;
	// Variable For Parking Time Length
	float parkingTimeLength = 0.0;
	// Variable For Exit Arrival Time (Enter Queue To Leave Parking Lot)
	float exitArrivalTime = 0.0;
	// Variable For Exit Depart Time (What Time They Left Exit Queue)
	float exitDepartTime = 0.0;
}

// Timing Method. Used To Determined Next Event
void Simulation_Information::timing(void)
{
	// MinTimeUntilNextEvent
	float minTimeNextEvent = 1.0e+29;

	// Set to 0 until an event is chosen
	nextEventType = 0;

	// Determine the event type of the next event to occur.
	// Iterate through all event types
	for (int i = 1; i < NUMOFEVENTS; ++i)
	{
		// Find smallest time
		if (timeOfNextEvent[i] < minTimeNextEvent) 
		{
			minTimeNextEvent = timeOfNextEvent[i];
			// Next event is event with smallest time
			nextEventType = i; 
			timeOfLastEvent = simulationTime;
			simulationTime = timeOfNextEvent[i];

		}
	}

	// Check to see whether the event list is empty.
	// If all times of next events are EMPTY no event is scheduled
	if (nextEventType == 0)
	{
		// The event list is empty, so stop the simulation.
		std::cout << "The event list is empty at time: " << simulationTime << std::endl;
		exit(1);
	}

	// The event list is not empty, so advance the simulation clock.
	simulationTime = minTimeNextEvent;
}


// Choose Next Event Type Function 
void Simulation_Information::chooseNextEvent(void)
{
	switch (nextEventType)
	{
	case 1:
		// Arrival at entrance queue
		entranceArrive();
		break;
	case 2:
		// Departure from entrance queue
		entranceDepart();
		break;
	case 3:
		// Leaving lot
		leaveSpot();
		break;
	case 4:
		// Arrival at exit queue
		exitArrive();
		break;
	case 5:
		// Departure from exit queue
		exitDepart();
		break;
	}
}


// Arrival Function For Entrance Gate
void Simulation_Information::entranceArrive(void)
{

	// Schedule next arrival.
	timeOfNextEvent[1] = simulationTime + massDensityFunction();

	// Need To Make Sure Ever Car have to make the next car entracearrivaltime to timeOfNextEvent[1]
	arrayOfCars[carsCounter].entranceArrivalTime = timeOfNextEvent[1];

	// Check to see whether server is busy.
	if (entranceServerStatus == BUSY) 
	{
		// If The Server is Busy Add The Car Into The Entrace Queue
		entranceQueue.push(arrayOfCars[carsCounter]);
	}
	else 
	{
		// Server is idle, so arriving customer has a delay of zero.  (The
		// following two statements are for program clarity and do not affect
		// the results of the simulation.) 
		totalEntranceQueueDelayTime = simulationTime - timeOfLastEvent;

		// Increment the number of customers delayed.
		numberOfCustomersDelayed++;

		// Set The Server To Busy
		entranceServerStatus = BUSY;

		// Schedule a departure (service completion).
		timeOfNextEvent[2] = simulationTime + exitGate;

		// Set the entrance depart time for the car object
		arrayOfCars[carsCounter].entranceDepartTime = timeOfNextEvent[2];

		// Put Car Into The Entrance Queue
		entranceQueue.push(arrayOfCars[carsCounter]);
	}

	// Increment Cars Counter
	carsCounter++;
}


// Depart Function For Entrance Gate
void Simulation_Information::entranceDepart(void)
{
	// Amount Of Search Time For Each Car
	float singleCarSearchTime = 0;

	// Car's Index In Parking Lot Structure Array
	int lotIndex = 0;

	// Check to see whether the queue is empty.
	if (entranceQueue.size() == 0)
	{
		// The queue is empty so make the server idle and eliminate the
		// departure (service completion) event from consideration.
		entranceServerStatus = IDLE;
		timeOfNextEvent[2] = EMPTY;
	}
	else
	{
		// Need To Access The Next Car In Line
		Car nextCarInLine = entranceQueue.front();

		// Temp Variable 
		int tempCarNumber = nextCarInLine.carNumber;

		// Compute the delay of the customer who is beginning service and update the total delay accumulator 
		totalEntranceQueueDelayTime = simulationTime - nextCarInLine.entranceArrivalTime;

		// Increment the number of customers delayed
		numberOfCustomersDelayed++;

		// Schedule departure
		timeOfNextEvent[2] = simulationTime + exitGate;

		// Schedule Depart Time For Current Time
		arrayOfCars[tempCarNumber].entranceDepartTime = simulationTime;

		// Pop The Car Off The Entrance Queue
		entranceQueue.pop();

		// Enter lot and search for spot
		// Choose random spot and check to see if it's empty
		do
		{
			singleCarSearchTime += 30.0f;
			totalSearchTime += 30.0f;
			lotIndex = static_cast <int>((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (parkingSpots - 1));
		} while (parkingLotSpots[lotIndex] = EMPTY); // Try again if spot was taken

		
		// Assign Parking Spot To Car
		arrayOfCars[tempCarNumber].parkingSpotLocation = lotIndex;


	}

	// Enter lot and search for spot
	// Choose random spot and check to see if it's empty
	/*do
	{
		singleCarSearchTime += 30.0f;
		totalSearchTime += 30.0f;
		lotIndex = static_cast <int>((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (parkingSpots - 1));
	} while (parkingLotSpots[lotIndex] = EMPTY); // Try again if spot was taken*/

	// Increment number of cars parked
	parked++; 

	// Store departure time in spot
	int parkTime = ParkingTime(parkIntervalLow, parkIntervalHigh);
	//arrayOfCars[temp]
	parkingLotSpots[lotIndex] = simulationTime + singleCarSearchTime + parkTime;

	// Print departure time of spot
	//printf("Spot %d taken. Departure time: %f seconds. Search time: %d\n", lotIndex, lot[lotIndex], singleCarSearchTime);
	//cout << "Spot " << left << setw(2) << lotIndex << " taken.   Departure time: " << left << setw(8) << lot[lotIndex] << " seconds.   Search time: " << singleCarSearchTime << endl;
	//cout << "Spot number taken: " << left << setw(2) << lotIndex << "   Departure time in seconds: " << left << setw(8) << lot[lotIndex] << "   Search time: " << singleCarSearchTime << endl;

	// Determine the time of the next car to leave a spot
	for (int i = 0; i <= parkingSpots - 1; i++)
	{
		if (parkingLotSpots[i] < nextLeavingCar)
		{
			nextLeavingCar = parkingLotSpots[i];
			leavingIndex = i;
			timeOfNextEvent[3] = parkingLotSpots[i];
		}
	}
	
}

// Function to handle car leaving lot event
void Simulation_Information::leaveSpot(void)
{ 
	int carspotLeaving = -1;
	int arrayEnd = arrayOfCars.size() - 1;
	while (carspotLeaving == -1)
	{
		if (arrayOfCars[arrayEnd].parkingSpotLocation == leavingIndex)
			carspotLeaving = arrayOfCars[arrayEnd].carNumber;
		arrayEnd--;
	}
	
	// Remove car from spot
	parkingLotSpots[leavingIndex] = EMPTY; 

	// Next Leaving Car Variable 
	nextLeavingCar = EMPTY;

	// Decrement Number of Cars Parked
	parked--;

	// Find car that is leaving next
	for (int i = 0; i <= parkingSpots - 1; ++i)
	{
		if (parkingLotSpots[i] <= nextLeavingCar)
		{
			nextLeavingCar = parkingLotSpots[i];
			leavingIndex = i;
			timeOfNextEvent[3] = parkingLotSpots[i];
		}
	}

	// Car arrives in exit queue
	exitQueueHelper(carspotLeaving);
}

//push car on the list
void Simulation_Information::exitQueueHelper(int carNumber)
{
	arrayOfCars[carNumber].exitArrivalTime = simulationTime;
	exitQueue.push(arrayOfCars[carNumber]);
	
}

// Arrival Function For Exit Gate
void Simulation_Information::exitArrive()
{

		/* Server is idle, so arriving customer has a delay of zero.  (The
		following two statements are for program clarity and do not affect
		the results of the simulation.) */

		
		totalExitQueueDelayTime += simulationTime - timeOfLastEvent;

		// Increment the number of customers delayed, and make server busy.
		if (exitQueue.size() != 0)
			exitServerStatus = BUSY;

		// Schedule a departure (service completion).
		timeOfNextEvent[5] = simulationTime + exitGate;
}


// Depart Function For Exit Gate
void Simulation_Information::exitDepart(void)
{

	// Check to see whether the queue is empty.
	if (exitQueue.size() == 0)
	{
		/* The queue is empty so make the server idle and eliminate the
		departure (service completion) event from consideration. */

		exitServerStatus = IDLE;
		timeOfNextEvent[5] = EMPTY;
	}

	else
	{

		// Compute the delay of the customer who is beginning service and update
		// the total delay accumulator.

		// totalExitQueueDelayTime = simulationTime - exitQueue.car.exitarrivalTime;
		

		// Increment the number of customers delayed, and schedule departure.
		// nextEventType[5] = simulationTime + exitGate;
		timeOfNextEvent[5] = simulationTime + exitGate;

		Car carObject = exitQueue.front();
		int temp = carObject.carNumber;
		arrayOfCars[temp].exitDepartTime = simulationTime;

		exitQueue.pop();
	}
}

// Update Average Time Stats
void Simulation_Information::updateAverageTimeStats(void)
{
	// Compute time since last event, and update last-event-time marker. 
	timeSinceLastEvent = simulationTime - timeOfLastEvent;
	timeOfLastEvent = simulationTime;

	// Update area under number-in-queue function.
	areaUnderEntranceQueue += entranceQueue.size() * timeSinceLastEvent;
	areaUnderExitQueue += exitQueue.size() * timeSinceLastEvent;

	// Update area under server-busy indicator function.
	areaEntranceServerStatus += entranceServerStatus * timeSinceLastEvent;
	areaExitServerStatus += exitServerStatus * timeSinceLastEvent;
}


// Report Statisical Data
void Simulation_Information::report(void)
{
	for (int i = 0; i < arrayOfCars.size(); i++)
	{
		std::cout << "car Number " << arrayOfCars[i].carNumber;
		std::cout << "  car EntranceTime " << arrayOfCars[i].entranceArrivalTime;
		std::cout << "  car EntranceLeave Time " << arrayOfCars[i].entranceDepartTime;
		std::cout << "  car parkingSpot " << arrayOfCars[i].parkingSpotLocation;
		//std::cout << "  car park time " << arrayOfCars[i].parkingTimeLength;
		std::cout << "  car exit arrival " << arrayOfCars[i].exitArrivalTime;
		std::cout << "  car exit depart " << arrayOfCars[i].exitDepartTime << std::endl;

	}
}


// Mass Density Function 
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

// Get a random parking number between a range
float ParkingTime(float parkIntervalLow, float parkIntervalHigh)
{
	//25 + (std::rand() % (63 - 25 + 1))
	float parkTime = 0;
	parkTime = parkIntervalLow - (std::rand() % (static_cast<int>(parkIntervalHigh) - static_cast<int>(parkIntervalLow) + 1));
	return parkTime;
}
