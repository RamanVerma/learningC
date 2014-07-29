/*
* Exercise 9.3
* Demonstarte a function that accepts an array of strings,
* and returns a string that is the result of concatenation
* of all the input strings.
* Each string should be delineated by just one newline character.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
* Function prototypes
*/
char * append(char * []);

int numstrings = 10; /*max number of input strings*/
char * ptr[10]; /*array of pointers to char arrays*/
int maxlenstring = 10; /*max possible length of each input string*/

/*
 * append() - appends the input array of strings
 * @strings:    array of char pointers containing strings
 *
 * Accepts an array of strings and returns a single string
 * that is created by concatenating all the strings.
 * 
 * The trick is that if an input string ends in new line,
 * we do not add another new line to it. But if it does not,
 * then we add a new line character.
 *
 * Return: pointer to char, containing the address of the 
 * appended string
 */
char * append(char * strings[]){
    int x, y, total_length = 0;
    char * ch;
    char * ch2;
    /*
     * Dynamincally allocate memory for the output string
     */
    char * out = (char *)malloc(sizeof(char) * numstrings * (maxlenstring + 1));
    if(out == NULL){
        printf("Memory allocation failed\n");
        return out;
    }
    ch2 = out;
    /*
     * Iterate over all the strings
     */
    for(;x < 10;x++){
        /*
         * Breaks out if we reach a NULL pointer
         */
        if(strings[x] == '\0'){
            break;
        }
        /*
         * walk through the strng until \n or \0
         * Assumption: strings end in null character
         */
        y = 0;
        ch = strings[x];
        while(*ch != '\n' && *ch != '\0'){
            ch++;
            y++;
        }
        /*
         * Append input string to the output string
         * Move the ptr marking output string by the length of 
         * appended string.
         * Append a new line character in the end
         */
        strncpy(ch2, strings[x], y);
        ch2 = ch2 + y;
        *(ch2++) = '\n';
        total_length += y;
    }
    printf("Total length of output string: %d , %d\n", total_length, strlen(out));
    printf("%s\n", out);
    return out;
}

/*
* main function
*/
int main(){
    char * ch;
    /*
     * Allocate memory for the strings
     */
    int index = 0;
    for(;index < numstrings;index++){
        ptr[index] = (char *)malloc(sizeof(char) * maxlenstring);
        if(ptr[index] == NULL){
            printf("Error allocating memory\n");
            return 1;
        }
    }
    /*
     * Get the input strings from user and store them in the array
     * The loop ends if user enters just a new line character and 
     * presses enter
     * FIXME Clumsy way of getting string input. Although it is safe,
     * because fgets fills a string(ptr[index]) with only as much
     * char as is its length, it stores characters higher than the 
     * specified length at the next string pointer. Not wrong per say,
     * I just dont like it. Guess the best way is scanf a single char at 
     * a time and strncpy it to the string buffer until the buffer length
     * is filled up or we get a \n, and rint message that rest of the char
     * will be lost.
     * Just more user friendly.
     */

    for(index = 0;index < numstrings;index++){
        printf("Enter another string. Or, press <Enter> to indicate finish\n");
        if(fgets(ptr[index], sizeof(ptr[index]), stdin) == NULL){
            printf("Error reading from stdin\n");
            return 2;
        }
        /*
         * This one was a pain in the ass, compiler errors out if I write
         * the second argument as '/n'. The difference is quotes.
         */
        if(strcmp(ptr[index], "\n") == 0){
            break;
        }
    }
    /*
     * call the string append function
     */
    ch = append(ptr);
    if(ch != NULL){
        printf("Happy Ending: %s\n", ch);
    }
    return 0;
}
