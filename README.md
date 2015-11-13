README

Parking lot simulation 
CS558 fall 2015

# Programmer: Ryan Stevens   RedID: 810318529
# Programmer: Haval Ahmed    RedID: 815013661
# Programmer: Lauren Peppard RedID: 813614016
# Programmer: Geoff Crews    RedID: 816165149
# Programmer: Sami Badra     RedID: 815012738

File Manifest:

.gitattributes
.gitgnore
Parking_Lot.sln
VisualStudio.gitgnore
file Parking_Lot
	Parking_Lot.vcxproj
	Parking_Lot.vcxproj filters
	Simulation.h
	Simulation.cpp
	main.cpp

The source code can be found under Simulation.h, Simulation.cpp, and main.cpp. Simulation.cpp is used to generate random varibales with the mass density function of 24*3(1-x). main.cpp calls the funtions and houses the function for the program. Main has a while loop which calls the initialize(), timing(); entranceArrive(), entranceDepart(), leaveSpot(), exitArive(), exitDepart(), and report().

Compile Instructions:
The user needs to run this program on visual studios 2015 which is free to download. the user will unzup the file and double click the parkling_Lot.sln. this will open up visual studios 2015. The user will then have build the program in visual studios before they can run it. 

If the user wishes to compile it using visual studios 2013 they will nees to right click on the prject, go to Properties. Under Configuration Properties, go to general. Change your platform toolset to one of the availiabe ones. 

Operating Instructions:
Once the program is built then the user runs it in visual studios. 


Design Choices: 
This simulation is geared towards a pay parking lot. If the lot is full cars will be turned away from the lot. If this is a parking lot for like a apartment complex then it wold be okay to not turn cars away. we used Simulation modeling and analysis 5th edition by Averill M. Law as a refference. We used the single server program ad updated it to fit our specific needs. For the demo we are not allowing the user configuarable variables since there has not been enough testing on it.

Extra Features:
So far we have two stopping condition. One is that if the waiting queue is too long the program will shut down. The other is when the program finishes running it will shut down. We plan on having other shut down methods when we submit the final product. There will be more extra features in the final product. 

Known bugs:
The timing function seems to be off. Our functions seem to be called over and over when they should not be. More tests have to be done to pinpoit the bug. We believe we found where the bug lies and are correcting it although since not evough tests have been done to 100 % verify it is gone it could still happen. There is a bug from reading in from a file for the user configurable variables. Because of this we are taking it out for the demo. 

Lessons Learned:
One of the first lessons is that more people working on something does not mean it will be easier. Some of this comes from the different levels of programming for each person and the languages each person uses. Some people were more fluent in java and wanted to use that while some didnt know java and wanted to use C++. The end result was we started in java for prototyping and the code that worked was then translated into C++. This was highly ineffecient and wasted time but allowed for each of us to put in work. From working in groups in other classes we learned how important version control is. Because of this we set up a private repo on bitbucket so the team can use git and have access to all the code and see what each member is doing. This would also help with documentation. Unfortunately three of the group members knew how to use git and have used it before so time was spent teaching about git to the other members of the group. This made it hard for the other members to feel involved since they had issues getting ove the git hurdle so they would not pull or push the code. Communication through git also became an issue because sometimes commit messages were very vague and simple. One example of this is a commit message simply stating "added more code". Due to these issues pair programming was put in place. The group would have to get together and do paired programming. This was beneficial to the group but it also restricted how much time each member would put into the program. Since we are presenting a demo we had to put git aside for now but after the demo tese issues will be alleviated. It should be that each member can work on the code whenever and push the latest code to the repository. 

*****************************************************************************************************************************
Program Update 1.2

File Manifest: 
The file mifest is the same except that code has been moved around.

Compile Instructions:
are the same as above

Operating Instructions:
If the user wants to run it in visual studios they can just build then run the program. If the user wants to change the vairables in the text document and run the program with those numbers instead of the default ones they can. this is done by
opening up the simulationValues.txt file and changing those values. The values are
1. the number of pakring spots in the system
2. the number of cars in the system
3. rate the entrance gate will let people in the parking lot (in seconds)
4. the high value time spent in the parking lot (in seconds)
5. the low value for time in the parking lot (in seconds)
6. the rate at which a car will be allowed to exit the parking lot (in seconds)

the user then opens visual studios and goes to project, parkinglot properties. Once in there you go to debugging and in comman arguments you click the drop down and click edit. From there you will have to copy the file path of the txt file and paste it in there. 


Design Choices: 
The program has been updated. The code has been refactored completely and has been moved for easier readability. New variables that define what they are used for has been made and redundant code and variables have been taken out. 
we decided that we will stop the simulation after so many people get to the entrance service the simulation will end. This though will make it so the last few people in the parking lot will not have the correct numbers for when they exit the system. We thought about changing it so that we will end the program after the number of customers exit the system but after much debate the team decided that it we are ultimatly after the entrance queue instead of the exit queue. 

The program now is able to read in from a file. the user can change the vairbales in the file and run the program with those insteaad. 

Also we make car objects and output every car's information. This includes what time they get into the entrance queue, time they were serviced, the parking spot number for the car, the time they stayed parked, the time they enter the exit queue, and the time they are serviced from the exit queue and leave the system. 

now the entrace and exit queues will no longer have a size limit. So an infinant number of cars can be waiting to get in the parking lot. This was changed due to in real world conditions parking lots can have long wiat times (especially during the christmas season). We also now no longer turn cars away from the parking lot. This also is because most parking lots, especially unpaid parking lots, do not turn people away. 

Extra Features: 
	The main extra feature we have is the car objects. Because we make car objects we can now print out every cars information so if the user wants to focus on something that we are not they are able to do that. 
	We also made it so that cars farther away from the exit gate will take longer to get to the exit gate. So cars who are close will take seconds to get to the exit and it grows the farther away you go from the exit. So each spot takes different times to get to the exit. 
	We have data being printed after every 10 cars have left the system we are outputting statistical data. That way if the user wants to look at the data real time they can. 
	We also set it up so that if the user wants to pause the simulation they can click the left mouse button. to resume the simulation they can press the space bar. For this extra functionality the program has to be run on a windows. We tired it on windows 7 and it didnt work and we also did it on windows 10 and it worked. 
	When the program is run it will output all the data in a cvs file for the convience of the user to plot, compare, and store the data. To find the cvs file the user will run the program and then in his windows explorer go to the folder that has that the program was saved to. The user will then go into the Parking_Lot and double click it. the .csv file is called CarData.csv. This file will be over written everytime the user runs the program. If the user wants to save their data they can move the file to a different location so it will not be overwritten. We added another file called Simulation stats that focuses on the service time, the entrance queue size, the exit queue size, the area under the entrance queue and the area under the exit queue.
	

Known bugs: 
	It can be a bug or design choice but we decided it is better to end the system after certain number of people go through the entrance service so people are still in the system while the simulation ends. Some of our extra features does not work on all computers. 
	

Lessons Learned:
We learned how important it is to make car objects in terms of debugging. We also learned that most of the old code was redundant and should be deleted. We found better ways to do program the simulation making it sleaker and more efficient code. Most of the lessons learned were personal lessons in working in a big group. This program would have been better if the group was 2-3 people. Having a larger group allowed for some people to not code as much as others. Also still some people would not learn git to push and pull the code from the repository and instead emailing the code. This makes it harder to track the changes. This would not be as much of an issue if they could show up for pair programming. Although some group members would not show up for it. If we were given the chance to redo the program we would choose a team of two or three instead. 
