#include <stdio.h>
#include <string.h>
int main(){
char buf[5];
fgets(buf,5,stdin);
printf("%s\n",buf);
printf("%ld\n",strlen(buf));
return 0;
}
