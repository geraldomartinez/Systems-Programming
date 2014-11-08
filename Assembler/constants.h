
//Geraldo Martinez
//gm979351

/*
This file contains the constant definitions used throughout the program.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *symFILE, *objFILE, *errFILE; //Declaration of the necessary pointer files to be outputted
struct symbol *head; //Declares a symbol struct called head to be used to manuever through the linked list.

#define NUMBER_ARG 2 //Number of command line arguments that the program takes in
#define BUFFER_MAX 81 //Max number of characters in each line in the inputted file
#define FILE_ARG 1 //The position of the file in the command line arguments
#define MAX_OPCODE_NAME 5 //The max length name of an opcode from the symbol table
#define EXTENSION_LEN 4 //Number of characters in the .asm file extension.
#define MAX_LABEL_LENGTH 10 //The longest size of a label is of 9 characters
#define FALSE 0 //Used for boolean purposes, represents a FALSE value.
#define TRUE 1 //Used for boolean purposes, represents a TRUE value.
#define THREE_ARGS 3 //Represents the number of arguments in some opcode values.
#define TWO_ARGS 2 //Represents the number of arguments in some opcode values.
#define ONE_ARG 1 //Represents the number of arguments in some opcode values.
#define NO_ARGS 0 //Represents the number of arguments in some opcode values.
#define EMPTY_MASK 0x0000 //Empty mask used for bit shifting
#define opcode_val 26 //Amount of bytes needed to move the opcode in any format
#define	register_source	21 //Amount of bytes needed to move in the first register source
#define register_source_two 16 //Amount of bytes needed to move in the second register source
#define register_target 11 //The amount of bytes needed to shift for the target register
#define shift_amount 6 //The amount needed to shift
#define MASK_complement 0x0000FFFF //Used in the I-format to deal wit 2s complement