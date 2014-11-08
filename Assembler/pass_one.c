//Geraldo Martinez
//gm979351

/*
This file contains the pass_one function. The purpose of this function is to 
go through the file and pick up label names with it's respective symbol value.
It takes in a file as the parameter (Being the file that the user will input).
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "structs.h"
#include "prototypes.h"


extern struct symbol *symbol_container; //Externs the use of the symbol_container struct in order to pass store values in it.

void pass_one(FILE *infile){
	
	char buffer[BUFFER_MAX]; //Used to store the read line from the file
	char temp_holder[BUFFER_MAX]; //Temporarily holds the container of the buffer
	char *line_holder; //used to store the stripped down contents of the buffer
	char label_noColon[MAX_LABEL_LENGTH]; //Stores the label name
	
	int line_number = 1; //Starts the line count at 1. Represents the lines in the file
	int comment_check; //Used to tell whether line was a comment or not
	int current_line = 0; //Holds the value of the current line being processed 
	int num_holder=0; //Stores number read from buffer if it is primitive .word
	int second_num_holder=0; //Another variable used to store a number read from buffer
	int label_counter = 0; //Stores the number of labels in the file.
	
	
	//While there are lines in the file, read up to 81 characters at a time.
	while(fgets(buffer, BUFFER_MAX, infile) != NULL) 
	{
		if(strcmp(buffer, "\n") != 0){ //If the line isn't blank, enter
			if(strchr(buffer, ':') != NULL){ //If the line contains a label
				label_counter++; //Increment the number of labels in the file
			}
		}
		
	}
	
	symbol_container[label_counter+1]; //Initializes the symbol_container array in order to hold enough labels
	rewind(infile); //Rewinds the file to go through the first pass
	
	
	//While there are lines in the file, read up to 81 characters at a time.
	 while(fgets(buffer, BUFFER_MAX, infile) != NULL)
	{
		fprintf(errFILE, "%d: %s", line_number, buffer); //Re-prints the inputted file back to the error file
		line_number++;	//Increments the number of lines
		
		if(strcmp(buffer, "\n") != 0){ //If the line isn't blank
			comment_check = FALSE; //There is no line comment
			strcpy(temp_holder, buffer); //Compies the buffer into the tempholder
			line_holder = strtok(buffer, " \t\n"); //Strips any space in a line, concatenates the whole string.
			
			if(strchr(line_holder, '#') != NULL){ //Checks to see if there is a comment in the line
				comment_check = TRUE; //If there is, sets comment_check to true
			}
			
			if(strchr(line_holder, ':') != NULL){ //If there is a label in the string
				strcpy(label_noColon, line_holder); //Copies the contents of the line into the other variable
				strtok(label_noColon, ":"); //strips the colon off the label
				fprintf(symFILE, "%s\t%d \n", label_noColon, current_line); //prints the label into the symbol file, with the current line
				initialize_table(label_noColon, current_line, symbol_container); //Stores the labels into the symbol table
				strtok(temp_holder, ":"); //removes colon 
				line_holder = strtok(NULL, " \t"); //Strips any blank space in the current line
			}
	
			if(strchr(line_holder, '.') != NULL){ //If there is a period for a directive in the string...
				if(strcmp(line_holder, ".text") == 0){ //If it is a text directive
					current_line--; //decrement current line
				}
				if(strcmp(line_holder, ".data") == 0){ //If it is a data directive
					current_line--; //decrement current line
				}
				if(strcmp(line_holder, ".resw") == 0){ //if it is a resw directive
					line_holder = strtok(NULL, " \t,"); //strip away any blank space
					num_holder = atoi(line_holder); //store the number from the line into num_holder 
					current_line = current_line + num_holder - 1; //calculate the value of the current line
				}
				
				if(strcmp(line_holder, ".word") == 0){ //If it is a .word directive
					line_holder = strtok(NULL, " \t,"); //strip away any blank space
					
					if(strchr(line_holder, ':') != NULL){ //strip away the colon between number
						second_num_holder = atoi(line_holder); //store the first number in the variable
						line_holder = strchr(line_holder, ':'); //strip away the other colon
						line_holder = strtok(line_holder, " \t\n#:"); //strip away any other uncessesary space
						num_holder = atoi(line_holder); //store the second number
						current_line = current_line + num_holder - 1; //calculate the value of the current line
					}
				}
				
			}
			
			if (comment_check == FALSE){ //if the was no comment
				current_line++; //increment line
			}						
		}
	}
	
	multiple_symbol(); //calls on the multiple_symbol function and checks to see if there was multiple symbols

}