/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 11.4
 *
 * This program counts the occurences of each letter in a 
 * paragraph etered from the keyboard
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/*define the max length of the input text*/
const size_t MAX_TEXT_LEN = 80;
/*structure to hold the alphabet and count of its occurences*/
struct alphacount{
    char alphabet;
    int count;
};
/*an array of the aplhacount structures*/
struct alphacount occurences[26];
/*
 * initarray()  initializes the alphacount array
 */
void initarray(){
    int x = 0;
    char start = 'a';
    for(x = 0;x < 26;x++){
        occurences[x].alphabet = (char)((int)start + x);
        occurences[x].count = 0;
    }
    return;
}
/*
 * get_input_from_console()   gets the input from stdin into the buffer
 * @buffer: buffer to hold the input
 *
 * returns the pointer to the buffer
 */
char *get_input_from_console(char *buffer){
    int index = 0;
    char *ptr = NULL;
    ptr = buffer;
    if(buffer == NULL)
        return buffer;
    while(((*(ptr + index) = getchar()) != '\n') && (index < (sizeof(buffer) - 1))){
        index++;
    }
    *(ptr + index + 1) = '\0';
    return buffer;
}
/*
 * main function
 */
void main(){
    int x = 0;
    char *ptr = NULL;
    char *index = NULL;
    int index2 = 0;
    /*
     * initialize the array
     */
    initarray();
    /*
     * Allocate memory for the input text
     */
    ptr = (char *)malloc(sizeof(char) * MAX_TEXT_LEN);
    if(ptr == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    get_input_from_console(ptr);
    printf("%s\n", ptr);
    /*
     * count the occurences of each alphabet in the inout text
     */
    index = ptr;
    while(*index != '\0'){
        if(isalpha(*index)){
            index2 = (int)(tolower(*index)) - (int)('a');
            occurences[index2].count++;
        }
        index++;
    }
    /*
     * Print the output
     */
    for(x = 0;x < 26;x++){
        printf("Alphabet: %c, Count: %d\n", occurences[x].alphabet, occurences[x].count);
    }

}
