/*
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
    char fname[10];   /*first name*/
    char lname[10];   /*last name*/
    char phone[10];   /*phone number*/
    struct phonebook *next; /*pointer to next structure*/
};

struct phonebook *firstentry;   /*pointer to the first entry in the list*/

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
    char more;
    char option;
    bool done = false;
    char first[10];
    char last[10];
    char phone[10];
    struct phonebook *entry = NULL;
    struct phonebook *lastentry = NULL;
    printf("Do you want to enter data to the phone book. (y/n): ");
    more=getchar();
    while(more == 'y' || tolower(more) == 'y'){
        /*
         * Allocate memory for new entry and check if allocation succeded
         */
        entry = (struct phonebook *)malloc(sizeof(struct phonebook));
        if(entry == NULL){
            printf("Failed to allocate memory");
            return;
        }
        /*Enter the information for this entry*/
        printf("Enter the first name: ");
        fgets(entry->fname, sizeof(entry->fname),stdin);
        printf("Enter the last name: ");
        fgets(entry->lname, sizeof(entry->lname),stdin);
        printf("Enter the phone number: ");
        fgets(entry->phone, sizeof(entry->phone),stdin);
        entry->next = NULL;
        /*Add this entry to the linked list*/
        if(firstentry == NULL){
            firstentry = entry;
        }else{
            lastentry->next = entry;
        }
        lastentry = entry;
        printf("Do you want to enter data to the phone book. (y/n): ");
        more=getchar();
    }
    /*
     * Now ask the user if he/she wants to search by name/number
     */
    while(!done){
        printf("A: Search by first name and last name.\n");
        printf("B: Search by phone number.\n");
        printf("*: Quit.\n");
        option = getchar();
        switch(tolower(option)){
            case 'a':   /*searchbyname*/
                printf("Enter the first name: \n");
                fgets(first, sizeof(first),stdin);
                printf("Enter the last name: \n");
                fgets(last, sizeof(last),stdin);
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
