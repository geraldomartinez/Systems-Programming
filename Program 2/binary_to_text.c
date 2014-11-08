//Geraldo Martinez
//gm979351

/*
This file contains the function binary_to_text. This function converts an inputted binary 
file and writes its contents in another file of type text. The function takes in two
parameters of type FILE that represent the inputted binary file and the outputted text file.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

void binary_to_text(FILE *input_file, FILE *output_file){
	char buffer[BUFFER_SIZE]; //Represents the char array in which the string from the binary file will be read in and stored.
	int count; //Represents the integer value that will be read from the binary and then printed on the text file.
	unsigned char buffer_size; //Holds the size of the first byte from the binary file representing the size of the buffer.
	
	
	//Reads through the file line by line until the fread returns a value of 0, which means that there are no more lines.
	while (fread((void *) &buffer_size, sizeof(unsigned char), 1, input_file)!=0){ //Reads the first byte of the binary file.
		fread((void *) buffer, sizeof(char), buffer_size, input_file); //Reads the string of the current line from the binary file and stores it into buffer.
		fread((void *) &count, sizeof(int), 1, input_file); //Reads the integer from the binary file into the count.
		fprintf(output_file, "%s\t%d\n", buffer, count); //Writes the inputted data from the binary file into the text file.
		memset(buffer, 0, BUFFER_SIZE); //Resets the buffer in order to avoid corrupted data.
	}
}
