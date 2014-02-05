#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define NUM_STR 10
#define LEN_STR 15

void main(){

char BUF[LEN_STR];    //char array to hold input strings
char *pstr[NUM_STR] = {NULL};    //array of pointers to the variables of type char
char *pchar = BUF;    //pointer to variable BUF
char *tmp = NULL;
int i = 0;
bool sorted = false;    //boolean variable to check if strings are sorted

for(i=0;i<NUM_STR;i++){    //loop to get all the strings as user input
	pchar = BUF;
	printf("Enter %s string of maximum length %d\n", i>0 ? "another":"a",LEN_STR);
	while(((*pchar=getchar())!='\n')&&(pchar-BUF<LEN_STR-1)){
		pchar++;
	}
	if(*(pchar)!='\n'){    //user did not enter newline character in the end
		printf("You exceeded the maximum length of string.\n");
		i--;
		continue;
	}
	*pchar='\0';    //add null character at the end of string
    if(pchar-BUF == 0){    //user entered empty line.Break out
		break;
	}
	pstr[i]=(char *)malloc(pchar-BUF+1);    //allocate memory to copy input string
	strcpy(pstr[i],BUF);    //copy the input string to new location
}
for(;i>=0;--i){
	printf("%s\n",pstr[i]);    //print strings in reverese order
	free(pstr[i]);    //free memory as it has served its purpose
	pstr[i]=NULL;    //initialize the pointer variable
}
}
