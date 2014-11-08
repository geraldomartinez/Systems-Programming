//Geraldo Martinez
//gm979351

/*
This file contains the function text_to_binary. This function converts an inputted text 
file and writes its contents in another file being binary. The function takes in two
parameters of type FILE that represent the inputted text file and the outputted binary file.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"


void text_to_binary(FILE *input, FILE *output){

	unsigned char buffer_length; //Represents the variable that stores the length of the string in the file.
	char buffer[BUFFER_SIZE]; //Represents the char array in which the string from the binary file will be read in and stored.
	int value; //Represents the integer being read from the text and copied into the binary file.
	int count; //Used to store the length of the buffer when the strlen is called on.
	
	/* This while loop runs through the text file scanning each line until it hits the End of the file. */
	while ( fscanf(input, "%s %d", buffer, &value) != EOF){
	       
                
	    count = strlen(buffer); //Stores the length of the buffer into the count variable.
		buffer_length = (unsigned char) count; //Casts the length of the buffer into an unsigned char and stores it into buffer_length.
		fwrite((const void *) &buffer_length, sizeof(unsigned char), 1, output); //Writes the first byte into the binary file.
		fwrite((const void *) buffer, count, 1, output); //Writes the string read from the text file into the binary file.
		fwrite((const void *) &value, sizeof(int), 1, output); //Writes the int value read from the text file into the binary file.
		memset(buffer, 0, BUFFER_SIZE); //Resets the buffer in order to get rid of junk data.
	}	

}