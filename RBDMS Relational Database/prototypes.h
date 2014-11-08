//Geraldo Martinez
//gm979351

/*
This file contains all of the prototypes used in the program for each of the functions used.
*/

int fileExist(const char *filename);
void nattr(char *rel_name);
int tuplen(char *rel_name);
void infattr(char *rel_name, char *attr_name);
int count(char *rel_name);
void project(char *rel_name, char *attr_name);
void select_fun(char *rel_name, char *attr_name, char *relop_name, char *value_name);