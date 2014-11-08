//Geraldo Martinez
//gm979351

/*
This file includes the function fileExist. The role of this function
is to test wether a specified file exists in the current directory or not.
The function takes in a parameter of type char that tests whether the file name
exists, if it does it returns a nonzero value, if not it returns a zero.
The function uses the stat function from the sys/stat.h library in c.
*/

//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//Header files needed in this file.
#include "constants.h"
#include "prototypes.h"

int fileExist(const char *filename) {
    struct stat buff; //declares a variable of type struct to pass onto the stat function.
    int result = stat(filename, &buff); //Calls on the stat function and stores the return value onto result.
    return result == 0; //returns a zero if file doesn't exist
}