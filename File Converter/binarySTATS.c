//Geraldo Martinez
//gm979351

/*
This file contains the function binarySTATS. This function takes in one parameter of type FILE,
which represents a binary file. With this binary file, it reads the data line by line and computes
certain statistical information from it such as longest and shortest integer as well as string.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

void binarySTATS(FILE *input){

	char buffer[BUFFER_SIZE]; //Holds the string being read from the binary file.
	int count; //Holds the integer being read from the binary file.
	unsigned char buffer_size; //Holds the size of the string in each line of the binary file.

	int min_value; //Holds the value of the lowest integer in the binary file.
	int max_value; //Holds the value of the highest integer in the binary file.
	
	int integer_boolean_value = 0; //Boolean value for the first loop in the while loop for the integer calculation, then sets to 1.
	int buffer_boolean_value = 0; //Boolean value of the first loop in the while loop for the string calculation, then sets to 1.
	
	int string_min; //Holds the value of the string with the lowest chars.
	int string_max; //Holds the value of the string with the highest chars.
	int string_count; //Holds the value of the current string being processed in the while loop or binary file.
	char max_string[BUFFER_SIZE]; //Represents the string of the largest string in the binary file.
	char min_string[BUFFER_SIZE]; //Represents the string of the shortest string in the binary file.
	
	while (fread((void *) &buffer_size, sizeof(unsigned char), 1, input)!=0){ //Loops while there are more lines to read in the binary file.
				
		fread((void *) buffer, sizeof(char), buffer_size, input); //Reads the string in the current line of the binary file, then stores it into buffer.
		string_count = strlen(buffer); //Stores the length of the current string into string_count.
		
		if (buffer_boolean_value == 0){ //If statement that only happens on the first line of the binary file being read.
		buffer_boolean_value = 1; //Sets the value of the boolean variable to 1, making the if statement unreachable .
		strcpy(max_string, buffer); //Copies the string of the first line into max_string.
		strcpy(min_string, buffer); //Copies the string of the first line into min_string.
		string_max = strlen(buffer); //Stores the length of the buffer into string_max.
		string_min = strlen(buffer); //Stores the length of the buffer into string_min.
		}
		
		if (string_count < string_min){ //If the length of the current string is lower than the string_min,
			string_min = string_count; //then store that value into string_min.
		}
		
		if (string_count > string_max){ //If the length of the current string in higher than string_max,
			string_max = string_count; //then stores that value into string_max.
		}
		
		fread((void *) &count, sizeof(int), 1, input); //Reads the integer in the current line of the binary file, then stores it into count.
		
			if (integer_boolean_value == 0){ //If statement that only happens on the first line of the binary file being read.
			integer_boolean_value = 1; //Sets the value of the boolean variable to 1, making the if statement unreachable .
			max_value = count; //Stores the value of the first integer into max_value.
			min_value = count; //Stores the value of the first integer into min_value.
		}
		
		if(count < min_value) //If the current count is lower than the min_value,
		{
			min_value = count; //then stores the count into min_value.
		}
		
		if (count > max_value){ //If the current count is higher than the max_value,
		max_value = count; //then stores that count into max_value.
		}
		
		//printf("%s\t%d\n", buffer, count);
		memset(buffer, 0, BUFFER_SIZE); //Resets the buffer in order to get rid of corrupted data.
	}
	
	
	printf("Length of a shortest string in the input file	= %d\n", string_min ); //Prints the statistics for the shortest string in the binary file.
	fflush(stdout);
	printf("Length of a longest string in the input file	= %d\n", string_max ); //Prints the statistics for the longest string in the binary file.
	fflush(stdout);
	printf("Value of the maximum integer in the input file	= %d\n", max_value); //Prints the statistics for the maximum integer in the binary file.
	fflush(stdout);
	printf("Value of the minimum integer in the input file	= %d\n", min_value); //Prints the statistics for the minimum integer in the binary file.
	fflush(stdout);

}