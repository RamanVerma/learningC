/*
* This program will accept a string as input.
* It will output each of the words used in this string in ascending
* order of length.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUF_LEN 100	/* max length of string buffer */

int numwordsentered=0; 	/* actual number of words input by user */

int numwords(char *);	/* returns the number of words in a string */
void str2words(char *,char **);	/* extracts words from a string and returns 
			them as a array pointed to by the second parameter */
int length(char *);	/* returns the length of an input string */

/*
* main function
*/
void main(){
	char *in=NULL;
	char **words=NULL;
	in=(char *)malloc((sizeof(char)*BUF_LEN)+1);	
	if(in==NULL){
		printf("%s:%s:%d unable to allocate memory.	\	
			will exit\n",__FILE__,__FUNCTION__,__LINE__);
		exit(1);
	}
	char *start=in;
	int count=0;
	while(1){
		*in=getchar();
		if(*in=='\n'){
			*in='\0';
			break;
		}else{
			in++;
			count++;
		}
		if(count==BUF_LEN){
			*in='\0';
			break;
		}
	};
	numwordsentered=numwords(start);
	words=(char **)malloc(sizeof(char *)*numwordsentered);	
	if(words==NULL){
		printf("%s:%s:%d unable to allocate memory.	\	
			will exit\n",__FILE__,__FUNCTION__,__LINE__);
		exit(1);
	}
	str2words(start,words);
	int i=0;
	for(;i<numwordsentered;i++){
		printf("%s\n",*words++);
	}
}

/*
* number of words in a string
* @str char pointer holding a string
* Return number of words in the string
*/
int numwords(char *str){
	int count=0;
	if(*str=='\0'){
		return count;
	}
	while(*str!='\0'){
		if(isspace(*str))
			count++;
		str++;
	};
	return ++count;
}

/*
* extracts words from a string
* @str string passed as first argument
* @warray array of extracted words
* Assumption main method will define the length of warray and allocate memory
* memory allocation for individual words will happen inside this function.
* ***NOTE***
* I am not sure if the memory allocated for individual words will hold after
* this function exits. Although my text book says that while variables are
* local, memory allocated for pointers hold even after the function exits.
* All we need to do is return the address of that memory. I guess the pointer
* itself will be discarded but not the memory block. Book also says that it is
* not a good coding style to allocate memory in one function and release in
* another. This may cause memory leaks.
*/
void str2words(char *str,char **warray){
	int count=0;
	int num=0;
	char *start=NULL;
	while(1){
		if(!isspace(*str) && *str!='\0'){
			count++;
			if(count==1)
				start=str;
		}else{
			*warray=(char *)malloc((sizeof(char)*count)+1);
			if(warray==NULL){
				printf("%s:%s:%d unable to allocate memory.\ 
				will exit\n",__FILE__,__FUNCTION__,__LINE__);
				exit(1);
			}
			strncpy(*warray++,start,count);
			num++;
			count=0;
		}
		str++;
		if(num==numwordsentered || *str=='\0')
			break;
	};
}

/*
* length of a string
* @word input string
* Return: length of the word
*/
int length(char *word){
	int count=0;
	while(*word!='\0'){
		count++;
	}
	return count;
}
