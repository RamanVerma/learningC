/* 
* This program converts an integer to a string
* It emuates the implementation of sprintf() function
*/

#include<stdio.h>
#include<stdlib.h>

#define BUF_LEN 10	/* Max length of the converted string */
char *int2str(int,char *);	/* converts int to str */

/*
* main function
*/
void main(){
	char *str=NULL;	/* pointer that will store string 
				representation of the interger*/
	int in=0;	/* integer to be input by the user */
	scanf("%d",&in);
	str=(char *)malloc(sizeof(char)*BUF_LEN);
	if(!str){
		printf("%s:%s:%d unable to allocate memory. will exit 	\
				now.\n",__FILE__,__FUNCTION__,__LINE__);
		exit(1);
	}
	printf("%s\n",int2str(in,str));
}

/*
* converts integer to string
* @in integer argument, passed by value
* @str pointer to char. It stores the converted string here
* Return: nothing
*/
char *int2str(int input, char *output){
	int rem=0;
	int index=0;
	const char digits[]="0123456789";	/* This makes all the 
							difference */
	char *localstr=(char *)malloc(sizeof(char)*BUF_LEN);
	char *ret=output;
	if(!localstr){
		printf("%s:%s:%d unable to allocate memory. will exit	\ 
				now.\n",__FILE__,__FUNCTION__,__LINE__);
		exit(1);
	}
	if(input<0){
		*output++='-';
		input*=-1;
	}
	do{
		index++;
		*localstr++=digits[input%10];	/* It will not work if I do
				*localstr++=(char)(input%10);	*/
	} while(input/=10);
	for(;index>0;index--){
		*output++=*--localstr;
	}
	return ret;
}
