#include<stdio.h>

/*
* Function prototypes
*/
double add(double, double); /*return the sum of two parameters*/
double sub(double, double); /*return the difference of two parameters*/
double mul(double, double); /*return the product of two parameters*/
/*
* array op function
* Parameters: array of data values of type double, size of array,
* function pointer that returns double and accepts two values of
* type double
*/
double array_op(double [], int, double(*)(double, double));


/*
* add function: adds the two parameters
*/
double add(double a, double b){
    return (a + b);
}
/*
* sub function: subtracts the two parameters
*/
double sub(double a, double b){
    return (a - b);
}
/*
* mul function: multiplies the two parameters
*/
double mul(double a, double b){
    return (a * b);
}
/*
* array_op function: performs pfun operation on the array
*/
double array_op(double array[], int size, double(*pfun)(double, double)){
    int x = 0;
    double ret = 0.0;
    for(x = 0;x < size;){
        double a = array[x++];
        double b = array[x++];
        ret += pfun(a, b);
    }
    return ret;
}
/*
* main function
*/
void main(){
    double array[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    /*Declaring a pointer to a function*/
    double(*pfun)(double, double);
    double result = 0.0;
    /*Calling array_op with add function*/
    pfun = add;
    result = array_op(array, 10, pfun);
    printf("Result of array_op(array, 10, add) is %f\n", result);
    /*Calling array_op with sub function*/
    pfun = sub;
    result = array_op(array, 10, pfun);
    printf("Result of array_op(array, 10, sub) is %f\n", result);
    /*Calling array_op with mul function*/
    result = array_op(array, 10, mul);
    printf("Result of array_op(array, 10, mul) is %f\n", result);
    return;
}
