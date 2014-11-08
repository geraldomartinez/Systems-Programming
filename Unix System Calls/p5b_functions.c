//Geraldo Martinez
//gm979351

/*
This file contains all of the necessary functions that make the second part
of project 5 work. It also includes struct and linked list definitions as well as
different types of functions that deals with linked lists.
*/


//Below are the necessary files and libraries needed for this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//Constants declared to use in this program

#define NON_FILE_ARGS 3 //number of arguments that aren't files
#define ARCHIVE_POSITION 2 //Possible archive position
#define TRUE 1 //Boolean value equal to true
#define FALSE 0 //Boolean value representing false
#define MAX_FILE_SIZE 256 //Max filename length

extern char **my_argv; //Accesses the global variables from the main function
extern int my_argc; //Accesses the global variables from the main function

/*This struct definition declares the struct of the linked list used to store 
the information about each file used in the -p flag. The linked list will be later
used to display these contents
*/
struct file_list
{
	char *name; //Stores file name
	int byte_size; //Stores file byte size
	struct file_list *next; //Pointer to the next node on the list
}*head; //Global variable head

/*
The function add is used to add nodes into the linked list structure, if the 
list is empty, it assigns the first node accordingly. 
*/
void add(char *name_in, int size_in){
	struct file_list *temp; //Temp node used to add new nodes
	struct file_list *temp2; //Other temp node used to loop through list
	 temp=(struct file_list *)malloc(sizeof(struct file_list)); //allocates enough space for the linked list
	 
	 strcpy(temp->name, name_in); //Copies the name of the file into the right field in the linked list
	 temp->byte_size = size_in; //Copies the size of the file into the right field in the linked list
	 temp2=head; //Assigns head to temp2
	//If the list is empty
	 if(head == NULL){
	 head = temp; //assign the contents of temp into the head
	 head->next=NULL; //point to the next node
	 }
	 //If it isn't empty
	 else{
	   while(temp2->next!=NULL){ //Loop until there are no more nodes
	     temp2 = temp2->next; //Shifts to the next node
	   }
	   temp2->next = temp; //Assigns the next node to temp's data
	 
	 }
}

/*
return_byte takes in a linked list and a integer, and goes into 
and returns an integer on the current node representing the number of bytes in a file.
*/

int return_byte(struct file_list *r, int len){
	int num; //Stores the byte size of the file
	int i; //loop counter
	r=head; //Assigns the list to the head global
	
	//If the list is empty return 0
	if(r == NULL){
		return 0;
	}
	else{
		//Loops until the appropiate node has been reached
		for(i = 0; i<len; i++){
		
		r=r->next; //points to the next node
		}
		num = r->byte_size; //assigns the byte size of the current node to num
		return num; //Returns this number
	}
}

/*
return_name is very similar to that of return_byte, except that instead of 
a number, it returns the string representing the name of the file.
*/
char *return_name(struct file_list *r, int len){
	char *name; //Used to store the filename
	int i; //Loop counter 
	name = malloc(MAX_FILE_SIZE);
	r = head; //Assigns global variable head to the list
	//If the list is empty, return empty string
	if(r==NULL){
		return "";
	}
	
	else{
		//Loops to the correct node, depending on inputted number
		for(i = 0; i<len; i++){
		
		r=r->next;
		}
		strcpy(name, r->name); //Copies the node's filename into name
		//printf("hey %s\n", name);
		return name; //returns the name
	
	}

}

