/*This code will read a string from the keyboard.
It then removes and punctuation marks and spaces.
And then re prints the string at the console.
Everything is done using pointers.
*/

#include<stdio.h>
#include<ctype.h>

#define MAX_INPUT 50

int main(){

char buffer[MAX_INPUT] = {'\0'};    //buffer to store the input
int index = 0;
char *temp = NULL;
temp=buffer;
for(index=0;index<MAX_INPUT;){
    *temp=getchar();
    if (!ispunct(*temp) && !isspace(*temp)){
        temp++;
        index++;
    }
    if (*temp == '\n'){
        break;
    }
}
printf("This is what you have entered, without spaces and punctuation marks\n");
printf("%s\n",buffer);
}
