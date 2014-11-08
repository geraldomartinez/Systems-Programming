
//Geraldo Martinez
//gm979351

/*
This file contains the opcode symbol table. Declares a new opcode table array 
and stores 36 symbols in the table, specifying everything from opcode number, 
arguments, name of opcode, and format.
*/

struct opcode op_table[] = {
  {0,0,"hlt",'R'}, {1,3,"add",'R'}, {2,3,"sub",'R'},
  {3,3,"mul",'R'},
  {4,3,"div",'R'},
  {5,3,"mod",'R'},
  {6,2,"move",'R'},
  {7,3,"and",'R'},
  {8,3,"or",'R'},
  {9,3,"xor",'R'},
  {10,2,"com",'R'},
  {11,3,"sll",'R'},
  {12,3,"srl",'R'},
  {13,3,"sra",'R'},
  {14,1,"jr",'R'},
  {15,1,"rdr",'R'},
  {16,1,"prr",'R'},
  {17,1,"prh",'R'},
  {18,2,"li",'I'},
  {19,3,"addi",'I'},
  {20,3,"subi",'I'},
  {21,3,"muli",'I'},
  {22,3,"divi",'I'},
  {23,3,"modi",'I'},
  {24,2,"lwb",'I'},
  {25,2,"swb",'I'},
  {26,2,"lwa",'J'},
  {27,2,"swa",'J'},
  {28,1,"j",'J'},
  {29,1,"jal",'J'},
  {30,3,"jeq",'J'},
  {31,3,"jne",'J'},
  {32,3,"jlt",'J'},
  {33,3,"jle",'J'},
  {34,3,"jgt",'J'},
  {35,3,"jge",'J'},
};

	int table_len = sizeof(op_table) / sizeof(op_table[0]); //Calculates the size of the array and stores it into this variable.