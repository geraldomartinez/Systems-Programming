//Geraldo Martinez
//gm979351

/*
This file contains all of the prototypes used in the program for each of the functions used.
*/


void pass_one(FILE *infile);
void pass_two(FILE *infile);
void initialize_table(char *label, int line_num, struct symbol *table_sample);
void multiple_symbol();
int opArguments_lookup(char *opcode, int line);
int opcode_number_lookup(char *current_line);
void symbol_lookup(char *symbol_name);
int LC_value_lookup(char *current_line);
char opFormat_lookup(char *current_line);

void jformat(int opcode_number, int target_register, 
int first_register, int jump_register, int immediate_register, int line);


void rformat(int opcode_number, int target_register, 
int first_register, int second_register, int shifts, int line);


void iformat(int opcode_number, int target_register, 
int first_register, int immediate_register, int line);