/*
The prefix_display function simply prints the files that matches
the string inputted by the user in the -p flag.

*/
void prefix_display(struct file_list *r, char *prefix_name){
char *strholder; //Will hold the pointer that will be returned from strstr
int str_len;
int boolean = FALSE; // Sets the boolean state to flase
	r = head; //points the struct to th head
	str_len = strlen(prefix_name); //calculates the length of the prefix name
	//If the list is empty, do nothing
	if(r==NULL){
		return;
	}
	//While the list isn't empty
	while(r!=NULL){
		strholder = malloc(sizeof(r->name)); //Allocates space for the string variable
		strcpy(strholder, r->name); //Copies the name of the file into strholder
		strholder[str_len] = '\0'; //Cuts the current filename up to the prefix pt
		
		//Compares the current trimmed file name to the prefix
		if(strcmp(strholder, prefix_name) == 0){
		printf("%s %d\n", r->name, r->byte_size); //Prints the filename and size
			boolean = TRUE;//Sets the boolean state to true
		
		}
	
	r=r->next;//Points to the next node
	}
	if(boolean == FALSE){ //If boolean is false to this point
	printf("No matching files found.\n"); //No prefix match was found
	return;
	
	}

}
/*
The function create takes no arguments, the purpose of this function is 
to compile a bunch of files provided by the user, and then put them toguether
into a binary file. 
*/

void create(){
	int filedes; //Stores the file destination for the files being opened
	int nread; //stores the location of the files being read
	int file_num; //Stores the number of files specified by the user
	int binary; //Stores the location of the binary file used to store all file information
	int w1; //Stores the location of the files being writen to
	int filename_chars; //Stores the length of the filenames
	char *buffer; //Stores the data inside the files
	char *file_name; //Stores the name of the file
	unsigned char data; //Stores data being written into binary files
	long total; //Stores the total bytes to write in a file
	int i; //Loop counter
	struct stat st; //Stat declaration to retrieve certain file information
	int file_size; //Stores the total bytes in a file
	
	
	//Opens the binary file used to store all the file information
	if((binary = open(my_argv[ARCHIVE_POSITION], O_WRONLY | O_CREAT, 0644)) == -1){
		fprintf(stderr, "Could not open the binary file for writing.\n");
		exit(1);
	}
	
	file_num = my_argc-NON_FILE_ARGS; //Calculates the number of files inputted
	data = (unsigned char)file_num; //Assigns the number of files into a unsigned char
	
	w1 = write(binary, &data, sizeof(unsigned char)); //Writes the number of files into the binary file
	
	//For loop that goes through each file
	for(i = NON_FILE_ARGS; i < my_argc; i++){ 
		filename_chars = strlen(my_argv[i]); //Stores the length of the filename
		file_name = strcpy(malloc(filename_chars), my_argv[i]); //Allocates and copies the name into the var
		stat(my_argv[i], &st); //Retrieves information about the current file
		file_size = st.st_size; //Gets the size of the file in bytes
		data = (unsigned char)filename_chars; //Gets the number of chars in the name into the char var
		
		/* Writes each of the fields into the proper position in the compressed file */
		w1 = write(binary, &data, sizeof(unsigned char));
		w1 = write(binary, file_name, filename_chars);
		w1 = write(binary, &file_size, sizeof(int));
	}
	
		//For loop that goes through each file
	for(i = NON_FILE_ARGS; i < my_argc; i++){
		total = 0 ; //Resets the counter each time
		stat(my_argv[i], &st); //Retrieves information about the files
		file_size = st.st_size; //Gets the size of the file in bytes 
		buffer = malloc(file_size); //Allocates enough space for the buffer
		
		//Opens the current file, exits if the program fails
		if((filedes = open(my_argv[i], O_RDWR)) == -1 ){
			printf("Couldn't open %s\n", my_argv[i]);
			exit(1);
		}
		
		//Reads the information from the file into the buffer until no more bytes to read
		while((nread=read(filedes, buffer, file_size)) > 0 ){
			total+=nread; //Increments total times read
			w1 = write(binary, buffer, total); //Writes the information to the file
		}
		close(filedes); //Closes each file
	}
	close(binary); //Closes compressed file
}

/*
The function prefix takes two arguments of type string (char *),
 the purpose of this function is to print certain file information
 specified by the user. The function takes the string the user types
 and looks through the binary file to check if any filename matches that
 prefix.
*/

