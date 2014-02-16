/*This code will get temperature readings from the keyboard.
There are 6 readings to be entered per day, and for an 
arbitrary number of days. These readngs are stored in a
dynamically allocated array. The ouput will be the readings
per day and their average, as single precision floating point
numbers.
*/

#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX_DAYS 10
#define READINGS_PER_DAY 6
#define MAX_VALUE_SIZE 10

int main(){
    float *days[MAX_DAYS] = {NULL};
    float value = 0;
    float *readings = NULL;    //stores floating point values
    char *x = NULL;    //receives the input characters
    bool validInput = false;    //pointer to identify that a value is being input
    char *inputValue = NULL;    //points to the start of a new input number
    int count = 0;    //to keep track of the length of input float value
    int numOfInput = 0;    //stores the number of values entered for a day
    int dayIndex = 0;    //counter for num of days for which data has been entered
    int count2 = 0;
    float sum = 0;
    
    inputValue = (char *)malloc(MAX_VALUE_SIZE*sizeof(char));
    if (inputValue == NULL){
		printf("Not able to allocate memory. Will exit.\n");
		return 1;
    }
    x=(char *)malloc(sizeof(char));
    if (x == NULL){
		printf("Not able to allocate memory. Will exit.\n");
		return 1;
    }
    while(dayIndex < MAX_DAYS){    //loop till data for max allowed number of days has been received
        numOfInput=0;
        validInput=false;
	    readings = (float *)malloc(READINGS_PER_DAY*sizeof(float));    //allocate memory to store float values
	    if (readings == NULL){
		    printf("Not able to allocate memory. Will exit.\n");
		    return 1;
	    }
        memset(readings,0.0,READINGS_PER_DAY);
        days[dayIndex]=readings;
        while( (*x = getchar()) != '\n' ){
            if (isspace(*x) && validInput){    //a useful input has been completed now
                *readings=atof(inputValue);    //convert to float and store at the allocated memory
                readings++;    //increment to the next pointer
                validInput=false;
                numOfInput++;
                if (numOfInput == READINGS_PER_DAY){
                    break;    //all the expected values for this day have been received
                }
            }
            if ( validInput ){
                count++;
                if (count > MAX_VALUE_SIZE) {
                    printf("You have entered a number greater than the allowed limit of %d. Will skip any more entries for this day.\n", MAX_VALUE_SIZE);
                    break;
                }
                strcat(inputValue,x);
            }
            if((isdigit(*x) || *x == '+' || *x == '-') && !validInput){    //start of a valid input
                validInput=true;
                memset(inputValue,'\0',MAX_VALUE_SIZE);
                strcat(inputValue,x);    //keep track of the start of a valid input value
                count=1;    //counting the length of input value
            }
        }
        if (validInput){    //copying the last input number
            *readings=atof(inputValue);    //convert to float and store at the allocated memory
            readings++;    //increment to the next pointer
            validInput=false;
            numOfInput++;
        }
        if(numOfInput==0){
            dayIndex--;    //just so that the last row, which is empty is not printed
            break;    //user entered new line char. So, pack up!
        }
        dayIndex++;
    }
    for(count=0;count<=dayIndex;count++){
        sum = 0;
        for(count2=0;count2<READINGS_PER_DAY;count2++){
            sum += *(days[count]+count2);
            printf("%.1f\t",*(days[count]+count2));
        }
        printf("Average Temp: %.1f",sum/READINGS_PER_DAY);
        printf("\n");
    }
}
