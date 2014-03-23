/*
* This code accepts strings from the user.
* It then sorts them, prints the sorted output.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool str_in(char **,int *);	/* function prototype for string input */
void str_sort(const char *[], int);	/* function prototype for string sort */
void swap(void **p1, void **p2);	/* swap two pointers */
void str_out(char *[], int);	/* function prototype for string output */

const size_t BUFFER_LEN = 256;
const size_t NUM_P = 50;

/*
* main function
*/
int main(){
int numofstr = 0;
char **arrayofstr = NULL;
arrayofstr = (char **)malloc(sizeof(char *)*NUM_P);	/* Allocating an array of char * */
if(arrayofstr==NULL){
	printf("main: Error while allocating memory. Exiting now!");
    exit(1);
}
while(str_in(arrayofstr,&numofstr));	/* Calls function to accept strings from user */
str_out(arrayofstr,numofstr);
}

/*
* 	String input routine
* @arrayofstr array of strings where the string will be stored
* @numofstr number of strings entered so far
* Returns: true, when user enters a valid string,
* and false, otherwise. 
* If no memory is obtained, or if there is an 
* error reading from the keyboard, the program is
* terminated by calling exit()
*/
bool str_in(char ** arrayofstr, int *numofstr){
bool ret = true;
int index = 0;
char *str = NULL;
str = (char *)malloc(sizeof(char)*BUFFER_LEN);	/* Allocate memory for the input string */
if(!str){
	printf("str_in: Error while allocating memory. Exiting now!");
    exit(1);
}
for(index=0;index<NUM_P;index++){	/* Store the allocated block of memory in a char** array */
if(*arrayofstr==NULL){
	*arrayofstr = str;
	*numofstr = index+1;
	break;
}else{
	arrayofstr++;
}
}
index=0;
while((*str++=getchar())!='\n' && index++ < (BUFFER_LEN-1));	/* Accept user input */
if(index==0){
	*numofstr -= 1;
	return false;	/* user entered a just new line character */
}else{
	*str='\0';	/* add an ending null char to the string */
	return true;
}
}

/*
*	String output routine
* @arrayofstr array of strings to be displayed
* @count number of strings in the array
* Return: void
*/
void str_out(char * arrayofstr[], int count){
int index=0;
for(index=0;index<count && index<NUM_P;index++){
	printf("%s\n",arrayofstr[index]);
}
}

/*
*	Sort the strings
* @arrayofstr Array containing the strings
* @numofstr number of strings
* Sorts the array of strings, using bubblesort
*/
void str_sort(const char * arrayofstr[], int numofstr){
int index = 0;
int index2 = 0;
for(index=0;index<numofstr;index++){
	for(index2=index+1;index2<numofstr;index2++){
		if(strcmp(arrayofstr[index],arrayofstr[index2] > 0)){
			swap(arrayofstr+index,arrayofstr+index2);
		}
	}
}
}

/*
*	Swap the strings
* @p1 pointer to pointer to first string
* @p2 pointer to pointer to second string
* Swaps the strings
*/

void swap(void **p1, void **p2){
char *tmp = NULL;
tmp=(char *)*p1;
*p1=*p2;
*p2=tmp;
}