void prefix(char *prefix_name, char *binary_file){
	struct file_list *list;  //Makes a new linked list
	int filedes; //Used to store file destination of the compressed file
	int nread; //Used to store file location of read data
	unsigned char data; //stores the data read from file
	int num_files; //Stores the number of files
	int filename_len; //Stores the length of file names 
	int i; //Loop counter
	char *buffer; //Stores file name
	int b_size; //Store's files byte size

	//Opens the binary file for reading, exits program if it fails.
	if((filedes = open(binary_file, O_RDWR)) == -1){
		printf("Couldn't open %s\n", binary_file);
			exit(1);
	}
	
	nread = read(filedes, &data, sizeof(unsigned char)); //Reads the number of files off the compressed file
	num_files = (int)data; //Converts it to integer
		
		//Loops through each files for the correct number of files
		for(i = 0; i < num_files; i++){
			nread = read(filedes, &data, sizeof(unsigned char)); //Reads the length of the filename
			filename_len = (int)data; //Converts it to int
			buffer = malloc(filename_len); //Allocates enough space for the buffer to read
			nread = read(filedes, buffer, filename_len); //Reads file name into buffer
			nread = read(filedes, &b_size, sizeof(int)); //Reads byte size into b_size
			add(buffer, b_size); //Calls on the add function
			
		}
		close(filedes); //Closes binary file
		prefix_display(list, prefix_name); //Prints the information accordingly
	}
	

	
/*
The function extract does the exact opposite of the create function.
The extract function takes one string as a parameter representing the binary
file's name. It goes through this file and uncompresses this "compressed file".
*/	
	
void extract(char *binary_file){
	struct file_list *list; //struct definition
	int filedes; //File destination of the binary file
	int nread; //stores return type of the read function
	unsigned char data; //Used to store read number of files 
	int num_files; //Used to store actual integer number of files
	int filename_len; //Stores the length of the file
	int i; //loop counter
	char *buffer; //Stores the file's content
	
	int b_size; //Stores the byte size of the file
	int size_test; //Also stores the byte size of the files
	int new_files; //File destination of the newly extracted files
	int w1; //Stores return type of write
	char *filename = malloc(MAX_FILE_SIZE); //Stores the file's name

	//Opens the compressed file for reading, exits if it returns 0;
	if((filedes = open(binary_file, O_RDWR)) == -1){
		printf("Couldn't open %s\n", binary_file);
			exit(1);
	}
	
	nread = read(filedes, &data, sizeof(unsigned char)); //Reads the first byte representing number of files
	num_files = (int)data; //Converts from char to integer
		
		//Loops through for each of the files
		for(i = 0; i < num_files; i++){
			nread = read(filedes, &data, sizeof(unsigned char)); //Reads the filename length
			filename_len = (int)data; //Converts it to integer
			buffer = malloc(filename_len); //Allocates enough space for the buffer
			printf("hey yall %d\n", i);
			nread = read(filedes, buffer, filename_len); //Reads the filename
			printf("test\n");
			nread = read(filedes, &b_size, sizeof(int)); //reads the file size in bytes
			printf("last test\n");
			add(buffer, b_size); //Calls on the add function
			//printf("string is %s\n", buffer);
			printf("made it\n");
		}
		printf("hey\n");
		//Loops through for each of the files
		for(i = 0; i < num_files; i++){
			size_test = return_byte(list, i); //Calls on the return_byte to get number of bytes on current file
			strcpy(filename, return_name(list, i)); //Copies the string returned by return_name into filename
			buffer = malloc(size_test); //Allocates space to read and write into the buffer
			//printf("filename is %s\n", filename);
			//Opens and creates the new individual files being extracted
			if((new_files = open(filename, O_WRONLY | O_CREAT, 0644)) == -1){
				printf("Couldn't open %s\n", filename);
				exit(1);
			}
			
			//Reads and writes the data from the binary file into the current file
			nread = read(filedes, buffer, size_test);
			w1 = write(new_files, buffer, size_test);
			close(new_files); //Closes the new_files
		}
	close(filedes); //Closes the file

}
