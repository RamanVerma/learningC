#include <stdio.h>
#include <string.h>

void main(){
char words[10][5]={"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
char words2[10][7]={"Zero","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninty"};
char words3[10][9]={"Ten","Eleven","Twelve","Thirteen","Forteen","Fifteen","Sixteen","Seventeen","Eighteen","Ninteen"};
char in[4];
int count=0;
fgets(in,4,stdin);
int number=atoi(in);
int quotient=number/100;
int remainder=number%100;
if(quotient!=0){
printf("%s hundred and ",words[quotient]);
}
quotient=remainder/10;
remainder=remainder%10;
if(quotient>1){
printf("%s ",words2[quotient]);
}
if(quotient==1){
printf("%s\n",words3[remainder]);
}else{
printf("%s\n",words[remainder]);
}
}
