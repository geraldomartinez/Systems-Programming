//Geraldo Martinez
//gm979351

/*
This file contains the infattr function. This function takes in a name of a relation 
and a corresponding attribute name. It scans the schema file, determining the type of attribute,
and the length in bytes of it. If no relation or attribute exists, then prints out appropiate error
message.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

void infattr(char *rel_name, char *attr_name){
	char filename[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the file.
	FILE *file; //FILE variable that will point to the file of the relation specified by the parameter.
	int waste = 0; //Used as a place holder for the first integer of the schema file.
	int byte_length = 0; //Stores the current byte length of the schema file.
	int boolean_value = 0; //Used as a boolean value for determining wether there is a match in an attribute name.
	char attrName[ATTRIBUTE_SIZE], attrType[ATTRIBUTE_TYPE_LENGTH]; 
	
	
	strcpy(filename, rel_name); //Copies the name of the relation onto the filename variable.
	strcat(filename, ".sch"); //Copies the extension onto the filename variable.
	
	/* This IF statement tests wether the file exists in the current directory or not, if it does, the function moves onto
	the else part, if it doesn't exists, it prints out an error message specifying an invalid relation. */
	if (fileExist(filename)==0){
		fprintf(stderr, "Error: Invalid relation -- %s\n\n", rel_name);
	}
	
	//If the file exists, do the following.
	else {
	
		/* Checks to see if the relation file can be opened for reading, if not prints out an
		error message and exits the program.
		*/
		if((file = fopen(filename, "r"))==NULL){
			fprintf(stderr, "Could not open the %s schema file for reading.\n", rel_name);
			exit(1);
			}
	
		fscanf(file, "%d", &waste); //Scans the first integer of the schema file.
		/*
		While loop that scans each line of the schema file, scanning both strings and integer
		until it hits the EOF. 
		*/
		while (fscanf(file, "%s%s%d", attrName, attrType, &byte_length)!=EOF){
			
			//If the current attribute name scanned in the file matches the one passed by the parameter, enter the if statement.
			if (strcmp(attr_name, attrName)==0){
				printf("Attribute type	: %s\n", attrType); //Prints the attribute type
				printf("Attribute length: %d\n\n", byte_length); //Prints the attribute byte length
				boolean_value = 1; //Sets the value of boolean_value to one.
			}
		}
		
		//If the value of boolean_value is still 0, then no match was found, indicating an invalid attribute.
		if (boolean_value==0){
			printf("Error: Invalid attribute -- %s\n\n", attr_name);
		}
		
		/* Attempts to close the schema file, if it is unable to close it prints out an error message.
		*/
		if (fclose(file)==EOF){
		fprintf(stderr, "Could not close the file: %s.\n", filename);
		exit(1);
		}
	}
}