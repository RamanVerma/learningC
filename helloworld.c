#include <stdio.h>
int main(){
//define variables
float in_temp = 0;
unsigned short int choice = 0;
//Ask for user input
printf("Specify the type of conversion: 1 for Celsius to fahrenheit, 2 for Fahrenheit to Celsius\n");
scanf("%hd",&choice);
if (choice > 1){
printf("Wrong input.");
return -1;
}
printf("Enter the input temperature\n");
scanf("%f",&in_temp);
if (choice == 0){
printf("%f degree Celsius corresponds to %f degree fahrenheit\n",in_temp,in_temp*1.8)+32;
}else {
printf("%f degree Fahrenheit corresponds to %f degree Celsius\n",in_temp,((in_temp-32)*5)/9);
}
return 0;
}
