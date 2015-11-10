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
			// Entrace Queue Size
			simulationInput >> entranceQueueSize;
			// Exit Queue Size 
			simulationInput >> exitQueueSize;
		}
		// Close File 
		simulationInput.close();
	}
	else
	{
		// Default Initialization Variables. Will be Read In Exactly This Order
		parkingSpots = 60;
		numberOfCars = 60;
		arrivalRate = 60;
		parkIntervalHigh = 120;
		parkIntervalLow = 60;
		exitGate = 60;
		entranceQueueSize = 500;
		exitQueueSize = 500;
	}

	// Statistical Counters.
	simulationTime = 0.0;
	nextEventType = 0;
	numberOfCustomersDelayed = 0;
	totalNumberOfCustomers = 0;
	numberInEntranceQueue = 0;
	numberInExitQueue = 0;
	entranceServerStatus = 0;
	exitServerStatus = 0;
	serviceTime = 0;
	exitServerStatus = IDLE;
	entranceServerStatus = IDLE;

	// Make Parking Spot Array The Correct Size
	parkingLotSpots.resize(parkingSpots);

	// Make Each Parking Spot Null or 0. We will add or replace the spot with zero after the spot is taken. 
	for (int i = 0; i < parkingSpots; i++)
		parkingLotSpots[i] = EMPTY;

	/* Initialize event list.  Since no customers are present, the departure
	(service completion) event is eliminated from consideration. */
	// First arrival
	timeOfNextEvent[1] = simulationTime + massDensityFunction();
	// Depart entrance queue
	timeOfNextEvent[2] = EMPTY;
	// Leave parking space
	timeOfNextEvent[3] = EMPTY;
	// Arrive at exit queue
	timeOfNextEvent[4] = EMPTY;
	timeOfNextEvent[5] = EMPTY;
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
	for (int i = 1; i < numberOfEvents; ++i)
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

	if (entranceServerStatus == BUSY) // Check to see whether server is busy.
	{
		// Server is busy, so increment number of customers in queue.
		++num_in_q;

		// Check to see whether an overflow condition exists.
		if (num_in_q > Q_LIMIT)
		{
			/* The queue has overflowed, so stop the simulation. */
			printf("\nOverflow of the array time_arrival at");
			printf(" time %f", sim_time);
			exit(2);
		}

		/* There is still room in the queue, so store the time of arrival of the
		arriving customer at the (new) end of time_arrival. */
		entranceQueue[num_in_q] = sim_time;
	}
	else // Server idle
	{
		/* Server is idle, so arriving customer has a delay of zero.  (The
		following two statements are for program clarity and do not affect
		the results of the simulation.) */
		delay = 0.0;
		total_of_delays += delay;

		// Increment the number of customers delayed, and make server busy.
		++num_custs_delayed;
		server_status = BUSY;

		// Schedule a departure (service completion).
		time_next_event[2] = sim_time + serviceTime;
	}

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
