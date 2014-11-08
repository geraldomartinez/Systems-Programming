//Geraldo Martinez
//gm979351

/*
This file contains the insert function called insertNode. This function is responsible
for passing the strings read from the input file into the binary tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files needed for this function
#include "struct_def.h"
#include "constants.h"
#include "prototype.h"

/*
The function insertNode is of type tree_node and takes in two parameters. One of the parameters
is a pointer variable of type tree_node and the second is of type char array which represents 
the current word being passed into the tree.
*/

tree_node *insertNode(tree_node *t_node, char word[]){

	
	
	//If the tree is empty, assigns root node
	if(t_node==NULL)
    {
        
		tree_node *new_item = malloc( sizeof(struct tree_node)); //Allocates space for the tree
		strcpy(new_item->string, word); //Copies the first word in the tree and makes it the root node
		new_item->left_child = new_item->right_child = NULL; //Sets the left and right subtree to NULL
		return new_item; //Returns the tree.
    }
	
	//basic idea using recursion and strcmp
    else
    {
        if(strcmp(word, t_node->string)<0) //If the current word being passed to the tree comes before the current one in the tree, it goes to the right subtree.
        {
            t_node->left_child=insertNode(t_node->left_child, word); //Puts the current string in the left subtree, recursively.
            
        }
        else if(strcmp(word, t_node->string)>0) //If the current word being passed to the tree comes after the current one in the tree, it goes to the left subtree.
        {
            t_node->right_child=insertNode(t_node->right_child, word); //Puts the current string in the right subtree, recursively.
            
        }
    }	
	return t_node; //Returns the tree
}
