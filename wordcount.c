#include <stdio.h>
#include <string.h>

void main(){
//Define variables
#define TEXTLEN 10000
#define LINEBUF 100
#define MAXWORDS 50
#define MAXWORDLEN 20
char eot='*';
char line[LINEBUF];
char text[TEXTLEN+1];
char words[MAXWORDS][MAXWORDLEN];
char tmp[MAXWORDLEN];
int wordcount[MAXWORDS];
int textlencount=0;
int tmplencount=0;
int count=0;
//Read the text from standard input and store in an array
while(1){
	fgets(line,LINEBUF,stdin);
	for(count=0;count<LINEBUF;count++){
		if(line[count]=='*' || textlencount==10000 || line[count]=='\0'){
			break;
		}
		if(isalpha(line[count])){
			text[textlencount++]=line[count];
		}else{
			text[textlencount++]=' ';
		}
	}
	if(line[count]=='*' || textlencount==10000){
		break;
	}

}
printf("Your text in one line---\n");
printf("%s\n",text);
printf("%d\n",textlencount);
//Do stuff
for(count=0;count<MAXWORDS;count++){
	words[count][0]='\0';
	wordcount[count]=0;
}
int count1=0;
for(count=0;count<textlencount;count++){
		if(isalpha(text[count]) && tmplencount<MAXWORDLEN-1){
			tmp[tmplencount++]=text[count];
		}else{
			tmp[tmplencount]='\0';
			tmplencount=0;
			for(count1=0;count1<MAXWORDS;count1++){
				if(strcmp(words[count1],tmp)==0){
					wordcount[count1]++;
					break;
				}else if(words[count1][0]=='\0'){
					strcpy(words[count1],tmp);
					wordcount[count1]++;
					break;
				}
			}
		}
}
//Print results
for(count=0;count<MAXWORDS;count++){
	if(words[count][0]=='\0'){
		break;
	}
	printf("%s | %d\n",words[count],wordcount[count]);
}
}
