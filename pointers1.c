/*This program accesses elements of an array using the array name,
*and using pointers.
*/
#include <stdio.h>
#define NROWS 3
#define NCOLS 3
void main(){
long array[NROWS][NCOLS]={
	{10L,11L,12L},
	{20L,21L,22L},
	{30L,31L,32L}
};
long *plong=NULL;
int index=0;
int index2=0;
/*The significance of next line is that plong is a pointer to a long
* while array  is a pointer to a pointer to a long. Hence, we 
*dereference array before assigning it to plong.
* This line could also have been written as plong=&array[0][0]
*/
plong=*array;
printf("Printing the array elements using pointer.\n");
printf("Address in decimal\tAddress in hex\tArray element\n");
for(index=0;index<NROWS*NCOLS;index++){
	printf("%d\t%p\t%ld\n",(plong+index),(plong+index),*(plong+index));
}
/*Notice the use of *array inside the for loop. This is an important
*difference between pointer to a data-type vs array name for an array 
*of that data-type. Array names can have muliple levels of indirection,
*so you may need to put muliple * operators before an array name, to use
*it for accessing the element.
*/
printf("Printing the array elements using array name.\n");
printf("Address in decimal\tAddress in hex\tArray element\n");
for(index=0;index<NROWS*NCOLS;index++){
	printf("%d\t%p\t%ld\n",(*array+index),(*array+index),*(*array+index));
}
}
