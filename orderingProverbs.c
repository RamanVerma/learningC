/*This program accepts proverbs from the user as a keyboard input.
It then stores them in memory and displays all of them sorted by
their length.
*/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PROVERBS 10    //maximum number of proverbs
#define MAX_LEN_INPUT 50    //maximum length for each proverb

int main(){
bool done=false;    //flag to indiacate that user has finished entering her input
int num=1;    //counter for the number of proverbs entered
char buffer[MAX_LEN_INPUT]={'\0'};    //array of char to store user input
int index=0;
char *temp=NULL;    //char buffer to hold the address of copy of input string
char *arrayOfProverbs[MAX_PROVERBS]={NULL};    //array of char pointers
int iterator=0;    //iterator for the array of Proverbs
char *temp2=NULL;    //convenience pointer

//Receive input from the user and store it in memory
while(!done && num<=MAX_PROVERBS){
    index=0;
    while((buffer[index]=getchar())!='\n' && index<MAX_LEN_INPUT){
        index++;
    }
    buffer[index]='\0';    //replacing the newline char with null to use strlen accurately
    temp=(char *)malloc(strlen(buffer)*sizeof(char));    //allocate memory to store the input string
    if(temp==NULL){
        printf("System could not allocate memory. Program will exit.\n");
        return 1;
    }
    memset(temp,' ',strlen(buffer)*sizeof(char));    //initialize the allocated memory to all spaces
    memcpy(temp,buffer,strlen(buffer)*sizeof(char));    //create a copy of the input string
    for(iterator=0;iterator<num;iterator++){    //iterate over the array of Proverbs
        if(arrayOfProverbs[iterator]==NULL){
            arrayOfProverbs[iterator]=temp;    //reached the end of array
        }else if(strlen(arrayOfProverbs[iterator]) > strlen(temp)){    //check the length of strings in the array
            for(index=num-1;index>iterator;index--){    //move all pointers to point to the previous element
                arrayOfProverbs[index]=arrayOfProverbs[index-1];
            }
            arrayOfProverbs[iterator]=temp;    //place the address of temp at correct position in the array
        }
    }
    num++;
    if(index==0){    //indicates that the user has finished entering the input
        done=true;
    }
}
//Display the sorted array of Proverbs
for(iterator=0;iterator<num;iterator++){
    printf("%s\n",arrayOfProverbs[iterator]);
}
}
