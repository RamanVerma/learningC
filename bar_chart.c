/*
 * produces a bar chart out of data entered by the user.
 * the program accepts user data in the form of value 
 * bar's tag. it also accepts the dimension of screen
 * to be used to display the chart. dimension is defined
 * as the <# of rows> X <# of columns>
 */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

/*
 * maximum length of the tag
 */
#define TAG_LEN 10
/*
 * structure that defines the data input by the user
 */
typedef struct userdata{
    double value;
    char tag[TAG_LEN];
    struct userdata *next;
}data;

/*
 * create pointer variables of the above defined type
 */
data *head = NULL;
data *entry = NULL;
data *last = NULL;

int count = 0;
double uservalue = 0.0;
double max = 0.0;
char *ptr = NULL;

/*
 * get_user_data()     gets the data input from user
 *
 * gets user data and stores it in a linked list.
 * also records the max value entered by the user
 * returns False, if the user has entered empty string
 *         True otherwise
 *
 * FIXME if the user enters a number larger than 5 characters,
 * or a tag greater than TAG_LEN, the stdin buffer forwards 
 * the stale characters to next getchar() call and the next
 * input gets messed up. Need to understand how to effectively
 * drop this buffer. fflush(stdin) didn't work for me
 * earlier.
 */
bool get_user_data(){
    count  = 0;
    while(((*(ptr + count) = getchar()) != '\n') && (count < 5)){
        count++;
    }
    /*
     * append a null character
     */
    *(ptr + count) = '\0';
    /*
     * break the while loop when user enters empty line. There is
     * no other check for any garbage data !!
     */
    if(strcmp(ptr, "\0") == 0){
        return false;;
    }
    uservalue = atof(ptr);
    if(head == NULL){
    /*
     * allocate memory for head of linked list
     */
        head = (data *)malloc(sizeof(data));
        if(head == NULL){
            printf("Failed to allocate memory\n");
            return false;
        }
        head->value = uservalue;
        head->next = NULL;
        last = head;
    }else{
        /*
         * allocate memory for new data
         */
        entry = (data *)malloc(sizeof(data));
        if(entry == NULL){
            printf("Failed to allocate memory\n");
            return false;
        }
        last->next = entry;
        entry->value = uservalue;
        entry->next = NULL;
        last = entry;
    }
    /*
     * storing the max value entered by the user
     */
    max = (last->value > max) ? last->value : max;
    /*
     * accept tag for this data
     */
    memset(ptr, '\0', sizeof(ptr));
    count = 0;
    while(((*(ptr + count) = getchar()) != '\n') && (count < TAG_LEN)){
        count++;
    }
    /*
     * append a null character
     */
    *(ptr + count) = '\0';
    strncpy(last->tag, ptr, TAG_LEN);
    return true;
}

/*
* draw_bar_chart()     draws the bar chart for the given data
 * @head(): head of the linked list holding the data
 *
 * draws a bar chart for the data from the linked list
 * chart is drwan according to the screen dimensions specified
 * by the user
 */
void draw_bar_chart(data *head){
    return;
}

/*
 * main function
 */
void main(){
    int rows = 0;
    int cols = 0;
    /*
     * memory buffer to hold user input temporarily
     */
    ptr = (char *)malloc(sizeof(char) * TAG_LEN);
    if(ptr == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    memset(ptr, '\0', sizeof(ptr));
    /*
     * accept user input and store in a linked list
     */
    while(get_user_data());
    /*
     * iterate through the linked list and process data
     */
    entry = head;
    while(entry != NULL){
        printf("value %f , tag %s\n", entry->value, entry->tag);
        /*
         * point to the next entry in the list
         */
        entry = entry->next;
    }
    printf("Enter the number of rows to be used for the display\n");
    scanf("%d", &rows);
    printf("Enter the number of cols to be used for the display\n");
    scanf("%d", &cols);

}
