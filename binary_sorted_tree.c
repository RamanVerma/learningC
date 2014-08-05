/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 11.5
 *
 * The program receives an arbitrary number of names as input.
 * Names are received first name followed by the second name, 
 * and then a new line character.
 * End of input is signified by new line character as the first
 * character in the name.
 * The program has to store this information in a binary search
 * tree and output the same. Order of sorting is last name and 
 * then the first name
 * There is NO requirement for a balanced tree.
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*max length for first or last name*/
#define MAX_NAME_LEN 10
/*structure for each node of the binary search tree*/
struct person{
   char fname[MAX_NAME_LEN];
   char lname[MAX_NAME_LEN];
   struct person *left;
   struct person *right;
};
/*
 * buffers for data processing
 */
char *fullname1 = NULL;
char *fullname2 = NULL;
/*
 * bstree_insert()  inserts a node into the binary search tree
 * @root:   the root node of this tree
 * @node:   the node to be inserted into the tree
 */
void bstree_insert(struct person* entry, struct person *root){
    memset(fullname1, '\0', sizeof(fullname1));
    memset(fullname2, '\0', sizeof(fullname2));
    fullname1 = strcat(entry->fname, entry->lname);
    fullname2 = strcat(root->fname, root->lname);
    printf("entry full name: %s\n", fullname1);
    printf("root full name: %s\n", fullname2);
    /*
     * make recursive calls to find correct place for this entry
     */
    /*
     * process left child
     */
    if(strcmp(fullname1, fullname2) < 0){
        if(root->left == NULL)
            root->left = entry;
        else
            bstree_insert(entry, root->left);
    }
    /*
     * process left child
     */
    if(strcmp(fullname1, fullname2) < 0){
        if(root->right == NULL)
            root->right = entry;
        else
            bstree_insert(entry, root->right);
    }
    return;
}
/*
 * main function
 */
void main(){
    /*
     * root for the tree
     */
    struct person *root = NULL;
    struct person *entry = NULL;
    int count  = 0;
    char *ptr = NULL;
    char *buffer = NULL;
    /*Allocate memory for input buffer*/
    buffer = (char *)malloc(sizeof(char) * 2 * MAX_NAME_LEN);
    if(buffer == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    /*Allocate memory for helper buffers*/
    fullname1 = (char *)malloc(sizeof(char) * 2 * MAX_NAME_LEN);
    if(fullname1 == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    /*Allocate memory for helper buffers*/
    fullname2 = (char *)malloc(sizeof(char) * 2 * MAX_NAME_LEN);
    if(fullname2 == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    /*
     * Get the input from the user
     */
    do{
        /*
         * Allocate memory for variable of type struct person
         */
        entry = (struct person *)malloc(sizeof(struct person));
        if(entry == NULL){
            printf("Failed to allocate memory\n");
            return;
        }
        /*
         * initialize the input buffer
         * get the user input
         */
        memset(buffer, '\0', sizeof(buffer));
        ptr = buffer;
        while((*ptr = getchar()) != '\n'){
            ptr++;
        }
        /*
         * check if the user entered empty string, else break 
         * the input string into first and last names
         */
        if(strcmp(buffer, "\n") == 0){
            free(entry);
            break;
        }else{
            /*
             * split the user input into first name and last name
             */
            ptr = buffer;
            count = 0;
            while(*(ptr + count) != '\0' && isalpha(*(ptr + count))){
                count++;
            }
            strncpy(entry->fname, ptr, count);
            ptr = ptr + count + 1;
            count = 0;
            while(*(ptr + count) != '\0' && isalpha(*(ptr + count))){
                count++;
            }
            strncpy(entry->lname, ptr, count);
        }
        /*
         * if the tree is empty, assign the entry to root
         * and return
         */
        if(root == NULL){
            root = entry;
            return;
        }
        /*
         * store the entry into binary search tree
         */
        bstree_insert(entry, root);
        /*
         * assign the left and right nodes NULL for now
         */
        entry->left = NULL;
        entry->right = NULL;

        ptr = NULL;
        
//        printf("fname: %s\n", entry->fname);
//        printf("lname: %s\n", entry->lname);
    }while(1);
}
