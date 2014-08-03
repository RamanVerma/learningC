/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 11.2
 *
 * This program demonstrates a linked list.
 * A structure type is defined to hold the first and last names of a person
 * along with his/her phone number.
 * The program should allow users to enter arbitrary number of enteries of
 * this struct type.
 * It should then let a user search a number, given the first and last names,
 * or search a name, given the number.
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

/*phone book structure*/
struct phonebook{
    char fname[11];   /*first name*/
    char lname[11];   /*last name*/
    char phone[11];   /*phone number*/
    struct phonebook *next; /*pointer to next structure*/
};

struct phonebook *firstentry;   /*pointer to the first entry in the list*/

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
 * searchbyname()     search phone number, given the first and last names
 * @fname: first name of the person
 * @lname: last name of the person
 *
 * returns the phone number of the person, or NULL pointer, if the number
 * is not found
 */
struct phonebook *searchbyname(char * fname, char *lname){
    struct phonebook *entry = firstentry;
    while(entry != NULL){
        if(strcmp(entry->fname) == 0 && strcmp(entry->lname) == 0){
            break;
        }else{
            entry = entry->next;
        }
    }
    return entry;
}

/*
 * searchbynumber()   search names, given the phone number
 * @number: phone number
 *
 * returns the phonebook entry matching this number
 */
struct phonebook *searchbynumber(char *number){
    struct phonebook *entry = firstentry;
    while(entry != NULL){
        if(strcmp(entry->phone, number) == 0){
            break;
        }else{
            entry = entry->next;
        }
    }
    return entry;
}

/*
 * main function
 */
void main(){
    char *more;
    char option;
    int err;
    bool done = false;
    char first[11];
    char last[11];
    char phone[11];
    struct phonebook *entry = NULL;
    struct phonebook *lastentry = NULL;
    /*
     * Allocate memory
     */
    more = (char *)malloc(sizeof(char) * 2);
    if(more == NULL){
        printf("Failed to allocate memory");
        return;
    }
    printf("Do you want to enter data to the phone book. (y/n): \n");
//    fgets(more, sizeof(more), stdin);
//    err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
    get_input_from_console(more);

    while(more[0] == 'y' || more[0] == 'Y'){
        /*
         * Allocate memory for new entry and check if allocation succeded
         */
        entry = (struct phonebook *)malloc(sizeof(struct phonebook));
        if(entry == NULL){
            printf("Failed to allocate memory");
            return;
        }
        /*Enter the information for this entry*/
        printf("Enter the first name: \n");
//        fgets(entry->fname, sizeof(entry->fname),stdin);
//        err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
        get_input_from_console(entry->fname);

        printf("Enter the last name: \n");
//        fgets(entry->lname, sizeof(entry->lname),stdin);
//        err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
        get_input_from_console(entry->lname);

        printf("Enter the phone number: \n");
//        fgets(entry->phone, sizeof(entry->phone),stdin);
//        err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
        get_input_from_console(entry->phone);

        entry->next = NULL;
        /*Add this entry to the linked list*/
        if(firstentry == NULL){
            firstentry = entry;
        }else{
            lastentry->next = entry;
        }
        lastentry = entry;

        printf("Do you want to enter data to the phone book. (y/n): \n");
//        err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
//        fgets(more, sizeof(more), stdin);
//        err = fflush(stdin);  /*fflush() flushes stray newline char left in buffer*/
        get_input_from_console(more);
    }
    /*
     * Now ask the user if he/she wants to search by name/number
     */
    while(!done){
        printf("A: Search by first name and last name.\n");
        printf("B: Search by phone number.\n");
        printf("*: Quit.\n");
        option = getchar();
        err = fflush(stdin);  /*gets rid of the stray newline char in stdin buffer*/
        switch(tolower(option)){
            case 'a':   /*searchbyname*/
                printf("Enter the first name: \n");
                err = fflush(stdin);
                fgets(first, sizeof(first),stdin);
                err = fflush(stdin);
                printf("Enter the last name: \n");
                fgets(last, sizeof(last),stdin);
                err = fflush(stdin);
                entry = NULL;
                entry = searchbyname(first, last);
                if(entry != NULL){
                    printf("Phne number is: %s\n", entry->phone);
                }else{
                    printf("Could not find the relevant entry.\n");
                }
                break;
            case 'b':   /*searchbynumber*/
                printf("Enter the phone number: ");
                fgets(phone, sizeof(phone),stdin);
                err = fflush(stdin);
                entry = NULL;
                entry = searchbynumber(phone);
                if(entry != NULL){
                    printf("This phne belongs to %s %s\n", entry->fname, entry->lname);
                }else{
                    printf("Could not find the relevant entry.\n");
                }
                break;
            default:    /*quit*/
                done = true;
                break;
        }
    }
}
