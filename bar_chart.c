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
 * maximum length of the tag. currently limited to 1
 */
#define TAG_LEN 1
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
int nrows = 0;
int ncols = 0;
double uservalue = 0.0;
double max = 0.0;
int numcols = 0;
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
     * increment the count to track number of cols
     */
    max = (last->value > max) ? last->value : max;
    numcols++;
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
 * returns 0 for success and 1 for any errors
 */
int draw_bar_chart(data *head){
    int height = nrows;
    int x = 0;
    double scalefactor = max / (nrows - 1);
    /*
     * create an array of characters to represent the bars
     * initialize the array with spaces
     */
    char *pattern = (char *)malloc(sizeof(char) * numcols * 2);
    if(pattern == NULL){
        printf("Failed to allocate memory\n");
        return 1;
    }
    memset(pattern, ' ', sizeof(pattern));
    /*
     * iterate over each row. Think of it as drawing a skyline
     * top to down
     */
    for(height = nrows;height > 0; height--){
        x = 0;
        /*
         * now draw the pattern of the skyline at this height
         */
        entry = head;
        while(entry != NULL){
            /*
             * value at any linked list node is compared to the 
             * current height of the sky scraper times the 
             * scaling factor.
             */
            if(entry->value >= (height * scalefactor)){
                *(pattern + x) = '#';
            }
            x+=2;
            entry = entry->next;
        }
        /*
         * print the pattern for this height
         */
        printf("%s\n", pattern);
    }
    /*
     * now write down the tags
     */
    x = 0;
    entry = head;
    while(entry != NULL){
        /*
         * value at any linked list node is compared to the 
         * current height of the sky scraper times the 
         * scaling factor.
         */
        strncpy((pattern + x), entry->tag, TAG_LEN);
        x+=2;
        entry = entry->next;
    }
    /*
     * print the tags
     */
    printf("%s\n", pattern);

    return 0;
}

/*
 * main function
 */
void main(){
    int rows = 0;
    int cols = 0;
    /*
     * memory buffer to hold user input temporarily
     * FIXME hard coded value here '6'
     */
    ptr = (char *)malloc(sizeof(char) * 6);
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
     * ask for the number of height and width of the output
     * right now, I just assume that the width would be sufficient
     * for all the columns to be displayed
     */
    printf("Enter the number of rows to be used for the display\n");
    scanf("%d", &rows);
    nrows = (rows < 2) ? 100 : rows;
    printf("Enter the number of cols to be used for the display\n");
    scanf("%d", &cols);
    ncols = cols;
    /*
     * we have all the info. draw the bar chart
     */
    draw_bar_chart(head);
    return;
}
