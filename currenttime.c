/*
 * Beginning C - From Novice to Professional - Fourth Edition
 * Ivor Horton
 * Exercise 13.2
 *
 * Gets the current time in 12 hour or 24 hour formats
 */
 
#include<stdio.h>
#include<time.h>
#include<stdbool.h>

time_t t;
struct tm *timer = NULL;
char *time_in_string = '\0';

/*
 * main function
 */
void main(){
    int value = 0;
    int hour = 0;
    bool morning  = true;
    /*
     * get the current time as a string
     */
    t = time(NULL);
    time_in_string = ctime(&t);
    printf("time in string %s\n", time_in_string);
    /* use this string representation of time to get the 
     * representation in integers
     */
    timer = localtime(&t);
    /*
     * get usr input if she wants time in 12 hour format
     * or 24 hour format
     */
    printf("Do you want to see time in 12 hour format(0), or 24 hour format(1). (0/1)");
    scanf("\n%d", &value);
    /*
     * display the output
     */
    if(value == 0){
        if(timer->tm_hour > 12){
            timer->tm_hour = timer->tm_hour % 12;
            morning  = false;
        }else{
            morning = true;
        }
        printf("Current time is %d:%d:%d %s\n", timer->tm_hour, timer->tm_min, timer->tm_sec, morning ? "am":"pm");
    }else if(value == 1){
        printf("Current time is %d:%d:%d\n", timer->tm_hour, timer->tm_min, timer->tm_sec);
    }else{
        printf("Wrong input.\n");
    }
    return;
}
