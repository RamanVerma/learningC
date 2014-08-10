/*
 * sample code to illustrate static memory allocation
 */

#include<stdio.h>
#include<string.h>

/*
 * main function
 */
void main(){
    /*
     * static allocation of memory to a single pointer to char
     */
    char *ptr2 = "I am a string.";
    printf("%s, length %d\n", ptr2, (int)strlen(ptr2));
    /*
     * demonstarting static allocation of a two dimensional
     * array of characters
     */
    char *ptr[7] = {"Sunday", "Monday", "Tuesday", "Wedneday",
                        "Thursday", "Friday", "Saturday"};
    int x = 0;
    for(x = 0;x < 7;x++){
        printf("%s, length %d\n", ptr[x], (int)strlen(ptr[x])); 
    }
}
