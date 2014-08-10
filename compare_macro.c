/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 13.1
 *
 * Demonstrates the use of a macro to compare two integers
 */
#include<stdio.h>
#include "macros.h"

/*
 * main function
 */
void main(){
int a = 0;
int b = 0;
int c = 0;

/*
 * get the user input
 */
printf("Enter the first integer\n");
scanf("%d", &a);
printf("\nEnter the second integer\n");
scanf("%d", &b);

/*
 * do the comparison with the help of our macro
 * print the result
 */
c = compare(a,b);
if(c > 0)
    printf("a is greater than b\n");
else if(c == 0)
    printf("a is equal to b\n");
else
    printf("a is less than b\n");

return;
}
