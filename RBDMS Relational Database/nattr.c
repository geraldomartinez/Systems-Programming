//Geraldo Martinez
//gm979351

/*
This file contains the function nattr. This function takes in a parameter
of type char that specifies the name of a relation. The function then 
prints the number of attributes of the specified relation.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

void nattr(char *rel_name){
	char filename[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the file.
	int attributes; //Declaration of variable that will be used to store the number of attributes in the specified relation.
	FILE *file; //FILE variable that will point to the file of the relation specified by the parameter.
	
	strcpy(filename, rel_name); //Copies the name of the relation onto the filename variable.
	strcat(filename, ".sch"); //Copies the extension onto the filename variable.
	
	/* This IF statement tests wether the file exists in the current directory or not, if it does, the function moves onto
	the else part, if it doesn't exists, it prints out an error message specifying an invalid relation. */
	if (fileExist(filename)==0){
		fprintf(stderr, "Error: Invalid relation -- %s\n\n", rel_name);
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
		
		fscanf(file, "%d", &attributes); //Scans in the first digit of the schema file of the specified relation.
		printf("%d\n\n", attributes); //Prints this number, since this is the number of attributes on the relation.
		
		/* Attempts to close the schema file, if it is unable to close it prints out an error message.
		*/
		if (fclose(file)==EOF){
			fprintf(stderr, "Could not close the file: %s.\n", filename);
			exit(1);
		}
	
	}
}