//Geraldo Martinez
//gm979351

/*
This file contains the function select_fun. This function takes in 4 parameters 
representing the name of a relation, attribute, a relop and a value to project 
to stdout. 
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

void select_fun(char *rel_name, char *attr_name, char *relop_name, char *value_name){
	char filename[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the binary file.
	char filename_two[FILENAME_SIZE]; //Declares a char variable that will be used to store the name of the schema file.
	int schema_len, boolean_value=0, tuple_count, total_length, tuple_size, second_boolean=0; //Integer variables used to store certain data about the relation
	int totcr, i=0, byte_len, x=0; //Other variables used to store data being read in, as well as max size.
	FILE *file, *file_two; //FILE variable that will point to the file of the relation specified by the parameter.
	char first_attr[ATTRIBUTE_SIZE], second_attr[ATTRIBUTE_SIZE]; //Variables holding the name and type of certain attributes.
	char *buffer; //Declares a char variable that will be used to read in the contents of the binary file.
//	char *storage[101];
	int boolean_test = 0, boolean_check=0, boolean_t=0; //Boolean variables used to manipulate error messages.
	char hey[3]="\""; //Variable holding a quotation mark used to remove it from the value_name.
	char *new_value_name; //Variable that will be used to store the contents of the value_name after calling strtok on it

	
	strcpy(filename, rel_name); //Copies the name of the relation onto the filename variable.
	strcat(filename, ".dat"); //Copies the .dat extension onto the filename variable.
	strcpy(filename_two, rel_name); //Copies the name of the relation onto the filename_two variable.
	strcat(filename_two, ".sch"); //Copies the .sch extension onto the filename_two variable.
	
	/* This IF statement tests wether the file exists in the current directory or not, if it does, the function moves onto
	the else part, if it doesn't exists, it prints out an error message specifying an invalid relation. */

	
	if (fileExist(filename)==0){
		fprintf(stderr, "Error: Invalid relation -- %s\n\n", rel_name);
	}
	
		//If the file exists, do the following.
	else{
		/* Checks to see if the relation file can be opened for reading, if not prints out an
		error message and exits the program.
		*/
		if((file = fopen(filename, "rb"))==NULL){
		fprintf(stderr, "Could not open the %s binary file for reading.\n", rel_name);
		exit(1);
		}
		
		tuple_size = tuplen(rel_name); //Stores the length of each tuple of the relation into tuple_size
		tuple_count = count(rel_name); //Stores the number of tuples into tuple_count
		file_two = fopen(filename_two, "r"); //Opens the schema file for reading.
		total_length = tuple_size * tuple_count; //Stores the total relation size in bytes into total_length
		buffer = (char *)malloc(sizeof(char)*total_length); //Allocates space for the buffer with the total relation size.

		new_value_name = strtok(value_name, hey); //Strips the quotations from the string 
		for(x=0; x<tuple_count; x++){ //This loops until the number of tuples or rows has been reached.
			fscanf(file_two, "%d", &schema_len); //Scans the first digit of the schema file.
				while (i<schema_len){ //Loops for each category or attribute that the relation has.
					fscanf(file_two, "%s%s%d", first_attr, second_attr, &byte_len); //Scans the attribute name, type and length
					
					
					if(strcmp(second_attr, "S")==0){ //If the attribute type is of String, goes into the statement.
						fread((void *) buffer, sizeof(char), byte_len, file); //Reads x amount of data into the buffer, depending on the byte_len
						}
					if(strcmp(second_attr, "I")==0){ //If the attribute type is of Integer, goes into the statement.
						fread((void *) &totcr, sizeof(int), 1, file); //Reads one integer into totcr.					
					}
					
					if(strcmp(attr_name, first_attr)==0){ //Checks if current attribute name matches inputted.
						boolean_value = 1; //Sets the value to one.
						
							if(strcmp(second_attr, "I")==0){ //Checks if current attribute is of type Integer. 
								
								if(strcmp(relop_name, "==")==0){ //Checks if the relop is ==
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets the value to 1 
									boolean_check=0; //Resets the value of boolean_check
									if(atoi(value_name) == totcr) //Converts the inputted string to integer and checks for a match
									{
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								
								if(strcmp(relop_name, "!=")==0){ //Checks if relop is !=
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets second_boolean to one.
									boolean_check=0; //Resets value of boolean_test
									if(totcr != atoi(value_name)){ //Converts the inputted string to integer and checks for a match
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								if(strcmp(relop_name, "<=")==0){ //Checks if relop is <=
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets the value to 1 
									boolean_check=0; //Resets value of boolean_test
									if(totcr <= atoi(value_name)){ //Converts the inputted string to integer and checks for a match
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								if(strcmp(relop_name, ">=")==0){ //Checks if relop is >=
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets the value to 1 
									boolean_check=0; //Resets value of boolean_test
									if(totcr >= atoi(value_name)){ //Converts the inputted string to integer and checks for a match
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								if(strcmp(relop_name, "<")==0){ //Checks if relop is <
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets the value to 1 
									boolean_check=0; //Resets value of boolean_test
									if(totcr < atoi(value_name)){ //Converts the inputted string to integer and checks for a match
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								if(strcmp(relop_name, ">")==0){ //Checks if relop is >
									boolean_test = 0; //Resets value of boolean_test
									second_boolean = 1; //Sets the value to 1 
									boolean_check=0; //Resets value of boolean_test
									if(totcr > atoi(value_name)){ //Converts the inputted string to integer and checks for a match
										boolean_test = 1; //Sets the boolean_test to 1.
									}
									else{
										boolean_check = 1; //Else sets the boolean_check to one/
									}
								}
								
						}
						
						if(strcmp(second_attr, "S")==0){ //Checks to see if current attribute is of type string
							boolean_test = 0; //Sets boolean_test to 0
							if(strcmp(relop_name, "==")==0){ //Checks to see if relop is ==
									second_boolean = 1; //Sets second_boolean to 1.
									if(strcmp(new_value_name, buffer)==0){ //Checks to see if the buffer is the same as the string entered.
										boolean_test = 1; //Sets boolean_test to one.
									}
									else{
										boolean_check=1; //Sets boolean_check to one.
									}
								}
								if(strcmp(relop_name, "!=")==0){ //Checks if relop is !=
									second_boolean = 1; //Sets second_boolean to 1.
										if(strcmp(new_value_name, buffer)!=0){ //Checks to see if new_value_name isn't the same as buffer
											boolean_test=1; //Sets boolean_test to 1
										}
										else{
											boolean_check = 1; //Sets boolean_check to 1.
											}
								}
								else{
									boolean_t = 1; //Sets boolean_t to 1.
								}
								
						}
					
					}
					
					if(boolean_test == 1){ //Checks to see if boolean_test is one.
						if(strcmp(second_attr, "S")==0){ //Checks to see if current attribute is of type string
							printf("%s\t", buffer); //Prints out the data in the buffer
							}
					
						if(strcmp(second_attr, "I")==0){ //Checks to see if current attribute is of type Integer
							printf("%d\t", totcr); //Prints out the data in totcr
							}
						
				}
					i++; //Increments the counter of the while loop
				}
			printf("\n"); //Prints a newline character that splits each tuple.
			i=0; //After the while loop goes through entire schema and a tuple in the binary file, resets the counter for a new tuple.
			rewind(file_two); //Resets the position of the schema file for a new read.
		}
		printf("\n"); //Prints a newline character.
		
		if (boolean_value == 0 ){ //If boolean value is still 0 at this point, then no attribute of that name was found in the schema file.
				printf("Error: Invalid attribute -- %s\n\n", attr_name);
				return;
			}
		if (boolean_check == 1){ //If boolean_check is set to one, then there isn't any tuples that satisfy the condition
			printf("No tuples satisfy the specified condition.\n\n"); 
			return;
		}
		if ((second_boolean == 0)||(boolean_t == 1)){ //if second_boolean is still 0 at this point, then no value for that type of attribute was found.
			printf("Error: Wrong type of value for attribute %s\n\n", attr_name);
		}
		
		
		
		
		
		
		/* Attempts to close the binary file, if it is unable to close it prints out an error message.
		*/
		if (fclose(file)==EOF){
			fprintf(stderr, "Could not close the file: %s.\n", filename);
			exit(1);
		}
	}
}