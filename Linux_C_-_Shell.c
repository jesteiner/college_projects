#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> //for close on exec
#include <signal.h>

int main ()
{
	char promptString[] = ":"; //shell prompt
	char inRedirect[] = "<"; // input redirection string
	char outRedirect[] = ">"; //outpur redirection string
	char exitString[] = "exit"; //exit command string
	char cdString[] = "cd"; //change directory command string
	char backgroundString [] = "&"; //indicates process should be run in background
	char statusString[] = "status"; //status command string
	char commentString[] = "#"; //indicates line is a comment
	char emptyString[] = ""; //indicates line is blank
	char *charPoint; //for tokenized arguments
	int inRedirectBool = 0; //boolean if input redirection symbol was in args
	int outRedirectBool = 0; //boolean if output redirection symbol was in args  
	int backgroundBool = 0; //boolean if background symbol was in args
	int lineType = 0; //used for switch block
	int numArguments = 0; //keeps track of number of arguments; 
	int processesCreated = 0; //tracks number of processes created to avoid problems
	int lastStatus = 1; //stores the exit status of last process to exit

	struct sigaction defaultAct; //setup to ignore signals for main shell 
	defaultAct.sa_flags = 0;
	defaultAct.sa_handler = SIG_IGN;
	sigfillset(&(defaultAct.sa_mask));


	
	while(1)
	{
		sigaction(SIGTERM, &defaultAct, NULL); //ignore termination for main shell
		numArguments = 0; //tracks the numbers of arguments in command line
		char **arguments = malloc(512 * sizeof(char*)); //array of strings for arguments 
		char **lineArguments = malloc(512 * sizeof(char*)); //args to be passed to bash
		char *commandString = malloc(sizeof(char) * 2048); // string for a line of commands
		fputs(promptString, stdout); //command prompt
		fflush(stdin);
		fgets (commandString, 2048, stdin); //get the line of arguments
		charPoint = strtok(commandString, " ");
		int argIndex = 0;
		while (charPoint != NULL)
			{
			arguments[argIndex] = charPoint; //put charPoint into arguments array
			charPoint = strtok (NULL, " ");
			argIndex++;
			numArguments++;
			}

			arguments[argIndex] = NULL; //last argument should be null. might already be? 
	
		arguments[numArguments - 1] = strsep(&arguments[numArguments - 1], "\n"); //strip newline character from last arg.

		
		if (strcmp(arguments[0], emptyString) == 0) //line is empty
		{lineType = 1;}

		else if (strcmp(arguments[0], commentString) == 0) //line is comment
		{lineType = 2;}

		else if (strcmp(arguments[0], exitString) == 0) //line calls exit command
		{lineType = 3;}

		else if (strcmp(arguments[0], cdString) == 0) //line calls cd command
		{lineType = 4;}
	
		else if (strcmp(arguments[0], statusString) == 0) // command is "status"
		{lineType = 5;}
	
		else //if first argument isn't built in, comment, or blank it must be bash  
		{lineType = 6;}	

		switch (lineType) //switch based on line type determined above
		{
			case 1: //blank line

				break;

			case 2: //comment
				break;

			case 3: //exit built in command

				printf("exiting \n");
				fflush(stdout);
				return 0; 
				break;

			case 4: // cd built in command

				if (arguments[1] != NULL)
				{chdir(arguments[1]);}

				else // if no arguments cd goes to home directory
				{chdir(getenv("HOME"));}
				break;

			case 5: //status built in command

				printf("status is %i\n", lastStatus); //report status of last process to exit 
				fflush(stdout); //testing
				break;
		
			case 6: // bash command
				inRedirectBool = 0;
				outRedirectBool = 0;
				backgroundBool = 0;
				int regularArgs = 0; // normal command line args, not <, filenames, etc
				int execStatus = -99;
				int fileFailure = 0;
				argIndex = 1;
				char inFileString[128];
				char outFileString[128];

				while (arguments[argIndex] != NULL) //go through array of arguments one at a time
				{
					if (strcmp(arguments[argIndex], inRedirect) == 0) //check if input redirect present
					{
						inRedirectBool = 1;
						strcpy(inFileString, arguments[argIndex + 1]);
						arguments[argIndex] = NULL;
						arguments[argIndex + 1] = NULL;
					}

					else if (strcmp(arguments[argIndex], outRedirect) == 0) //check for out redirect
					{
						outRedirectBool = 1;
						strcpy(outFileString, arguments[argIndex + 1]); //copy file name for redirection
						arguments[argIndex] = NULL; // redirection symbol shouldn't be passed to exec
						arguments[argIndex + 1] = NULL; // file name shouldn't be passed to exec
					}

					else if (strcmp(arguments[argIndex], backgroundString) == 0) //check for bg symbol
					{
						backgroundBool = 1;
						arguments[argIndex] = NULL; // remove ampersand from list of arguments
					} 
										
					argIndex = argIndex + 1;
				}

				//setup to exec process
					
				pid_t cpid = fork(); // fork new process
				if (cpid == 0) //if child process
				{
					if (inRedirectBool == 1) //setup input file if necessary
					{
						int inFD = open(inFileString, O_RDONLY); //open file for input
						if (inFD == -1)
						{
							printf("could not open input file \n");
							fflush(stdout);
							lastStatus = 1;
							fileFailure = 1;
						}

						dup2(inFD, 0);	//set input file to stdin
					}
						
					else if (outRedirectBool == 1) //setup output file if necessary
					{
						int outFD = open(outFileString, O_WRONLY|O_CREAT|O_TRUNC, 0644);
						if (outFD == -1)
						{
							printf("could not open output file \n");
							fflush(stdout);
							lastStatus = 1; 
							fileFailure = 1;						
						}

						dup2(outFD, 1); //set output file to stdout
					}
					if (fileFailure == 0) //execute only if files opened 
					{
						processesCreated++;
						execStatus = execvp(arguments[0], arguments);
						if (execStatus == -1)
						{
							printf("command could not be executed \n");
							fflush(stdout);
							lastStatus = 1;
						} 
					}
				}

				else //in parent process
				{	

					if (backgroundBool == 1) //run in background
					{
						defaultAct.sa_handler = SIG_DFL; //set signal handling back to default
						sigaction(SIGTERM, &defaultAct, NULL);
						
						printf("background process id is %i \n", cpid);
						fflush(stdout);


						waitpid(cpid, &lastStatus, WNOHANG); //continue running foreground, wait for bg
						if (WIFEXITED(lastStatus))
						{
							if (WIFSIGNALED(lastStatus)) //exited with signal
							{
								lastStatus = WIFSIGNALED(lastStatus);
								printf("exited with signal %i \n", lastStatus);
								fflush(stdout);	
							}
							else
							{
							lastStatus = WEXITSTATUS(lastStatus); //exited normally
							printf("exit status was %d\n", lastStatus);
							fflush(stdout);

							}
						}
					}
						
					else //run in foreground
					{
						waitpid(cpid, &lastStatus, 0); //wait for the foreground process to finish before continuing
						lastStatus = WEXITSTATUS(lastStatus);	
							 		
					}
				}
				break;

			default:
			printf("error determining line type \n");
	
		}

		fflush(stdout);
		free(arguments);
		free(commandString);
	} //end of for loop 
	return 0;
}
