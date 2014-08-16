/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 10.1
 *
 * demostrates different format specifiers for 
 * scanf() function
 */

#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>

#define MAX_STR_LEN 20

/*
 * get_type1()  get the string of type 1
 * @str char array where the string is to be stored
 *
 * gets a string conatining lower case alphabets and then a 
 * single digit
 */
void get_type1(char str[]){
    int count = 0;
    char ch = '\0';
    int size_array = sizeof(str)/sizeof(str[0]);
    /*
     * FIXME Don't know why the array length comes out to 
     * be only 8. GRRRR!
     */
    printf("array length %d\n", size_array);
    /*
     * loop upper boundary = length of char array
     */
    while(count < (size_array - 1)){
        /*
         * get the next char from stdin
         */
        ch = (char)getchar();
        /*
         * check if this char is valid
         */
        if(ch >= 'a' && ch <= 'z'){
            /*
            * its a lower case alpohabet
            */
            str[count] = ch;
        }else if(isdigit(ch)){
            /*
             * its a digit
             */
            str[count++] = ch;
            str[count] = '\0';
            break;
        }else{
            /*
             * end of input, or invalid char. Put it back!
             */
            str[count] = '\0';
            ungetc(ch, stdin);
            break;
        }
        count++;
    }
    return;
}


/*
 * get_type2()  get the string of type 2
 * @str char array where the string is to be stored
 *
 * gets a string containing to words starting with upper case
 * alphabet and followed by lower case alphabets. also, each
 * word is separated by a hyphen
 */
void get_type2(char str[]){
    int count = 0;
    char ch = '\0';
    int size_array = sizeof(str)/sizeof(str[0]);
    bool invalid_input = false;
    /*
     * enum based system to track current stage of string input
     */
    enum {start_w1, started_w1, start_w2, started_w2} stage;
    stage = start_w1;
    /*
     * loop upper boundary = length of char array
     */
    while(!invalid_input && count < (size_array - 1)){
        /*
         * get the next char from stdin
         */
        ch = (char)getchar();
        /*
         * check if this char is valid
         */
         switch(stage){
            /*
             * process the first char for word 1
             */
            case start_w1:
                if(ch >= 'A' && ch <= 'Z'){
                    str[count++] = ch;
                    stage++;
                }else{
                    invalid_input = true;
                    ungetc(ch, stdin);
                }
                break;
            /*
             * process the rest of word 1 and the separator
             */
            case started_w1:
                if(ch >= 'a' && ch <= 'z'){
                    str[count++] = ch;
                }else if(ch == '-'){
                    str[count++] = ch;
                    stage++;
                }else{
                    invalid_input = true;
                    ungetc(ch, stdin);
                }
                break;
            /*
             * process the first char for word 2
             */
            case start_w2:
                if(ch >= 'A' && ch <= 'Z'){
                    str[count++] = ch;
                    stage++;
                }else{
                    invalid_input = true;
                    ungetc(ch, stdin);
                }
                break;
            /*
             * process the rest of word 2
             */
            case started_w2:
                if(ch >= 'a' && ch <= 'z'){
                    str[count++] = ch;
                }else{
                    invalid_input = true;
                    ungetc(ch, stdin);
                }
                break;
         }
    }
    /*
     * add a null char like a gentleman
     */
    str[count] = '\0';
    return;
}

/*
 * get_type3()  get the string of type 3
 * @str char array where the string is to be stored
 *
 * gets a string containing an integer, or a floating point
 * number
 */
void get_type3(char str[]){
    int count = 0;
    char ch = '\0';
    int size_array = sizeof(str)/sizeof(str[0]);
    bool got_decimal = false;
    bool got_exp = false;
    /*
     * loop upper boundary = length of char array
     */
    while(count < (size_array - 1)){
        ch = (char)getchar();
        if(isdigit(ch)){
            str[count++] = ch;
            continue;
        }
        if(!got_decimal && (ch == '.')){
            got_decimal = true;
            str[count++] = ch;
            continue;
        }
        if(!got_exp && (ch == 'e' || ch == 'E')){
            got_decimal = true;
            got_exp = true;
            str[count++] = ch;
            continue;
        }
        ungetc(ch, stdin);
        break;
    }
    str[count] = '\0';
    return;
}

/*
 * get_type4()  get the string of type 4
 * @str char array where the string is to be stored
 *
 * gets a string containing alphabets and spaces
 * number
 */
void get_type4(char str[]){
    int count = 0;
    char ch = '\0';
    int size_array = sizeof(str)/sizeof(str[0]);
    /*
     * loop upper boundary = length of char array
     */
    while(count < (size_array - 1)){
        ch = (char)getchar();
        if(isalpha(ch) || isspace(ch)){
            str[count++] = ch;
        }else{
            ungetc(ch, stdin);
            break;
        }
    }
    str[count] = '\0';
    return;
}

/*
 * get_type5()  get the string of type 5
 * @str char array where the string is to be stored
 *
 * gets a string containing anything except spaces and digits
 * number
 */
void get_type5(char str[]){
    int count = 0;
    char ch = '\0';
    int size_array = sizeof(str)/sizeof(str[0]);
    /*
     * loop upper boundary = length of char array
     */
    while(count < (size_array - 1)){
        ch = (char)getchar();
        if(isspace(ch) || isdigit(ch)){
            ungetc(ch, stdin);
            break;
        }else{
            str[count++] = ch;
        }
    }
    str[count] = '\0';
    return;
}

/*
 * main function
 */
void main(){
    /*
     * define five char arrays
     */
    char s1[MAX_STR_LEN] = {'\0'};
    char s2[MAX_STR_LEN] = {'\0'};
    char s3[MAX_STR_LEN] = {'\0'};
    char s4[MAX_STR_LEN] = {'\0'};
    char s5[MAX_STR_LEN] = {'\0'};

    /*
     * call the corresponding functions to get the strings
     * of each type
     */
    get_type1(s1);
    get_type2(s2);
    get_type3(s3);
    get_type4(s4);
    get_type5(s5);
    /*
     * print all the strings now
     */
    printf("\n%s", s1);
    printf("\n%s", s2);
    printf("\n%s", s3);
    printf("\n%s", s4);
    printf("\n%s", s5);
    printf("\n");
    return;
}
