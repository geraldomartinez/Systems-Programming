//Geraldo Martinez
//gm979351

/* This file contains the first part (part a) of project 5. All of the necessary
functions and constants are all in this file along with the main function. This program
takes in either two or three parameter, the third being optional and only "-s" is allowed. 
The program lists the hidden files in a pathname specified by the user in the input, the program
also lists the size in bytes as well as the time it was last modified.
*/


//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>


//Constants declared to use in this program
#define DIR_MAX_LEN 255 //Max length of a directory name
#define NO_FLAG_ARGS 2 //Number of arguments if there are no flags specified
#define FLAGS_ARG 3 //Number of arguments if there are flags specified

#define FLAG_POSITION 2 //Position of the flags in the command line args
#define PATHNAME_POSITION 1 //Position of the pathname in the command line
#define MAX_DIR_LEN 255 //max name of a hidden file
#define MAX_TIME_LEN 50 //Number of chars that the time will take up


/*This function declares the struct of the linked list used for the -s flag in order 
to easily sort the information gathered from the input file. The linked list structure 
is composed of two strings and a integer.
*/
struct sorted_list
{
	char name[MAX_DIR_LEN]; //Represents the name of the hidden file
    int size; //Stores the size of the hidden file
	char m_time[MAX_TIME_LEN]; //Stores the information of the last time it was modified
    struct sorted_list *next; //Pointer to the next node.
}*head;
/*
The function add is used to add nodes into the linked list structure, if the 
list is empty, it assigns the first node accordingly. 
*/
void add(char *name_in, int size_in, char *time_in){
	struct sorted_list *temp; //Temp node used to add new nodes
	 temp=(struct sorted_list *)malloc(sizeof(struct sorted_list)); //allocates enough space for the linked list
	 
	 strcpy(temp->name, name_in); //Copies the name of the file into the right field in the linked list
	 temp->size = size_in; //Copies the size of the file into the right field in the linked list
	 strcpy(temp->m_time, time_in); //Copies the time info of the file into the right field in the linked list
	 
	 //If the list is empty
	 if(head == NULL){
	 head = temp; //assign the contents of temp into the head
	 head->next=NULL; //point to the next node
	 }
	 
	 //if it isn't empty
	 else{
	 temp->next=head; //assign the head into the temp's next node
	 head=temp; //assign the temp into the head
	 
	 }

}

/*
The display function simply prints the linked list, it takes a struct
sorted_list and prints all of the info
*/
void display(struct sorted_list *r){
	r= head; //points the struct to the head
	if(r==NULL){ //If the list is empty, print notthing
		return;
	}
		while(r!=NULL){ //Loops through each node, printing the data accordingly.
		printf("%s %d %s", r->name, r->size, r->m_time);
		r=r->next; //points to the next node
	}
}


/*
The sort function takes in a linked list and sorts the the data from
smallest to highest according to byte size of each node.
*/

void sort(struct sorted_list *r){
	struct sorted_list *temp;
	int temp_num; //will temporarily store the file size
	char temp_dir[MAX_DIR_LEN]; //will temporarily store the file name
	char temp_time[MAX_TIME_LEN]; //will temporarily store the file time info
	r=head; //points inputted list to the head or start
	temp = r->next; //points the temp to the node after the inputted list
	if(r== NULL){ //if the list is empty, do nothing.
		return;
	}
	
	/* Small bubble sort implementation*/
	while(r!=NULL){ //loops while there are nodes
		while (temp!= NULL){ //loops while there are nodes
			if((r->size) > (temp->size)){ //if the data before the next is bigger than it
				
				//Re-arranges the names accordingly.
				strcpy(temp_dir, temp-> name);
				strcpy(temp->name, r->name);
				strcpy(r->name, temp_dir);
				//Re-arranges the size accordingly.
				temp_num = temp-> size;
				temp->size = r->size;
				r->size = temp_num;
				//Re-arranges the time string accordingly.
				strcpy(temp_time, temp-> m_time);
				strcpy(temp->m_time, r->m_time);
				strcpy(r->m_time, temp_time);
			}
			else{
			temp = temp->next; //points to the next node
			r=r->next; //points to the next node
			}
		}
	r=r->next; //points to the next node
	}
}



