/*This is a calculator program, using pointers.
It parses the input expression left to right, and
does not follow the operator precedence rules.
*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#define EXP_LEN 20    //MAX Length for the input expression

int main(){

char Expression[EXP_LEN];    //input expression
float lastresult = 0;    //last result
float interresult = 0;    //intermediate result
char *strop = NULL;    //string rep of operands
float op1 = 0;    //operand 1
bool op1set = false;    //operand 1 is found or not
float op2 = 0;    //operand 2
bool op2set = false;    //operand 2 has been found or not
char operator = NULL;    //operator
bool operatorset = false;    //operator has been found or not
char *parser = NULL;    //pointer to parse the expression
int index = 0;
int len = 0;    //length of operand in string representation
char *tmp = NULL;    //temp pointer to hold start position of operands
bool more = true;    //boolean to indicate quit/continue the program
bool error = false;    //boolean to indicate error while parsing input

while(more){    //endless loop
    printf("Enter an expression\n");    //get the first operand
    fgets(Expression,EXP_LEN,stdin);
    parser = Expression;
    index = 0;
    while(index < EXP_LEN){
        if (*parser == '='){
            if (!op1set){
                op1 = lastresult;
                op1set = true;
            } else if(operatorset){
                op2 = lastresult;
                op2set = true;
            } else{
                printf("Misplaced = sign. Wrong input expression.\n");
                error = true;
            }
            index++;
            parser++;
        } else if (*parser=='+' || *parser == '-' || isdigit(*parser)){    //find a '+' or '-' sign
            if(!op1set){    //operand 1 is not set
                tmp = parser;
                len = 1;
                parser++;
                index++;
                while((index < EXP_LEN) && (isdigit(*parser) || *parser == '.')){
                    len++;
                    parser++;
                    index++;
                }
                strop = (char *)malloc(len*sizeof(char));
                if (!strop){
                    printf("Out of Memory. Program will quit.\n");
                    return 1;
                }
                strncpy(strop,tmp,len);
                op1 = atof(strop);    //Assuming input data is correct
                free(strop);
                strop = NULL;
                tmp = NULL;
                op1set = true;
            } else if(!operatorset){    //operand 1 is set but operator has not been set
                operator = *parser;
                operatorset = true;
                parser++;
                index++;
            } else if(!op2set){    //operand 1 is set but operand 2 is not
                tmp = parser;
                len = 1;
                parser++;
                index++;
                while((index < EXP_LEN) && (isdigit(*parser) || *parser == '.')){
                    len++;
                    parser++;
                    index++;
                }
                strop = (char *)malloc(len*sizeof(char));
                if (!strop){
                    printf("Out of Memory. Program will quit.\n");
                    return 1;
                }
                strncpy(strop,tmp,len);
                op2 = atof(strop);    //Assuming input data is correct
                free(strop);
                strop = NULL;
                tmp = NULL;
                op2set = true;
            }
        } else if (*parser == '*' || *parser == '/' || *parser == '^' || *parser == '%'){
            if (!operatorset){
                operator = *parser;
                operatorset = true;
                index++;
                parser++;
            } else {
                printf("Wrong input string.\n");
                break;
            }
        } else if(*parser != '\n'){
            error = true;
            printf("Wrong input string.\n");
            break;
        }
        if (op1set && operatorset && op2set){    //calculate the intermediate result
            switch(operator){
                case '+':
                    op1 = op1 + op2;
                    break;
                case '-':
                    op1 = op1 - op2;
                    break;
                case '*':
                    op1 = op1 * op2;
                    break;
                case '/':
                    if (op2 != 0){
                        op1 = op1 / op2;
                    } else {
                        error = true;
                        printf("Divide by zero error.\n");
                    }
                    break;
                case '^':
                    op1 = pow(op1,op2);
                    break;
                case '%':
                    if (op2 != 0){
                        op1 = (long)op1 % (long)op2;
                    } else {
                        error = true;
                        printf("Divide by zero error.\n");
                    }
                    break;
                default:
                    printf("Wrong operator %c\n", operator);
                    error = true;
                    break;
            }
            op2 = 0;
            operatorset = false;
            op2set = false;
        }
        if(*parser == '\n'){
            if (op1set){
                lastresult = op1;
                op1 = 0;
                op1set = false;
                printf("%s = %lf\n",Expression,lastresult);
            } else {
                more = false;
            }
            break;
        }
        if (error){
            op1 = 0;
            op2 = 0;
            op1set = false;
            operatorset = false;
            op2set = false;
            error = false;
            break;
        }
    }
    //parse it and compare if it is == quit
}
}
