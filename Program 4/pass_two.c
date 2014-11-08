//Geraldo Martinez
//gm979351

/*
This file contains the pass_two function. The purpose of this function is to 
go through the file and finish assembling the rest of the program. This function
has various purposes from error checking, writing to the object file the correct
hex values of instructions, etc.
*/


//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Header files needed in this file.
#include "constants.h"
#include "structs.h"
#include "oc_table.h"
#include "prototypes.h"

int error_check = FALSE; //Declares a variable used to keep track of any errors found or not.

void pass_two(FILE *infile){
	
	char buffer[BUFFER_MAX]; //Used to store the read line from the file
	char temp_holder[BUFFER_MAX]; //Temporarily holds the container of the buffer
	char *line_holder; //used to store the stripped down contents of the buffer
	char label_noColon[MAX_LABEL_LENGTH];  //Stores the label name
	char instruction[MAX_LABEL_LENGTH]; //stores the current instruction of the .data directive processed
	
	int i; //used for the for loop in the .word directive
	int line_counter=0; //used to count lines
	int first_register; //Stores the value of the first register
	int second_register; //Stores the value of the second register
	int target_register; //Stores the value of the target register
	int immediate_operand; //stores the immediate operand
	int unused; //Stores the unused bytes for the Rformat
	
	int LC_value; //Holds the value of the LC value of the symbol
	int opArguments; //Holds the number of arguments of the current opcode
	char opFormat; //Holds the type of format of the current opcode
	int opcode_number; //Holds the opcode number of the current opcode
	
	int current_line = 0; //Starts the current line at 0
	int word_count; //Used to store the number of .word directives
	int num_holder; //Holds the number read from the file
	
	//This while loop is the heart of the second pass, reads up to 81 characters per line
	while(fgets(buffer, BUFFER_MAX, infile) != NULL)
	{
	
		//Resets all the registers and variables for every line read
		i = 0;
		first_register = 0;
		second_register = 0;
		target_register = 0;
		immediate_operand = 0;
		unused = 0;
		
		//If the current line is not a new line, then enter
		if(strcmp(buffer, "\n") != 0 ){
			strcpy(temp_holder, buffer); //copies the current line into this temps
			line_holder = strtok(buffer, " \t\n"); //Copies the current line with no spaces in strings
			
			/*If there is a colon, then it is a label
				Enters the case where if there is a label
				the program does certain computations
			*/
			if(strchr(line_holder, ':') != NULL){ 
				strcpy(label_noColon, line_holder); //Copies the stripped line into this variable
				strtok(label_noColon, ":"); //strips the colon off the line, leaving the label
				
				strtok(temp_holder, ":"); //strips the colon off the temp_holder
				line_holder = strtok(NULL, " \t\n"); //strips the space off the line
				strcpy(instruction, line_holder); //copies the current instruction onto this variable
				
				
				/*
				The following function calls are used to store the respective opcode number
				from the current line into the variables, if there is an error in the line, it prints
				out the error message accordingly.
				*/
				opcode_number = opcode_number_lookup(line_holder);
				opArguments = opArguments_lookup(line_holder, current_line);
				opFormat = opFormat_lookup(line_holder);
				
				
				//If the opcode type takes in three arguments
				if (opArguments == THREE_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					target_register = atoi(line_holder); //converts the number read in from the file and stores it into the target register
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					first_register = atoi(line_holder); //converts the number being read in from the file and stores it
					
					
					/*Special cases for opcode numbers ranging from 11-13, and 19-23 for which all have three arguments*/
					if(((opcode_number >= op_table[19].opcode_number) && (opcode_number <= op_table[23].opcode_number))
					|| ((opcode_number >= op_table[11].opcode_number) && (opcode_number <= op_table[13].opcode_number))){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						immediate_operand = atoi(line_holder); //converts the number being read in from the file and stores it
						unused = atoi(line_holder); //converts the number being read in from the file and stores it
					}					
					//special case for the jeq opcode
					else if(opcode_number >= op_table[30].opcode_number){
						line_holder = strtok(NULL, "\t\n,$"); //strips the line from any space, commas or register sign.
						symbol_lookup(line_holder); //Since opcode 30 takes in a symbol, checks wether or not it exists
						LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
					}
					else { //else, do the following for the rest of the three argument opcodes
					line_holder = strtok(NULL, " \t\n,$");  //strips the line from any space, commas or register sign.
					second_register = atoi(line_holder); //converts the number being read in from the file and stores it
					}
					
				}
				
				//If the opcode type takes in two arguments
				else if(opArguments == TWO_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					target_register = atoi(line_holder); //converts the number being read in from the file and stores it
					
					//Special case for 'li'
					if(opcode_number == op_table[18].opcode_number){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						immediate_operand = atoi(line_holder); //converts the number being read in from the file and stores it
					}
					
					//special cases for lwa and swa
					else if((opcode_number >= op_table[26].opcode_number) &&
						(opcode_number <= op_table[27].opcode_number)){
							line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							symbol_lookup(line_holder); //Since opcode takes in a symbol, checks wether or not it exists
							LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
						}
					//special cases for lwb and swb	
					else if((opcode_number >= op_table[24].opcode_number) &&
						(opcode_number <= op_table[25].opcode_number)){
							line_holder= strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							immediate_operand = atoi(line_holder); //converts the number being read in from the file and stores it
							line_holder= strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							first_register = atoi(line_holder); //converts the number being read in from the file and stores it
						}
					
					else { //rest of the two argument cases
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						first_register = atoi(line_holder); //converts the number being read in from the file and stores it
					}
				}
				
				//If the current opcode has one argument
				else if(opArguments == ONE_ARG){
				
					//special case for the j and jal opcodes
					if((opcode_number >= op_table[28].opcode_number) &&
						(opcode_number <= op_table[29].opcode_number)){
							line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							symbol_lookup(line_holder); //Since opcode takes in a symbol, checks wether or not it exists
							LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
						}
					else { //rest of the one argument cases
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						target_register = atoi(line_holder); //converts the number being read in from the file and stores it
					}	
				
				}
				
				//if the current opcode has no arguments
				else if(opArguments == NO_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
				}
				
				if(opFormat == 'R'){ //if the opcode format is of type R
					rformat(opcode_number, target_register, first_register, second_register,
					unused, line_counter); //Call the R-fomat function
					line_counter++; //increment the line
				}
				if(opFormat == 'I'){ //if the opcode format is of type I
					iformat(opcode_number, target_register, first_register, 
					immediate_operand, line_counter); //Call the I-fomat function
					line_counter++; //increment the line
				}
				if(opFormat == 'J'){ //if the opcode format is of type J
					LC_value = LC_value_lookup(line_holder);
					jformat(opcode_number, target_register, first_register, LC_value, 
					immediate_operand, line_counter); //Call the J-fomat function
					line_counter++; //increment the line
				}
	
					if(strcmp(instruction, ".word") == 0) { //if there is a .word directive
						line_holder = strtok(NULL, " \t,"); //strips the line from any space, commas or register sign.
							if(strchr(line_holder, ':') != NULL){ //if there is a colon separating numbers
								word_count = atoi(line_holder); //converts the number being read in from the file and stores it
								line_holder = strchr(line_holder, ':');  //check if there is another colon
								line_holder = strtok(line_holder, " \t\n#:");  //strips the line from any space, commas or register sign.
								num_holder = atoi(line_holder); //converts the number being read in from the file and stores it
								
								//loops for the number specified in the file
								for(i = 0; i < num_holder; i++) {
									fprintf(objFILE, "%X\t%X \n", line_counter, word_count); //print the hex values into the object file
									line_counter++; //increment the line
								
								}
							
							}
						
					}
				
			}
			
			
			/*
			This marks the beginning of the second half of pass-two, this else statement deals
			with lines of code that do not have any labels in them.
			*/
			
			
			else{
				strcpy(instruction, line_holder); //copies the current instruction onto this variable
				
				/*
				The following function calls are used to store the respective opcode number
				from the current line into the variables, if there is an error in the line, it prints
				out the error message accordingly.
				*/
				opcode_number = opcode_number_lookup(line_holder);
				opArguments = opArguments_lookup(line_holder, current_line);
				opFormat = opFormat_lookup(line_holder);
				
				//If the current opcode takes in three arguments, enter.
			if (opArguments == THREE_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					target_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					first_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					
					if((opcode_number >= op_table[19].opcode_number) && (opcode_number <= op_table[23].opcode_number)){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						immediate_operand = atoi(line_holder);  //converts the number being read in from the file and stores it
					}
					
					else if((opcode_number >= op_table[11].opcode_number) && (opcode_number <= op_table[13].opcode_number)){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						unused = atoi(line_holder);  //converts the number being read in from the file and stores it
					}
					
					else if(opcode_number >= op_table[30].opcode_number){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						symbol_lookup(line_holder); //Since opcode takes in a symbol, checks wether or not it exists
						LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
					}
					else {
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					second_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					}
					
				}
				
				//If the current opcode takes in two arguments, enter.
				else if(opArguments == TWO_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
					target_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					
					if(opcode_number == op_table[18].opcode_number){
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						immediate_operand = atoi(line_holder);  //converts the number being read in from the file and stores it
					}
					
					else if((opcode_number >= op_table[26].opcode_number) &&
						(opcode_number <= op_table[27].opcode_number)){
							line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							symbol_lookup(line_holder); //Since opcode takes in a symbol, checks wether or not it exists
							LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
						}
						
					else if((opcode_number >= op_table[24].opcode_number) &&
						(opcode_number <= op_table[25].opcode_number)){
							line_holder= strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							immediate_operand = atoi(line_holder);  //converts the number being read in from the file and stores it
							line_holder= strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							first_register = atoi(line_holder);  //converts the number being read in from the file and stores it
						}
					
					else {
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						first_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					}
				}
				
				//If the current opcode takes in one arguments, enter.
				else if(opArguments == ONE_ARG){
				
				//Resets the values of these registers for one argument
					first_register = 0;
					second_register = 0;
					
					
					if((opcode_number >= op_table[28].opcode_number) &&
						(opcode_number <= op_table[29].opcode_number)){
							line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
							symbol_lookup(line_holder); //Since opcode takes in a symbol, checks wether or not it exists
							LC_value = LC_value_lookup(line_holder); //stores the LC value of that symbol into the variable
						}
					else {
						line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
						target_register = atoi(line_holder);  //converts the number being read in from the file and stores it
					}	
				
				}
				
				//If the current opcode takes in no arguments, enter.
				else if(opArguments == NO_ARGS){
					line_holder = strtok(NULL, " \t\n,$"); //strips the line from any space, commas or register sign.
				}
				
				if(opFormat == 'R'){ //if the opcode format is of type R
					rformat(opcode_number, target_register, first_register, second_register,
					unused, line_counter); //Calls the R-format function
					line_counter++; //Increments the line counter
				}
				if(opFormat == 'I'){ //if the opcode format is of type I
					iformat(opcode_number, target_register, first_register, 
					immediate_operand, line_counter); //Calls the I-format function
					line_counter++; //Increments the line counter
				}
				if(opFormat == 'J'){ //if the opcode format is of type J
					LC_value = LC_value_lookup(line_holder);
					jformat(opcode_number, target_register, first_register, LC_value, 
					immediate_operand, line_counter); //Calls the J-format function
					line_counter++; //Increments the line counter
				}
			
			}
			
			
		}
		
		current_line++; //Increments the number of lines to show the current line
		
	} //Ends the while Loop
	
} //End of the pass two function