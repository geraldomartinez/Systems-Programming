//Geraldo Martinez
//gm979351

/*
This file contains the main function for this program. The purpose of this program
is to assemble assembly language code supplied by a file inputted by the user. The program
takes in two arguments, one of which is the file inputted by the user. The design 
strategy of the assembler is that of a two-pass assembler.

*/


//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

struct symbol *symbol_container; //declares a struct of symbol, which will contain all the symbols read from the file
extern int error_check; //calls to use the error_check variable from another file, indicating if there is an error or not

int main(int argc, char *argv[]){
	FILE *asmFILE; //Pointer to the file being read in (.asm file).
	char *filename_sym, *filename_obj, *filename_err; //Used to store the filenames of the files that will be written out.
	
	/* Checks to see if user inputted the correct amount of command line arguments of three.
	If not, prints an error message and exits the program. */
	if(argc != NUMBER_ARG){
		fprintf(stderr, "Invalid number of command line arguments.\n");
		exit(1);
	}
	
		/* Checks to see if  user inputted a file that is readable.
	If not, prints an error message and exits the program.*/
	if((asmFILE = fopen(argv[FILE_ARG], "r"))==NULL){
		fprintf(stderr, "Could not open the asm file for reading.\n");
		exit(1);
	}
	
	filename_sym = malloc(sizeof(argv[FILE_ARG])); //Allocates enough space to store the name of the file
	strcpy(filename_sym, argv[FILE_ARG]); //Copies the name of the inputted file into filename_sym
	filename_sym[strlen(filename_sym) - EXTENSION_LEN] = '\0'; //Removes the last four spots in the string array by setting it to the '\0' char
	strcat(filename_sym, ".sym"); //Sets the extension to the file accordingly. 
	
	
	//Opens the symbol file for writing. Prints error if unable to open
	 if ((symFILE = fopen(filename_sym, "w")) == NULL)  
	  {
		printf("Could not write to file.\n"); 
		exit(1);
	  }
	  
	filename_obj = malloc(sizeof(argv[FILE_ARG])); //Allocates enough space to store the name of the file.
	strcpy(filename_obj, argv[FILE_ARG]); //Copies the name of the inputted file into filename_obj
	filename_obj[strlen(filename_obj) - EXTENSION_LEN] = '\0'; //Removes the last four spots in the string array by setting it to the '\0' char
	strcat(filename_obj, ".obj"); //Sets the extension to the file accordingly. 
	
	//Opens the object file for writing. Prints error if unable to open
	if ((objFILE = fopen(filename_obj, "w")) == NULL)  
	  {
		printf("Could not write to file.\n"); 
		exit(1);
	  }
	  
	filename_err = malloc(sizeof(argv[FILE_ARG])); //Allocates enough space to store the name of the file.
	strcpy(filename_err, argv[FILE_ARG]); //Copies the name of the inputted file into filename_err
	filename_err[strlen(filename_err) - EXTENSION_LEN] = '\0'; //Removes the last four spots in the string array by setting it to the '\0' char
	strcat(filename_err, ".err"); //Sets the extension to the file accordingly. 
	
	//Opens the error file for writing. Prints error if unable to open.
	if ((errFILE = fopen(filename_err, "w")) == NULL)  
	  {
		printf("Could not write to file.\n"); 
		exit(1);
	  }
	
	pass_one(asmFILE); //Goes through the first pass, picking up symbol names.
	rewind(asmFILE); //Rewinds the input file to prepare for the second pass.
	pass_two(asmFILE); //Goes through the second pass, checking for remainding errors, if not outputing the object file.

	
	/*
	The following if statements check to see if there was an error during the 
	assembly process, then proceeds to remove files accordingly. 
	*/
	
	//If there is an error
	if (error_check == TRUE){
		remove(filename_obj); //Removes the object file.
		remove(filename_sym); //Removes the symbol file as well.
	}
	
	//If there was no error.
	if (error_check == FALSE){
		remove(filename_err); //removes the error file.
	}

	
return 0;
}