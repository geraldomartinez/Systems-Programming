//Geraldo Martinez
//gm979351

/*
This file contains the main function for the second part (part b) of project 5. This 
program handles several files both formatted and unformatted using unix system calls.
This program has three different flags of -c -x and -p in which each serve for a 
different purpose and take different command line arguments depending on which you used.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//Constants declared to use in this program
#define FOUR_ARGS 4 //Number of possible command line arguments
#define THREE_ARGS 3 //Number of possible command line arguments
#define FLAG_POSITION 1 //Position of the flag in the command
#define ARCHIVE_POSITION 2 //Possible archive position
#define PREFIX_POSITION 2 //Prefix position in the command
#define PREFIX_ARCHIVE 3 //Archive position when there is a prefix specified

char **my_argv; //global variables used to store command arguments
int my_argc; // global variable used to store number of command arguments


//Prototypes
void prefix(char *prefix_name, char *binary_file);
void create();
void extract(char *binary_file);

//Main
int main(int argc, char *argv[]){


	my_argv = argv; //Sets the global my_argv to argv
	my_argc = argc; //Sets the global my_argc to arg
	
	//If there are more than four arguments
	if((argc > FOUR_ARGS)){
		//Checks if appropiate flag was used
		if(strcmp(argv[FLAG_POSITION],"-c")==0){ 
			create(); //Calls on the create function
		}
		
		else{ //THe specified flag wasn't -c
			fprintf(stderr, "Wrong flag inputted.\n"); //Error message for wrong flag inputted.
			exit(1);
		}
	}
	//If there are exactly four arguments
	else if((argc == FOUR_ARGS)){ 
		//If the flag is -c
		if(strcmp(argv[FLAG_POSITION],"-c")==0){
			create(); //Calls on the create function
		}
		//If the flag is -p
		else if(strcmp(argv[FLAG_POSITION],"-p")==0){
			prefix(argv[PREFIX_POSITION], argv[PREFIX_ARCHIVE]); //Calls on the prefix function
		}
		else{ //THe specified flag wasn't either -c or -p
			fprintf(stderr, "Wrong flag inputted.\n"); //Error message for wrong flag inputted.
			exit(1);
		}
	}
	//If the number of args is three
	else if((argc == THREE_ARGS)){
		//Checks if the flag is -x
		if(strcmp(argv[FLAG_POSITION],"-x")==0){
			extract(argv[ARCHIVE_POSITION]); //Calls on the extract function
		}
		else{ //THe specified flag wasn't -x
			fprintf(stderr, "Wrong flag inputted.\n"); //Error message for wrong flag inputted.
			exit(1);
		}
		
	}
	else{ //Wrong valid of command line arguments
		fprintf(stderr, "Invalid number of command line arguments.\n"); //Error message if user inputs incorrect number of command line arguments.
		exit(1);
	}
return 0;
}