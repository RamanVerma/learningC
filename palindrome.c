#include<stdio.h>

#define MAXLEN 50
void main(){
char text[MAXLEN];
int count=0;
int count2=0;
_Bool isPalindrome=1;
fgets(text,MAXLEN,stdin);
for(count2=strlen(text)-2;count2>=count;count2--){
if(text[count]!=text[count2]){
isPalindrome=0;
break;
}
count++;
}
if(isPalindrome){
printf("You entered a Palindrome !\n");
}else{
printf("You have not entered a Palindrome !\n");
}
}
