//Geraldo Martinez
//gm979351

/* This file contains the main function for this program. The program takes in 3 parameters including 
the executable. This program implement some query operations on a relational database. It reads 
commands from a command file inputted by the user and the program returns results depending on the
specified query.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

int main(int argc, char *argv[]){
	FILE *configfile, *queryfile; //Declaration of FILE variables used to manipulate inputted files.
	char command[COMMAND_SIZE], relation_name[RELATION_SIZE], 
	attribute_name[ATTRIBUTE_SIZE], relop[COMMAND_SIZE], value[COMMAND_SIZE]; /*Declares the necessary 
	char arrays that will store the strings of each command being read in from the queryfile. */
	int attr_size; //Used to store the length of bytes of each tuple in the specified relation.
	int tuple_count; //Used to store the number of tuples in the specified relation.

	
	
	/* Checks to see if user inputted the correct amount of command line arguments of three.
	If not, prints an error message and exits the program. */
	if(argc != NUMBER_ARG){
		fprintf(stderr, "Invalid number of command line arguments.\n");
		exit(1);
	}
	
	/* Checks to see if  user inputted a file that is readable.
	If not, prints an error message and exits the program.*/
	if((configfile = fopen(argv[FILE_ARG], "r"))==NULL){
		fprintf(stderr, "Could not open the config file for reading.\n");
		exit(1);
	}
	
	/* Checks to see if user inputted a file that is writeable.
	If not, prints an error message and exits the program. */
	if((queryfile = fopen(argv[FILE_ARG_TWO], "r"))==NULL){
		fprintf(stderr, "Could not open the query file for reading.\n");
		exit(1);
	}
	
	
	
	
//	fscanf(configfile, "%d", &relation_number);
	/*
	relations[relation_number];
	
	for (i = 0; i < relation_number; i++)
	{
		fscanf(configfile, "%s", relation_name);
		//relations[i][0] = relation_name;
		strcpy(relations[i], relation_name);
		printf("%d\n", i);
		printf("%s\n", relations[i]);
	}
	
	//relations[0][0] = "Students";
	//relations[1][0] = "Courses";
	printf("%s\n", relations[0]);
	printf("%s\n", relations[1]);	*/
	
	
	
	

	while ( fscanf(queryfile, "%s", command) != EOF){ //Scans the query file one string at a time, until the EOF.
		if(strcmp(command, "quit")==0){ //If the current string is of quit, then exits the program.
			printf("You entered quit.\n"); //Prints exit message.
			exit(1); //Exits the programs.
		}		
			else if(strcmp(command, "nattr")==0){ //If the current string is of nattr, enters if statement.

				fscanf(queryfile, "%s", relation_name); //Scans the next word after the command for a relation name. 
				nattr(relation_name); //Calls the function on the relation.
			}
			
			else if(strcmp(command, "tuplen")==0){ //If the current string is of tuplen, enters if statement.

				fscanf(queryfile, "%s", relation_name); //Scans the next word after the command for a relation name.
				attr_size= tuplen(relation_name); //Assigns the return type of tuplen into attr_size, holding a number.
				
				if (attr_size != 0){ //If attr_size is not 0, then print the size of each tuple.
				printf("%d\n\n", attr_size); //Prints out the size.
				}
			}
			
			else if(strcmp(command, "infattr")==0){ //If the current string is of infattr, enters if statement.
				/* Scans the next two word after the command for a relation name and attribute name*/
				fscanf(queryfile, "%s", relation_name);
				fscanf(queryfile, "%s", attribute_name);
				
				infattr(relation_name, attribute_name); //Calls on the function infattr on the scanned words.
			}
			
			else if(strcmp(command, "count")==0){ //If the current string is of count, enters if statement.

				fscanf(queryfile, "%s", relation_name); //Scans the next word after the command for a relation name.
				tuple_count = count(relation_name); //Stores the return type of count into tuple_count.
				
				if (tuple_count != 0){ //If tuple_count is not zero, print out the number of tuples
				printf("%d\n\n", tuple_count); //Prints out the number.
				}
			}
			
			else if(strcmp(command, "project")==0){ //If the current string is of project, enters if statement.
				/* Scans the next two word after the command for a relation name and attribute name*/
				fscanf(queryfile, "%s", relation_name);
				fscanf(queryfile, "%s", attribute_name);
				project(relation_name, attribute_name); //Calls project on the relation name and attribute name scanned.
			}
			
			else if(strcmp(command, "select")==0){
			//	printf("You entered select.\n");
			/* Scans the next four words after the command for a relation, attribute, relop and a value name.*/
				fscanf(queryfile, "%s", relation_name);
				fscanf(queryfile, "%s", attribute_name);
				fscanf(queryfile, "%s", relop);
				fscanf(queryfile, "%s", value);
				
				select_fun(relation_name, attribute_name, relop, value); //Calls the select_fun command on this.
			}

	}
	
	/*Checks to see if input_file can be close.
	If not, prints an error message and exits the program. */
	if (fclose(configfile)==EOF){
		fprintf(stderr, "Could not close the file: %s.\n", argv[FILE_ARG]);
		exit(1);
	}
	/*Checks to see if input_file can be close.
	If not, prints an error message and exits the program. */
	if (fclose(queryfile)==EOF){
		fprintf(stderr, "Could not close the file: %s.\n", argv[FILE_ARG_TWO]);
		exit(1);
	}
	
	
return 0;
}
