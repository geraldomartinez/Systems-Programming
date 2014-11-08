//Geraldo Martinez
//gm979351

/*
This file contains all of the functions used for error checking in a file.
The functions print the error accordingly to the error file. The functions include
multiple_symbol, opArguments_lookup, and symbol_lookup.
*/


//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Header files needed in this file.
#include "constants.h"
#include "structs.h"

extern struct opcode op_table[]; //Extends the opcode table which will be used later on.
extern int error_check; //Uses the error variable to update whether an error has been found.
extern int table_len; //Uses the variable containing the length of the opcode table array.



/*
The function multiple symbol identifies the labels previously used in the file.
It uses a linked list to manuever through the previous values, comparing each one
to the ones before. Then pointing to the next node.
*/
void multiple_symbol(){
	struct symbol *first_pointer; //The first pointer used to point at the next node
	struct symbol *second_pointer; //The second pointer used to point at the current node
	int boolean = FALSE; //boolean statement used to print the multiply defined symbols
	second_pointer = head; //Sets the pointer to point to the head node
	
	//Loops through the list until there are no more nodes
	while(second_pointer != NULL){
		first_pointer = second_pointer -> next; //Sets the pointer to point to the next node
			
			//Loops through the list until there are no more next nodes
			while(first_pointer != NULL){
			
				//Compares the current node's label to the next
				if (strcmp(first_pointer -> name, second_pointer -> name) == 0){
				
				
				//If there is a match, write to the error file accordingly and set error_check to TRUE
				
					if (boolean == FALSE){
						fprintf(errFILE, "\nMultiply defined symbol(s): \n\n");
						boolean = TRUE;
					}
					fprintf(errFILE, "  %s\n", first_pointer -> name);
					error_check = TRUE;
				}
			first_pointer = first_pointer -> next; //Sets the pointer to the next node.
			}
		second_pointer = second_pointer -> next; //Sets the pointer to the next node.
	}
	fprintf(errFILE, "\n"); //Prints a line in between the error message and the symbols.
}

/*
This function is the opArguments_lookup. The purpose of this function is to 
ensure that the current line being read from the file is a legal opcode, it returns 
the number of arguments of the opcode if it is legal, if it's not, it returns 0 and prints
an error message to the error file. Takes in two parameters, the current line in the file,
as well as the string containing the opcode.
*/
int opArguments_lookup(char *opcode, int line){ 
	int i = 0; //used to loop through the opcode table.
	int arguments = 0; //Variable used to store the number of arguments of the opcode
	
	
	//Exits the functions if there is a comment
	if (strchr(opcode, '#') != NULL){
		return; 
	}
	
	//Exits the function if there is a directive
	if(strchr(opcode, '.') != NULL) {
		return;
	}
	
	//Loops through the opcode symbol table
	for(i = 0; i<= table_len-1; i++){ //Loops up until 36 elements
		if(strcmp(op_table[i].name, opcode) == 0){ //If the current opcode is a match
			arguments = op_table[i].numArgs; //Stores the number of arguments of that opcode into arguments
			return arguments; //Returns this number
		}
		if (i == table_len-1){ //If i is equal to 35, then there was no opcode found in the table
			 fprintf(errFILE, "line %d:\tIllegal opcode %s.\n", line, opcode); //prints the error message to the file
			  error_check = TRUE; //Sets the error variable to true to indicate that there was an error in the inputted file
			  return 0; //Returns 0
			
		}
	}
}

/*
The function symbol_lookup checks the third case of an error for this assembler. It takes in 
one parameter that represents a symbol in the file, if it is not in the symbol table, then it 
prints an error message to the file.
*/
void symbol_lookup(char *symbol_name){
	struct symbol *pointer_node; //defines a symbol pointer
	
	pointer_node = head; //Sets the pointer to the beginning of the list
	
	while (pointer_node != NULL){ //Loops until there are no more nodes
		if (strcmp(pointer_node -> name, symbol_name) == 0 ){ //If there is a symbol match, exits the function
			return;
		}
		else {
			pointer_node = pointer_node -> next; //If there isn't a match, points to the next node and repeats 
		}
	}
	
	error_check = TRUE; //if it reaches this point, then there was no symbol, indicating there was an error.
	fprintf(errFILE, "Symbol %s not found\n", symbol_name); //Prints the error message accordingly 
}