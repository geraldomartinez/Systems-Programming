//Geraldo Martinez
//gm979351

/*
This file contains the function R_format. The use of this format 
is to appropiately shift bytes into place when dealing with an opcode
format of type R, according to the opcode table. The function takes in
six  integers representing the opcode number, the target register, the first source
register, the jump_register, the immediate_register and the line.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"

void rformat(int opcode_number, int target_register, 
int first_register, int second_register, int unused, int line)
{
  int output = 0;//Used to store the hex values

  output & EMPTY_MASK;	//Clears the contents of the output

  output |= (opcode_number << opcode_val); //Shifts the opcode number 26 times over to the left
  output |= (first_register << register_source); //Shifts the first register 21 spots to the left to store the values accordingly next to the opcode
  output |= (second_register << register_source_two); //Uses the second register's input and shifts it 16 spots to the left.
  output |= (target_register << register_target); //Repeats the shifting and ORing, this time 11 spots to the left 
  output |= (unused << shift_amount); //Shifts the final amount 6 times into the un-used.


fprintf(objFILE, "%X\t%X \n",line, output); //Prints the hex values into the object file
}