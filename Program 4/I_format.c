//Geraldo Martinez
//gm979351

/*
This file contains the function I_format. The use of this format 
is to appropiately shift bytes into place when dealing with an opcode
format of type I, according to the opcode table. The function takes in
five integers representing the opcode number, the target register, the first source
register, the immediate register, and the line.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Header files needed in this file.
#include "constants.h"


void iformat(int opcode_number, int target_register, 
int first_register, int immediate_register, int line)
{
  int output = 0; //Variable used to store the hex values
 
  output & EMPTY_MASK; //ANDS the output with the empty mask

  output |= (opcode_number << opcode_val); //Shifts the opcode number 26 spots to the left and ORS it and stores it into output
  output |= (first_register << register_source); //Shifts the first register 21 spots to the left to store the values accordingly next to the opcode
  output |= (target_register << register_source_two); //Repeats the shifting and ORing, this time 11 spots to the left 
  output |= (MASK_complement & immediate_register); //Finally, it ANDS immediate_register with the MASK_complement and stores it into the output

fprintf(objFILE, "%X\t%X \n",line, output); //Writes the output and current line into the objFILE.
}
