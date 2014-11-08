//Geraldo Martinez
//gm979351

/*
This file contains all the necessary functions to compute and setup necessary
measures for the assembler. The file includes four functions named initialize_table,
opcode_number_lookup,LC_value_lookup, and opFormat_lookup
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"
#include "structs.h"

extern struct opcode op_table[]; //Extends the use of the opcode table.
extern int table_len; //Uses the length of the opcode table array.

/*
The function initialize table sets up the symbol table that will be used to store
the nodes representing the symbol names in the file, it takes in a label name(symbol), 
the current line, and a struct of type linked list.
*/
void initialize_table(char *label, int line_num, struct symbol table_sample){

	struct symbol *node_pointer; //Declares a pointer used to loop set up the list.
	node_pointer = malloc(sizeof(table_sample)); //sets the pointer with the correct size depending on the size of the table
	
	strcpy(node_pointer -> name, label); //Copies the current label into the first node into the list.
	node_pointer -> LC_value = line_num; //Sets the LC_value of the current label according to the current line being processed.
	
	node_pointer -> next = head; //Sets the next node to the head.
	head = node_pointer; //Sets the head back to the current pointer.
	return; //Exits
}


/*
The function opcode_number_lookup takes in the current line of the file
and checks to see if the current opcode name is a match to any on the table,
if it is, it returns the opcode number
*/
int opcode_number_lookup(char *current_line){ //opNumSearch
	int i; //Variable  used to look through the table
	int opNumber; //Variable used to store the opcode number
	
	
	for(i = 0; i <= table_len-1; i++){ //Loops through the opcode table, 36 elements
		if(strcmp(op_table[i].name, current_line) == 0){ //if there is a match with an opcode name and the one inputted
			opNumber = op_table[i].opcode_number; //Stores the opcode number into the opNumber variable.
			return opNumber; //Returns this number
		}
	}
	return 0; //Exits if there was no match
}

/*
The LC_value_lookup function takes in a label, or symbol, and checks through the symbol
table to return its appropriate LC value.
*/
int LC_value_lookup(char *current_line){
	int LC_value; //Variable used to store the LC value
	struct symbol *node_pointer; //Pointer used to loop through the list
	
	node_pointer = head; //sets the pointer at the beginning of the list
	
	while(node_pointer != NULL){ //Loops while there are elements in the list
		if(strcmp(node_pointer -> name, current_line) ==0){ //If there is a match in the label
			LC_value = node_pointer -> LC_value; //Stores the LC value of the node into the LC value variable
			return LC_value; //Returns the value
		}
		
		node_pointer = node_pointer -> next; //Sets the pointer to point at the next node
	
	}
	
	return 0; //Exits
}

/*
The opFormat_lookup function checks to see the type of format of the current
opcode, according to the opcode symbol table. It takes in the current opcode as 
a parameter
*/
char opFormat_lookup(char *current_line){
	int i; //Variable used to loop through the table
	char opFormat; //Used to store the format 
	
	for (i = 0; i<= table_len-1; i++){ //Loops through the opcode table, 36 elements
		if(strcmp(op_table[i].name, current_line) == 0){ //If there is a match in the opcode
			opFormat = op_table[i].format; //Store the current opcode's format into the opFormat
			return opFormat; //Returns that number
		}
		
		
	}
	return 0; //exits 
}