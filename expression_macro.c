/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 13.3
 *
 * Demonstrates the use of a macro to evaluate an expression
 * and print its result
 */

#include<stdio.h>
#include "macros.h"

/*
 * main function
 */
void main(){
    print_value(1+2);
    print_value((2*3)+(6/2)*(2));
    print_value((2*3)/(6/2)*(2));
}
