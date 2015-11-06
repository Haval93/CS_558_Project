README

Parking lot simulation 
CS558 fall 2015

# Programmer: Ryan Stevens   RedID: 810318529
# Programmer: Haval Ahmed    RedID: 815013661
# Programmer: Sami Badra     RedID: 815012738
# Programmer: Geoff Crews    RedID: 816165149
# Programmer: Lauren Peppard RedID: 813614016

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

