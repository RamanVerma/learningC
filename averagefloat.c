/*This programs calculates the average of an arbitrary number
of floating point numbers entered by the user, through keyboard.
All the values are stored in dynamically allocated memory, before
the average is calculated.
User enters all the numbers in one line
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INPUT 100

int main(){
char in[MAX_INPUT] = {0};    //User input is received here
float total = 0;
int count = 1;
int counter = 0;
int index = 0;
int len = 0;
float *tmp = NULL;
float number = 0.0;
char *t = NULL;
char *tab = NULL;
int newnum = 0; 
//Accepting user input
printf("Enter all the float point numbers as a space separated string\n");
while(((in[index]=getchar())!='\n') && (index<MAX_INPUT)){
    if(isblank(in[index++])){
        count++;    //do not rely on this variable to average
    }
}
//Create an array to store floating point numbers
tmp=(float *)malloc(count*sizeof(float));
if (tmp==NULL){
    printf("Failed to allocate memory. Will exit");
    return 1;
}
//Parse the input and store floating point numbers in array
newnum = 1;
for(index=0;index<MAX_INPUT;index++){
    if(newnum==1){
        tab = &in[index];    //keep a tab at the new number's address
        counter++;    //this variable is to be used for average
    }
    if(isblank(in[index]) || in[index] == '\n'){    //blank => new number will start after this char
        t=(char *)malloc(len*sizeof(char));    //allocate memory to pointer t
        if (t==NULL && len != 0){
            printf("Failed to allocate memory. Will exit");
            return 1;
        }
        memcpy(t,tab,len);    //copy the (string)number to t
        number = atof(t);
        total+=number;    //add the number
        tmp=&number;    //store the number in the array
        tmp=tmp+1;
        newnum = 1;    //now, set flag for new number
        len = 0;    //set next number's length to 0
        if(in[index] == '\n'){
            break;
        }
    }else{    //not blank => not new number
        newnum = 0;
        len++;
    }
}
//Display all the numbers that were entered.
//TODO****NOT WORKING****
for(index=counter;index>0;index--){
    tmp=tmp-1;
    printf("%f\n",*tmp);
}
printf("The average is %f\n",(total/counter));
return 0;
}