//The main function.

int main(int argc, char *argv[]){
	char pathname[DIR_MAX_LEN]; //Stores the pathname inputted by user
	struct stat statbuf; //declares the stat struct
	struct dirent *d; //declares the dirent struct
	struct sorted_list *list; //declares the linked list
	DIR *directory; //declares the directory that will hold the pathname
	int change_dir; //will store the return value of chdir
	
	if((argc == NO_FLAG_ARGS)){ //If the user entered two arguments
		strcpy(pathname, argv[PATHNAME_POSITION]); //Copies the name of the path into pathname
		//Attempts to open the directory specified by the pathname, if it fails it prints out an error msg.
		if((directory = opendir(argv[PATHNAME_POSITION])) == NULL){
			fprintf(stderr, "The directory %s cannot be opened.\n", pathname);
			exit(1);
		}
		else{
			
			//Loops through while it reads through the current directory
			while ((d = readdir(directory)) != NULL){
				
				//Checks to see if there are files starting with a '.' and makes sure
				//to skip files that just contain . and ..
				if((d->d_name[0] == '.') && (strcmp (d->d_name, ".") != 0) &&
				(strcmp (d->d_name, "..") != 0) ){
	
					change_dir = chdir(argv[PATHNAME_POSITION]); //changes the directory for each loop

					if(stat(d->d_name, &statbuf)==0){ //Calls the stat function on the directory and checks to see if it doesnt fail
				
						printf("%s %d %s", d->d_name, statbuf.st_size, ctime(&statbuf.st_mtime)); //prints out the information accordingly.
						
					}
			
				}
			}
		
		
		closedir(directory); //Closes the directory
		}
		
	}
	else if((argc == FLAGS_ARG)){ //If there are three args
		
		
		if(strcmp(argv[FLAG_POSITION],"-s")==0){ //Checks to see if the flag is -s
			
			strcpy(pathname, argv[PATHNAME_POSITION]); //Copies the name of the path into pathname
			
		//Attempts to open the directory specified by the pathname, if it fails it prints out an error msg.
			if((directory = opendir(argv[PATHNAME_POSITION])) == NULL){
			fprintf(stderr, "The directory %s cannot be opened.\n", pathname);
			exit(1);
			}
			
			//if firectory opens
			else{
			
			//Loops through while it reads through the current directory
			while ((d = readdir(directory)) != NULL){
				//Checks to see if there are files starting with a '.' and makes sure
				//to skip files that just contain . and ..
				if((d->d_name[0] == '.') && (strcmp (d->d_name, ".") != 0) &&
				(strcmp (d->d_name, "..") != 0) ){
		
					change_dir = chdir(argv[PATHNAME_POSITION]); //changes the directory for each loop

					if(stat(d->d_name, &statbuf)==0){ //Calls the stat function on the directory and checks to see if it doesnt fail
							add(d->d_name, statbuf.st_size, ctime(&statbuf.st_mtime)); //Calls on the add function to add to the current info the linked list
							sort(list); //Sorts the nodes accordingly each time the data is added
						
					}
			
				}
			}

			display(list); //Prints out the list
			closedir(directory); //Closes the directory
			}
		}
		else{ //THe specified flag wasn't -s
			fprintf(stderr, "Wrong flag inputted.\n"); //Error message for wrong flag inputted.
			exit(1);
		}
	}
	else{ //Wrong valid of command line arguments
		fprintf(stderr, "Invalid number of command line arguments.\n"); //Error message if user inputs incorrect number of command line arguments.
		exit(1);
	}
	
return 0;

}