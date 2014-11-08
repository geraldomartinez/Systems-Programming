//Geraldo Martinez
//gm979351

/*
This file includes the struct definition of the tree. It sets up a tree_node 
of type struct consisting of a string array with a max length of 16 chars. It also
makes two tree_node pointers pointing to the left and right subtrees of this tree.
*/

//Including the constants.h header file that has the MAXLEN constant in it.
#include "constants.h"

typedef	struct tree_node {
	char string[MAXLEN+1];
	struct tree_node *left_child, *right_child;
	}tree_node;
