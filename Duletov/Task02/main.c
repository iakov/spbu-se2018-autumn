#include <stdio.h>
#include <stdlib.h>

extern int sort(int j, int *number);

int main(int argc,char * argv[]){
int number[100];
int i,j = 0,buf=0, e, to=127, from=-128,z;
char enter[200];
//array to zero
for (i=0;i<100;i++){
	number[i]=0;
}
//reading from and to
i=1;
for (i=1;i<argc;i++){
	if ((argv[i][0]=='-') && (argv[i][1]=='-')){
	if ((argv[i][2]=='t') && (argv[i][3]=='o')){
		j=5;
		while (!argv[i][j]== '\0'){
			e = argv[i][j]-'0';
			buf = buf * 10 + e;
			j++;
		}
		to = buf;
		buf = 0;
	}
	if ((argv[i][2]=='f') && (argv[i][3]=='r') && (argv[i][4]=='o') && (argv[i][5]=='m')){
		j=7;
		while (!argv[i][j]== '\0'){
			e = argv[i][j]-'0';
			buf = buf * 10 + e;
			j++;
		}
		from = buf;
		buf = 0;
	}
	}
}
j=0;
//reading string
i=-1;
	scanf("%[^\n]", &enter);
//splitting string into numbers with to/from processing
do {
	i++;
	if ((enter[i]==' ') || (enter[i]=='\0')){
		if (number[j] <= from){
			printf("%d ", number[j]);
			number[j]=0;
		}
		else if (number[j] >= to){
			fprintf(stderr, "%d ", number[j]);
			number[j]=0;
		}
		else{
		j++;
		}
		buf=0;
	}
	else{
		e = enter[i]-'0';
		buf = buf * 10 + e;
		number[j] = buf;
	}
} while (!enter[i] == '\0');
//
z = sort(j, number);
return z;
}
