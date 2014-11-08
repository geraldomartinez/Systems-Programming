//Geraldo Martinez
//gm979351

/*
This file includes all of the functions used to compute the statistics of the inputted file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//The necessary header files needed for this file
#include "constants.h"
#include "struct_def.h"
#include "prototype.h"


/*
The function count takes in a node of type tree_node that returns the total number of nodes/strings
in the tree.
*/
int count(tree_node *tree){
	if (tree==NULL) //If the tree has no nodes, returns 0
		return 0;
	else {
		if (tree->left_child == NULL && tree->right_child ==NULL) //If the tree isn't empty, but both of the subtrees are, then returns a 1 for the root node.
			return 1;
		else
			return (1 + (count(tree->left_child) + count(tree->right_child))); //recursively computes the count of the right and left subtrees, adds them and then adds 1.
	}
}

/*
This function counts the nodes/strings on the left subtree of the tree. Takes in a parameter 
of type tree_node 
*/
int countLeft(tree_node *tree){
	if (tree==NULL) //If the tree is empty, returns 0 because there are no nodes in the left subtree
		return 0;
	else{
		if (tree->left_child==NULL) //If the left subtree is null, then also returns 0
			return 0;
		else
			return count(tree->left_child); //Calls on the count function which computes the # recursively. 
	}
}

/*
This function counts the nodes/strings on the right subtree of the tree. Takes in a parameter 
of type tree_node 
*/
int countRight(tree_node *tree){
	if (tree==NULL) //If the tree is empty, returns 0 because there are no nodes in the right subtree
		return 0;
	else{
		if (tree->right_child==NULL) //If the right subtree is null, then also returns 0
			return 0;
		else
			return count(tree->right_child); //Calls on the count function which computes the # recursively. 
	}
}

/*
The function leafCount computes the number of leaf nodes currently on the tree. It takes in 
a parameter of type tree_node that represents the pointer to the tree being passed on.
*/
int leafCount(tree_node *tree){
	if (tree == NULL) //If the tree is empty, there are no leaves in the tree so returns 0;
		return 0;
	if (tree->left_child == NULL && tree->right_child==NULL){ //If both subtrees are empty, returns 1 leaf representing the root node.
		return 1;
	}
	else
		return leafCount(tree->left_child) + leafCount(tree->right_child); //Recursively computes the leaves of each subtree, then adds them together to return results.
}

/*
The function treeHeight computes the number of largest number of links in the current tree. It takes in a
parameter of type tree_node that represents the pointer to the tree being passed on.
*/
int treeHeight(tree_node *tree){
	
	if (tree == NULL) //If the tree is empty, returns -1 because its computing the number of links instead of nodes in the tree.
		return NULL_TREE_HEIGHT;
	else
	{
		int left_height = treeHeight(tree->left_child); //recursively computes the height of the left subtree and stores it into a variable.
		int right_height = treeHeight(tree->right_child); //recursively computes the height of the right subtree and stores it into a variable.
		
		if (left_height > right_height) //Checks to see which subtree is larger.
			return left_height+1; //If the left subtree is larger then it adds 1 and returns the number.
		else return right_height+1; //If the right subtree is larger then it adds 1 and returns the number.
	}
	
}

/*
The function leftHeight computes the number of links of the height of the left subtree in the current tree. It takes in a parameter 
of type tree_node that represents the pointer to the tree being passed on.
*/

int leftHeight(tree_node *tree){

		int left_height = treeHeight(tree->left_child); //Calls on the treeHeight function to compute the height of the left subtree recursively then stores it in a variable.
		if (left_height == NULL_TREE_HEIGHT) //If the height returns the value of the tree being null, returns a 0 to represent the height of the subtree.
			return 0;
		else
			return left_height; //If the subtree isn't empty, then returns the computed value of the height.
		
}

/*
The function rightHeight computes the number of links of the height of the right subtree in the current tree. It takes in a parameter 
of type tree_node that represents the pointer to the tree being passed on.
*/
int rightHeight(tree_node *tree){



		int right_height = treeHeight(tree->right_child); //Calls on the treeHeight function to compute the height of the right subtree recursively then stores it in a variable.
		
		if (right_height == NULL_TREE_HEIGHT) //If the height returns the value of the tree being null, returns a 0 to represent the height of the subtree.
			return 0;
		else
			return right_height; //If the subtree isn't empty, then returns the computed value of the height.
}
