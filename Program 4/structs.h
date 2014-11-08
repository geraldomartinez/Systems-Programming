
//Geraldo Martinez
//gm979351

/*
This file contains all of the struct definitions necessary and used throughout
this program. The opcode struct is used to build the opcode symbol table while
the symbol struct is used to represent a linked list of symbols.
*/


struct opcode {
	int opcode_number; //The opcode value
	int numArgs; //Number of arguments in this opcode
	char name[MAX_OPCODE_NAME]; //Name of the opcode 
	char format; //Opcode format, either R, I or J
};

struct symbol {
	char name[MAX_LABEL_LENGTH]; //stores the name of a label.
	int LC_value; //Stores the LC value, or the number of lines processed
	struct symbol *next; //Pointer to the next label.
};