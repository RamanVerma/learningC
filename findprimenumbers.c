/*This program finds a user specified number of prime
* numbers. It uses dynamic allocation of memory. And 
* uses the fundamental tenet that a number 'x' is prime
* if it not divisible by any prime number found before 
* itself.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void main(){
int numofprimes=0;
unsigned long *pulong=NULL;
int primesfound=3;
int current=0;
bool isprime=true;
while(numofprimes<4){
	printf("Enter the number of primes you want to know.\n");
	scanf("%d",&numofprimes);
	if(numofprimes<4){
		printf("You should enter a number greater than 3.\n");
	}
}
pulong=(unsigned long *)malloc((numofprimes+3)*sizeof(unsigned long));
if(pulong==NULL){
	printf("Not enough heap memory with your program.Exiting now.\n");
	exit;
}
*pulong=2U;
*(pulong+1)=3U;
*(pulong+2)=5U;
unsigned long n=7U;
while(primesfound<(numofprimes+3)){
	isprime=true;
	for(current=0;current<primesfound;current++){
		if(n%(*(pulong+current))==0){
			isprime=false;
			break;
		}
	}
	if(isprime){
		primesfound++;
		*(pulong+primesfound-1)=n;
	}
	n++;
}
for(current=0;current<primesfound;current++){
	printf("%lu\t",*(pulong+current));
}
printf("\n");
}
