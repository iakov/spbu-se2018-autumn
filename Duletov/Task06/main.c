#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Table.h"
#include "Hash.h"

int main(){
	makeTable();
	int i;
	long int hash_value;
	char word[50] = "";
	char symbol;
	char *buf;
	while((symbol = getchar()) != EOF){
  	if((symbol<='Z' && symbol>='A') || (symbol<='z' && symbol>='a') || symbol=='-' || symbol=='\''){
    	word[i++] = symbol;
    }
    else{
    	if(i>0){
      	word[i]='\0';
       	buf=(char *)calloc(strlen(word) + 1, sizeof(char));
				if(buf == NULL){
					
     			printf("Failed to malloc memory\n");
        	return 1;
        }
        strcpy(buf, word);
        hash_value = hash(word);
				insert(word, hash_value);
    		i = 0;
     	}
    }
  }
  iterate();
	bookanalise();
	return 0;
}
