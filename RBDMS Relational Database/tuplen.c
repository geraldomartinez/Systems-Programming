//Geraldo Martinez
//gm979351

/*
This file includes the function tuplen. This function returns a integer representing the total size
of a tuple in the specified relation. The function takes in one parameter consisting of the name of such
relation. 
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

int tuplen(char *rel_name){
	char filename[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the file.
	int byte_length=0; //Variable that will store the length of the individual attribute of the schema file.
	int byte_count=0; //Variable that will store the total length of the tuple in the relation.
	int waste=0; //Used as a place holder for the first integer of the schema file.
	FILE *file; //FILE variable that will point to the file of the relation specified by the parameter.
	
	strcpy(filename, rel_name); //Copies the name of the relation onto the filename variable.
	strcat(filename, ".sch"); //Copies the extension onto the filename variable.

	
	/* This IF statement tests wether the file exists in the current directory or not, if it does, the function moves onto
	the else part, if it doesn't exists, it prints out an error message specifying an invalid relation. */
	if (fileExist(filename)==0){
		fprintf(stderr, "Error: Invalid relation -- %s\n\n", rel_name);
		return 0;
	}
	//If the file exists, do the following.
	else{
		/* Checks to see if the relation file can be opened for reading, if not prints out an
		error message and exits the program.
		*/
		if((file = fopen(filename, "r"))==NULL){
			fprintf(stderr, "Could not open the %s schema file for reading.\n", rel_name);
			exit(1);
			}
		
			fscanf(file, "%d", &waste); //Scans the first integer of the schema file.
			
			/* This while loop loops until the schema file hits EOF, scanning only the 
			integer from each line and skipping the first two strings of the schema file.*/
			while(fscanf(file, "%*s%*s%d", &byte_length) != EOF){ 
				byte_count += byte_length; //Stores the byte size of each attribute into byte_count. 
				}
				
		return byte_count; //Returns the length of each tuple of the specified relation 
		
		/* Attempts to close the schema file, if it is unable to close it prints out an error message.
		*/
		if (fclose(file)==EOF){
			fprintf(stderr, "Could not close the file: %s.\n", filename);
			exit(1);
			}
	}
}