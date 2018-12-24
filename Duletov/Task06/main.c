#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Table.h"
#include "Hash.h"

int main(){
	makeTable();
	int i=0;
	long int hash_value;
	char word[50] = "";
	char symbol;
	while((symbol = getchar()) != EOF){
  	if((symbol<='Z' && symbol>='A') || (symbol<='z' && symbol>='a') || symbol=='-' || symbol=='\''){
    	word[i++] = symbol;
    }
    else{
    	if(i>0){
      	word[i]='\0';
        hash_value = hash(word);
				insert(word, hash_value);
    		i = 0;
     	}
    }
  }
  hash_value = hash(word);
	insert(word, hash_value);
  iterate();
	bookanalise();
	return 0;
}
