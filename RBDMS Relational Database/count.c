//Geraldo Martinez
//gm979351

/*
This file contains the function count. This function takes in a relation name to which then 
opens a corresponding schema and binary file. This function returns the number of tuples in 
the specified relation as a type int.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

int count(char *rel_name){
	char filename[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the binary file.
	char filename_two[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the schema file.
	char first_attr_type[ATTRIBUTE_TYPE_LENGTH]; //Declares a char variable that will be used to store the type of attribute.
	int count=0, waste, tuple_len; //Variables used for the program, count stores the number of tuples, while tuple_len stores the integers read in from binary.
	char *buffer;//Declares a char variable that will be used to read in the contents of the binary file.
	int tuple_size; //Used to store the size of each tuple of the binary file.
	FILE *file, *file_two; //FILE variable that will point to the file of the relation specified by the parameter.
	
	
	strcpy(filename, rel_name); //Copies the name of the relation onto the filename variable.
	strcat(filename, ".dat"); //Copies the .dat extension onto the filename variable.
	
	strcpy(filename_two, rel_name); //Copies the name of the relation onto the filename_two variable.
	strcat(filename_two, ".sch"); //Copies the .sch extension onto the filename_two variable.
	
	
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
		if((file = fopen(filename, "rb"))==NULL){
			fprintf(stderr, "Could not open the %s binary file for reading.\n", rel_name);
			exit(1);
			}
			
			tuple_size = tuplen(rel_name); //Stores the length of each tuple of the relation into tuple_size
			buffer = (char *)malloc(sizeof(char)*tuple_size); //Allocates space for the buffer with the total tuple size
			file_two = fopen(filename_two, "r"); //Opens the schema file for reading.
	
					while (fread((void *) buffer, sizeof(char), tuple_size, file)!=0){ //Loop through each tuple of the binary file until it hits EOF.

				count++; //Increment counter as it loops through each tuple.

			}
			return count; //Returns the count of tuples of the relation.
			
			/* Attempts to close the binary file, if it is unable to close it prints out an error message.
		*/
			if (fclose(file)==EOF){
			fprintf(stderr, "Could not close the file: %s.\n", filename);
			exit(1);
		}
	}

}