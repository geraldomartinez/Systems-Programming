//Geraldo Martinez
//gm979351

/* This file contains the main function for this program. The program takes in 3 parameters
including the executable. This program takes in information from an inputted file and then writes
statistical information to an output file provided by the user.*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "struct_def.h"
#include "constants.h"
#include "prototype.h"

int main(int argc, char *argv[]){
	FILE *inf, *output; //Declarations of both inputs and outputs file pointers.
	char string[MAXLEN]; //Declaration of a string array in which the data from the input file will be stored in.
	int stringCount; //Stores the number amount of strings in the file.
	int leaf_count; //Stores the total number of leaves in the tree.
	int height_count; //Stores the height of the tree.
	int left_strings; //Stores the number of strings in the left subtree of the tree.
	int right_strings; //Stores the number of strings in the right subtree of the tree.
	int leftHeight_count; //Stores the height of the left subtree of the tree.
	int rightHeight_count; //Stores the height of the right subtree of the tree.
	tree_node *temp; //Declares the node that will be representing the tree.
	temp = NULL; //Sets the tree to NULL.
	
	/* Checks to see if user inputted the correct amount of command line arguments of three.
	If not, prints an error message and exits the program. */
	if(argc != NUMBER_ARG){
		fprintf(stderr, "Invalid number of command line arguments.\n");
		exit(1);
	}
	
	/* Checks to see if  user inputted a file that is readable.
	If not, prints an error message and exits the program.*/
	if((inf = fopen(argv[FILE_ARG], "r"))==NULL){
		fprintf(stderr, "Could not open the file: %s. for reading\n", argv[FILE_ARG]);
		exit(1);
	}
	
	/* Checks to see if user inputted a file that is writeable.
	If not, prints an error message and exits the program. */
	if((output = fopen(argv[FILE_ARG_TWO], "w"))==NULL){
		fprintf(stderr, "Could not open the file: %s. for writing\n", argv[FILE_ARG]);
		exit(1);
	}
	
	
	/*
	Checks to see that the inputted file isn't empty, and if it isn't it loops through it
	until it reaches the end of the file.
	*/
	
	if( inf != NULL ){
	
	  while ( !feof(inf ) ){
	    //memset(string, '\0', sizeof( string) );
		fscanf (inf, "%s", string); //For each loop, it scans the current word and stores it in the string variable.
		temp = insertNode(temp, string); //Calls the insertNode function to push that string into the binary tree.
	  } 
	}
	stringCount=count(temp); //Calls the function count which calculates the number of strings in the tree, then stores it into stringCount.
	leaf_count = leafCount(temp); //Calls the function leafCount on the tree which computes the number of leaves and stores it into left_count.
	height_count = treeHeight(temp); //Calls the treeHeight function on the tree and then computes and stores the height of tree into height_count.
	left_strings = countLeft(temp); //Calls the countLEft function on the tree which computes and stores the number of left subtree strings.
	right_strings = countRight(temp); //Calls the countRight function on the tree which computes and stores the number of right subtree strings.
	leftHeight_count = leftHeight(temp); //Calls the leftHeight function on the tree which computes and stores the height of left tree.
	rightHeight_count = rightHeight(temp); //Calls the leftHeight function on the tree which computes and stores the height of left tree

	fprintf(output, "No. of strings in the input file	= %d\n", stringCount); //Prints the stringCount into the output file
	fprintf(output, "Height of the binary search tree	= %d\n", height_count); //Prints the height_count into the output file
	fprintf(output, "Number of leaves in the tree		= %d\n", leaf_count); //Prints the leaf_count into the output file
	fprintf(output, "Height of the left subtree of root	= %d\n", leftHeight_count); //Prints the leftHeight_count into the output file
	fprintf(output, "No. of strings in the left subtree	= %d\n", left_strings); //Prints the left_strings into the output file
	fprintf(output, "Height of the right subtree of root	= %d\n", rightHeight_count); //Prints the rightHeight into the output file
	fprintf(output, "No. of strings in the right subtree	= %d\n", right_strings); //Prints the right_strings into the output file/
	
	/*Checks to see if input_file can be close.
	If not, prints an error message and exits the program. */
	if (fclose(inf)==EOF){
		fprintf(stderr, "Could not close the file: %s.\n", argv[FILE_ARG]);
		exit(1);
	}
	
	/*Checks to see if input_file can be close.
	If not, prints an error message and exits the program. */
	if (fclose(output)==EOF){
		fprintf(stderr, "Could not close the file: %s.\n", argv[FILE_ARG]);
		exit(1);
	}
		
	return 0;
}


