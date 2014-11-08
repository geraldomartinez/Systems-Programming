//Geraldo Martinez
//gm979351

/*
This file contains the function J_format. The use of this format 
is to appropiately shift bytes into place when dealing with an opcode
format of type J, according to the opcode table. The function takes in
six  integers representing the opcode number, the target register, the first source
register, the jump_register, the immediate_register and the line.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"

void jformat(int opcode_number, int target_register, 
int first_register, int jump_register, int immediate_register, int line)
{
  int output = 0;  //Used to store the output
  output & EMPTY_MASK; //Ensures the contents of the output is empty

  output |= (opcode_number << opcode_val); //Shifts the opcode number 26 times over to the left
  output |= (first_register << register_source);	//Shifts the first register next to the opcode number, 21 spots
  output |= (target_register << register_source_two); //Shifts the target register to the left 16 times
  output |= jump_register; //Stores the contents of the jump_register into the last 16 spots, the address


fprintf(objFILE, "%X\t%X \n",line, output); //Prints the hex values into the object file
}