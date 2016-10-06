#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(void)
{
	char directoryString [20];
	int myPid = getpid();
	sprintf(directoryString, "/steinerj.room.%i", myPid); 
	mkdir(directoryString, S_IRWXU | S_IRWXG | S_IROTH);	
	
	srand(time(NULL));

	char *connectString = "CONNECTION";

	const char *roomFiles[7]; //room file names
	roomFiles[0] = "roomOne.txt";
	roomFiles[1] = "roomTwo.txt";
	roomFiles[2] = "roomThree.txt";
	roomFiles[3] = "roomFour.txt";
	roomFiles[4] = "roomFive.txt";
	roomFiles[5] = "roomSix.txt";
	roomFiles[6] = "roomSeven.txt";

	const char *roomNames[10]; //possible room names
	roomNames[0] = "fffff";
	roomNames[1] = "xxxxx";
	roomNames[2] = "yyyyy";
	roomNames[3] = "zzzzz";
	roomNames[4] = "uuuuu";
	roomNames[5] = "wwwww";
	roomNames[6] = "ppppp";
	roomNames[7] = "vvvvv";
	roomNames[8] = "hhhhh";
	roomNames[9] = "ggggg";

	char *roomString = "ROOM NAME: ";
	const char *conString [6]; //string for printing connections
	conString[0] = "CONNECTION 1: ";
	conString[1] = "CONNECTION 2: ";
	conString[2] = "CONNECTION 3: ";
	conString[3] = "CONNECTION 4: ";
	conString[4] = "CONNECTION 5: ";
	conString[5] = "CONNECTION 6: ";

	int descriptors [7]; //open all files and put descriptors in array
	descriptors[0] = open(roomFiles[0], O_WRONLY | O_CREAT, 0644); 
	descriptors[1] = open(roomFiles[1], O_WRONLY | O_CREAT, 0644);
	descriptors[2] = open(roomFiles[2], O_WRONLY | O_CREAT, 0644);
	descriptors[3] = open(roomFiles[3], O_WRONLY | O_CREAT, 0644);
	descriptors[4] = open(roomFiles[4], O_WRONLY | O_CREAT, 0644);
	descriptors[5] = open(roomFiles[5], O_WRONLY | O_CREAT, 0644);
	descriptors[6] = open(roomFiles[6], O_WRONLY | O_CREAT, 0644);

	const char *possibleConnString [10]; //not sure why I have this again
	possibleConnString[0] = "fffff";
	possibleConnString[1] = "xxxxx";
	possibleConnString[2] = "yyyyy";
	possibleConnString[3] = "zzzzz";
	possibleConnString[4] = "uuuuu";
	possibleConnString[5] = "wwwww";
	possibleConnString[6] = "ppppp";
	possibleConnString[7] = "vvvvv";
	possibleConnString[8] = "hhhhh";
	possibleConnString[9] = "ggggg";


	int roomI;
	for (roomI = 0; roomI < 7; roomI++)
		{ 
		write(descriptors[roomI], roomString , 11);
		}

	//name rooms

	int nameAssignments[7] = {12, 12, 12, 12, 12, 12, 12}; //fill list with out of range values;
	
	int namesI;
	int namesAssigned = 0;
	int currentNamee = 0;
	int nameTaken;
	int randomName;
	while (namesAssigned < 7)
	{
	 	int limit = 9; // http://stackoverflow.com/questions/2999075/generate-a-random-number-within-range/2999130#2999130
		int divisor = RAND_MAX/(limit+1);

		do
		{
		randomName = rand() / divisor;	
		} while (randomName > limit);

		nameTaken = 0;
		for(namesI = 0; namesI < 7; namesI++)
		{
			if (randomName == nameAssignments[namesI])
			{
				nameTaken = 1; // name is taken
			}
		}	
		if (nameTaken == 0) //if name number isn't taken assign it to current namee, inc currentNamee index and namesAssigned 
		{
			nameAssignments[currentNamee] = randomName;
			currentNamee++;
			namesAssigned++;  
		}

	}
	int writeNameI;
	for (writeNameI = 0; writeNameI < 7; writeNameI++) //write name string
	{
		write(descriptors[writeNameI], roomNames[writeNameI], 5);
		write(descriptors[writeNameI], "\n", 1);

	}	
 	

//write empty connections

	int connections [7][6]; //array representing each room and each possible number of connections
	int checkConns2;
	int totalConnections;
	int adjustedConns;
	do 
	{
		for (checkConns2 = 0; checkConns2 < 7; checkConns2++) //initialize all values to an invalid value (99)
		{
			int checkConnsI;
			for (checkConnsI = 0; checkConnsI < 6; checkConnsI++)
			{
				connections[checkConns2][checkConnsI] = 99;  
			}
		}

		totalConnections = 0; // tracks total number of connections so we can make sure it's even 
		int connectionsI; //loop counter, counts each room
		for (connectionsI = 0; connectionsI < 7; connectionsI++) //for each room 
		{
			int limit = 6; //generate the number of connections
			int divisor = RAND_MAX/(limit+1);
			int numConnects; // random number of connections

			do{
			numConnects = rand() / divisor;
			numConnects = numConnects + 3;
			} while (numConnects > limit);

			totalConnections = totalConnections + numConnects; // accumulate total number of connections 

			int connSlotsI;
			for (connSlotsI = 0; connSlotsI < numConnects; connSlotsI++) //start at first slot and write an open until random number reached
			{
			connections[connectionsI][connSlotsI] = 11; // put a 1 to represent an open connection 
			}
		
			}
	
	} while (totalConnections % 14 != 0);

	//printf("total connections is %i \n", totalConnections); 
	
//assign connections
	int assignConnI;   // current room that we are setting connections for
	int potentialConn; //potential room to connect to 
	
	for (assignConnI = 0; assignConnI < 7; assignConnI++) // for each room	
	{

		int currentConnI = 0;
		int connectionsEvaluated = 0; 
		while (connectionsEvaluated < 6) // for each of the current rooms connections
		{

		//	printf("connections Evaluated is %i and we're evaluating room %i \n", connectionsEvaluated, assignConnI);
			if (connections[assignConnI][currentConnI] == 11) //if there is an open connection generate a random connection
			{
				//printf("room %i connection %i is open see this: %i \n", assignConnI, currentConnI, connections[assignConnI][currentConnI]);
				int connectionMade = 0;
				int potentialConn = 0;
				int connAttempts = 0;
				while (connectionMade == 0) //the current connection is open (i.e. is 1) so keep going until we connect it
				{
					if(connAttempts > 99) //give up if it is stuck in an infinite loop
					{
						connectionMade++;
						connectionsEvaluated++;
						currentConnI++;

					}

					int doublesBool = 0; //boolean to check for double connections between same rooms
					int limit = 6; //generate a potential room to connect to
					int divisor = RAND_MAX/(limit+1);

					do
					{
					potentialConn = rand() / divisor;
					} while (potentialConn > limit);


					int doubleCheckI;
					for (doubleCheckI = 0; doubleCheckI < 6; doubleCheckI++)
					{
						if (potentialConn == connections[assignConnI][doubleCheckI])
						{
							doublesBool = 1;
						}
					}
					if (doublesBool == 0) //if there isn't already a connection to that room 
					{	
						int testConnI; // each of the potential connection's connections are tested here
						for (testConnI = 0; testConnI < 6; testConnI++)
						{
							if (connectionMade == 0) //makes sure we only make one connection to the current random connection
							{
												
							if (connections[potentialConn][testConnI] ==11) //there is an open connection
							{
								if (assignConnI != potentialConn) //makes sure it doesn't connect to iteslf
								{
									connections[potentialConn][testConnI] = assignConnI; //	make the connection on the potential connection side 	
									connections[assignConnI][currentConnI] = potentialConn; // make the connection on the current examinee's side
									connectionMade++;
									connectionsEvaluated++;
									currentConnI++;
								}
							}
							}
						}
					}  
				connAttempts++;
				}
			}
			else //connection is full or doesn't need to be filled  
			{
				connectionsEvaluated++;
				currentConnI++;
			}
		}
	}

//wrire connections
	int printCurrI; //current room
	int printConnI; //current connection to print

	for (printCurrI = 0; printCurrI < 7; printCurrI++)
	{
		for (printConnI = 0; printConnI < 6; printConnI++)
		{
			if (connections[printCurrI][printConnI] != 99) //99 is no connection, shouldn't be any 11's as they are open connections
			{ 	
				if (connections[printCurrI][printConnI] != 11)
				{ 
					write(descriptors[printCurrI], conString[printConnI], 14);  
					write(descriptors[printCurrI], roomNames[connections[printCurrI][printConnI]], 5); //write to the current room, the name of the current connection
					write(descriptors[printCurrI], "\n", 1);  
				}
			}
		}

	} 	

//assign room types
	const char *startRoom = "ROOM TYPE: START_ROOM";
	const char *midRoom = "ROOM TYPE: MID_ROOM";
	const char *endRoom = "ROOM TYPE: END_ROOM";
	int typeAssignments[7] = {99, 99, 99, 99, 99, 99, 99}; //fill list with out of range values;

	int typesAssigned = 0;
	int startAssigned = 0;
	int endAssigned = 0;


	while (typesAssigned < 7) //until a type has been assigned to all rooms
	{
		int limit = 6;
		int divisor = RAND_MAX/(limit+1);
		int typeRandom; //generate a random number  
		do{typeRandom= rand() / divisor;} while (typeRandom > limit);

		if (startAssigned == 0) //should happen first time through when all rooms are available
		{
			typeAssignments[typeRandom] = 1; // 1 represents a start room
			write(descriptors[typeRandom], startRoom, 21);
			write(descriptors[typeRandom], "\n", 1);
			startAssigned++; //start room has been assigned
			typesAssigned++; //another room has been assigned
		}

		else if (endAssigned == 0)
		{
			if (typeAssignments[typeRandom] == 99) // if the random room is empty 
			{
				typeAssignments[typeRandom] = 3; // 3 represents end room; 
				write(descriptors[typeRandom], endRoom, 19);
				write(descriptors[typeRandom], "\n", 1);
				endAssigned++; //end room has been assigned
				typesAssigned++; //another room has been assigned
			}
		}

		else
		{
			if (typeAssignments[typeRandom] == 99) // if the random room is empty 
			{
				typeAssignments[typeRandom] = 2; //two represents mid room
				write(descriptors[typeRandom], midRoom, 19);
				write(descriptors[typeRandom], "\n", 1);
				typesAssigned++; //another room has been assigned
			}
		}
	}

	int closeI;
	for (closeI = 0; closeI < 7; closeI++) // close all the open files
	{
		close (descriptors[closeI]);
	}
	
	int gameStartIndex;
	int gameEndIndex; 
	int findStartI;   	
	for (findStartI = 0; findStartI < 7; findStartI++) //find start and end room  
	{
		FILE *file = fopen(roomFiles[findStartI], "r");
		char currLine [22];
		while (fgets(currLine, 22, file) != NULL) // read lines looking for the end room or start room string
		{
			int compareEnd = strncmp(currLine, endRoom, 19); 
			int compareStart = strncmp(currLine, startRoom, 22);

			if (compareStart == 0) // if match, set start to current index 
			{
				gameStartIndex = findStartI;
			}

			if (compareEnd == 0)

			{
				gameEndIndex = findStartI;
			}
		} 
		fclose(file);
	}

		int currentRoomIndex = gameStartIndex;//set room to start room found above
		int playerPath [20] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}; //set user's path to invalid data
		int playerSteps = 0; 
		while (currentRoomIndex != gameEndIndex) //until the current room is the end room...
		{	
			int validPaths[6] = {99, 99, 99, 99, 99, 99}; //after reading file, stores valid selections here
			FILE *file = fopen(roomFiles[currentRoomIndex], "r");
			char currLine [22];
			int availableSelections = 0;  			
			while (fgets(currLine, 22, file) != NULL) //get lines of curren room's file
			{
				char part1 [10]; //split the current line in 3 parts
				char part2 [2];
				char part3 [5];
				sscanf (currLine, "%s %s %s", part1, part2, part3);

				
				int connectInt = strncmp(connectString, part1, 10); //check if this line is a connection
				if (connectInt == 0)				   // if so see what room it connects to	
				{
						
					int compare0 =  strncmp(part3, possibleConnString[0], 19); //compare the final part of the string to a room name

					if (compare0 == 0) //if matches a room name 
					{
					validPaths[availableSelections] = 0; //add the room to the available selections
					availableSelections++;               //increment the number of available selections
					}

					int compare1 =  strncmp(part3, possibleConnString[1], 19);
					if (compare1 == 0)
	
					{
					validPaths[availableSelections] = 1; 
					availableSelections++;
					}   
   					int compare2 =  strncmp(part3, possibleConnString[2], 19); 

					if (compare2 == 0)

					{	
					validPaths[availableSelections] = 2; 
					availableSelections++;
					}
   
					int compare3 =  strncmp(part3, possibleConnString[3], 19); 

					if (compare3 == 0)

					{
					validPaths[availableSelections] = 3; 
					availableSelections++;
		
					}   

					int compare4 =  strncmp(part3, possibleConnString[4], 19); 

					if (compare4 == 0)

					{
					validPaths[availableSelections] = 4; 
					availableSelections++;
		
					}
   
					int compare5 =  strncmp(part3, possibleConnString[5], 19); 

					if (compare5 == 0)

					{	
					validPaths[availableSelections] = 5; 
					availableSelections++;
		
					}
   
					int compare6 =  strncmp(part3, possibleConnString[6], 19); 

					if (compare6 == 0)

					{
					validPaths[availableSelections] = 6; 
					availableSelections++;
		
					}
   
					int compare7 =  strncmp(part3, possibleConnString[7], 19); 
			
					if (compare7 == 0)

					{
					validPaths[availableSelections] = 7; 
					availableSelections++;
		
					}
   
					int compare8 =  strncmp(part3, possibleConnString[8], 19); 

					if (compare8 == 0)

					{
					validPaths[availableSelections] = 8; 
					availableSelections++;
		
					}   
	
					int compare9 =  strncmp(part3, possibleConnString[9], 19); 
	
					if (compare9 == 0)

					{	
					validPaths[availableSelections] = 9; 
					availableSelections++;
					} 
				}  

			}

			char inputString [6]; // buffer for input from user
			printf("CURRENT LOCATION: %s \n", roomNames[currentRoomIndex]);
			printf("POSSIBLE CONNECTIONS: ");
			int possibleI;
			for (possibleI = 0; possibleI < availableSelections; possibleI++) //print possible selections 
			{
				if (validPaths[possibleI] != 99)
				{
					printf("%s ", roomNames[validPaths[possibleI]]); 
				}
			}
			
			printf("\n");
			printf("WHERE TO? "); 
			fgets (inputString, 6, stdin); //get user input
			int userChoiceI;
			int goodInputBool = 0;
			for (userChoiceI = 0; userChoiceI < 7; userChoiceI++)
			{
				int userMatch = strncmp (inputString, roomNames[userChoiceI], 6); //compare user input to available selections
				if (userMatch == 0) //if user made a valid choice
				{
					currentRoomIndex = userChoiceI; //update current room
					playerPath[playerSteps] = userChoiceI; // add room to path
					playerSteps++; //increment steps
					goodInputBool = 1; //boolean user input was good set to true
				}

			}

			if (goodInputBool != 1) //if invalid user input
			{
				printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");  
			}

		}

		printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS! \n");
		printf("YOU TOOK %i STEPS. YOUR PATH TO VICTORY	WAS:\n", playerSteps);
		int printSteps = 0;
		while (playerPath[printSteps] != 99) //print user's path 
		{
			printf("%s \n", roomNames[playerPath[printSteps]]);
			printSteps++;
		} 
}



































