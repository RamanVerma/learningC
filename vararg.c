/*
 * Exercise 9.4 - Demonstarte a function that will
 * accept variable number of double variables as
 * input, along with the count for number of input
 * variables. It then returns a string representation
 * of these double arguments, each separated by a 
 * comma and with two digit precision decimal part.
 *
 * This is basically sprintf() :-)
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

char strdouble[5];
/*Function prototype*/
char *toString(int count, double first, ...);

/*
 * toString()   - converts variable number of double
 *                variables into string
 * @count: number of variable arguments
 * @first: first argument of type double
 * @...: subsequent arguments of type double
 *
 * This function creates astring representation of 
 * variable number of arguments of type double.
 * Each argument will be shown to have two digit
 * decimal precision and will be separated by comma.
 */
char *toString(int count, double first, ...){
    int w = 0;
    int x = 0; 
    int total_len = 0;
    double y = 0.0;
    char *ch;
    /*
     * Allocate memory to hold the output string
     */
    char *out = (char *)malloc(sizeof(char) * 5);
    if(out == NULL){
        printf("Failed to allocate memory.\n");
        return out;
    }
    ch = out;
    va_list parg; /*variable of type va_list*/
    va_start(parg, first); /*initialize parg*/
    /*
     * Now process each argument from the variable
     * argument list
     */
    for(x = 0;x < count;x++){
        /*
         * FIXME the follwing statment starts
         * iterating through the variable 
         * argument list from the second element
         * , not the first one.
         */
        y = va_arg(parg, double);
        /* Multiply double variable by 100, to 
         * get the two digit precision moved 
         * to left of decimal
         */
        y *= 100;
        /*
         * Divide the resulting number four times
         * by 10, and store the remainders
         * Cast it into int for every math operation
         */
        for(w = 4;w >= 0;w--){
            if(w == 2){
                strdouble[w]='.';
                continue;
            }
            /*
             * Note that we have added (int)y % 10 to 
             * (int)'0', before casting the result to char.
             * This way we are adding the single digit 
             * integer (0...9) to the ASCII value of digit '0'
             * ASCII values for 0 thru 9 are guaranteed to be
             * sequential, hence this logic works
             *
             * In case, we simply cast int to char, we will get
             * the char corresponding to ASCII code 0 thru 9.
             * I did that first.
             */
            strdouble[w] = (char)(((int)y % 10) + (int)'0');

            y = (int)y / 10;
        }
        strncpy(ch, strdouble, 5);
        ch += 5;
        *ch = ',';
        ch++;
        total_len += 6;
    }
    /*
     * Essential housekeeping to set 
     * parg back to NULL
     */
    va_end(parg);
    return out;
}
/*
 * main function
 */
int main(){
    printf("%s\n",toString(5, 2.2, 3.3, 4.4, 5.5, 6.6));
}
