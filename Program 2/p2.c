//Geraldo Martinez
//gm979351

/* This file contains the main function for this program. This program takes in either
three or four parameters, depending on the flag you specify in the input. This program
is able to take in an inputted text file and convert it to its equivalent binary file, 
and vice versa. It is also able to print out certain statistics from an inputted binary
file, all depending on the flag you specify. */

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

int main(int argc, char *argv[]){
FILE *text, *binary; //Declares the two variables of type FILE that will be manipulated in this program.

	
	if((argc == NUMBER_ARG_STAT)){ //Enters the IF statement in the number of arguments is 3.
		
		//If the binary file cannot be opened for reading, then prints out an error saying so.
		if((binary = fopen(argv[INPUT_FILE_ARG], "rb"))==NULL){
		fprintf(stderr, "Could not open the file for reading in the third argument.\n");
		exit(1);
		
	}
		if(strcmp(argv[FLAG_ARG],"-s")==0){ //If the flag entered is -s, then enters the IF statement, else prints out error message.

			binarySTATS(binary); //Calls on the binarySTATS function to compute statistical information on the inputted binary file.
			
			/*Checks to see if input_file can be close.
			If not, prints an error message and exits the program. */
			if (fclose(binary)==EOF){
			fprintf(stderr, "Could not close the file.\n", argv[INPUT_FILE_ARG]);
			exit(1);
			}
	
			
			
		}
		else {
			fprintf(stderr, "Wrong flag inputted.\n"); //Error message for wrong flag inputted.
			exit(1);
		}
	}
	
	else if((argc == NUMBER_ARG_CONVERT)){ //If the number of arguments is four, then enters this IF statement.
		
		if(strcmp(argv[FLAG_ARG], "-t")==0){ //If the flag is of -t, then enters this IF statement.
		
		
			//Opens the text file for reading, if not able to prints out an error message saying so.
			if((text = fopen(argv[INPUT_FILE_ARG], "r"))==NULL){ 
			fprintf(stderr, "Could not open the file for reading in the third argument.\n");
			exit(1);
		}	
			//Opens the binary file for writing, if not able to prints out an error message saying so.
			if((binary = fopen(argv[OUTPUT_FILE_ARG], "wb"))==NULL){
			fprintf(stderr, "Could not open the file for writing in the fourth argument.\n");
			exit(1);
		}
		
			text_to_binary(text, binary); //Calls on the function that converts the text file into a binary file.
			
			/*Checks to see if input_file can be close.
			If not, prints an error message and exits the program. */
			if (fclose(text)==EOF){
			fprintf(stderr, "Could not close the file. \n", argv[INPUT_FILE_ARG]);
			exit(1);
			}
			
			
			/*Checks to see if input_file can be close.
			If not, prints an error message and exits the program. */
			if (fclose(binary)==EOF){
			fprintf(stderr, "Could not close the file.\n", argv[OUTPUT_FILE_ARG]);
			exit(1);
			}
			
		}
		else if(strcmp(argv[FLAG_ARG], "-b")==0){ //If the flag is -b, then enters this IF statement.
		
		//Opens the text file for writing, if not able to then it prints out a message saying so.
		if((text = fopen(argv[OUTPUT_FILE_ARG], "w"))==NULL){
		fprintf(stderr, "Could not open the file for writing in the fourth argument.\n");
		exit(1);
		}
		
		//Opens the binary file for reading, if not able to then it prints out a message saying so.
		if((binary = fopen(argv[INPUT_FILE_ARG], "rb"))==NULL){
		fprintf(stderr, "Could not open the file for reading in the third argument.\n");
		exit(1);
	}
			binary_to_text(binary, text); //Calls onto the binary_to_text function to convert the binary to text file.
			
			/*Checks to see if input_file can be close.
			If not, prints an error message and exits the program. */
			if (fclose(text)==EOF){
			fprintf(stderr, "Could not close the file.\n", argv[OUTPUT_FILE_ARG]);
			exit(1);
			}
			
			
			/*Checks to see if input_file can be close.
			If not, prints an error message and exits the program. */
			if (fclose(binary)==EOF){
			fprintf(stderr, "Could not close the file.\n", argv[INPUT_FILE_ARG]);
			exit(1);
			}
			
		}
		else{
		
			fprintf(stderr, "Invalid flag inputted by user.\n"); //Error message if the wrong flag is inputted.
			exit(1);
		}
	}
	else {
	fprintf(stderr, "Invalid number of command line arguments.\n"); //Error message if user inputs incorrect number of command line arguments.
		exit(1);
	}
	

	
return 0;
}