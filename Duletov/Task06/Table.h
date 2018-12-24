#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cell {
  long int hash;
  char key[50];
  int value;
  struct Cell *next;
};


struct Cell *Chains[100000] = {0};
int size, counter, counter2;
char frequent[50];

void makeTable(){
	size = 1000;
	printf("Created successfully\n");
}

void copies(struct Cell *i, char *key){
	if(strcmp(i->key,key)==0){
		i->value ++;
		counter=1;
	}
	else{
		if(i->next != 0){
			copies(i->next, key);
		}
		else{
			return;
		}
	}
}

void insert(char *key, long int hash){
	long int value = hash % size;
	if(Chains[value]==0){
		Chains[value] = (struct Cell*)malloc(sizeof(struct Cell));
		Chains[value]->hash = hash;
		strcpy(Chains[value]->key, key);
		Chains[value]->value = 1;
	}
	else{
	 	copies(Chains[value], key);
	 	if(counter==1){
	 		counter=0;
	 		return;
	 	}
		struct Cell *buf = Chains[value];
		Chains[value] = (struct Cell*)malloc(sizeof(struct Cell));
		Chains[value]->hash = hash;
		strcpy(Chains[value]->key, key);
		Chains[value]->value = 1;
		Chains[value]->next = buf;
	}
}

void freeChain(struct Cell *i){
		if(i->next != 0)
		freeChain(i->next);
		free(i);
}

void clearTable(){
	int i;
	for(i=0;i<size;i++){
		if(Chains[i] != 0)
		freeChain(Chains[i]);
		Chains[i] = NULL;
	}
	size=0;
	printf("Cleared successfully\n");
}

int seek(struct Cell *i, char *key){
	if(strcmp(i->key,key)==0){
		return i->value;
	}
	else{
		if(i->next != 0){	
		 return seek(i->next, key);
		}
		else{
			return 2;
		}
	}
}

int get(char *key, long int hash){
	long int value = hash % size;
	if(Chains[value]!=0){
		return seek(Chains[value], key);
	}
	else{
		return 1;
	}
}

void count(struct Cell *i){
	counter++;
	if(i->next!=0){
		count(i->next);
	}
	else{
		return;
	}
}

void statistic(){
	long int z = 0;
	int i;
	for(i=0;i<size;i++){
		if(Chains[i]!=0)
		count(Chains[i]);
		printf("Chain %d contain %d keys\n", i, counter);
		z = z + counter;
		counter = 0;
	}
	printf("There are %li keys in table\n", z);
}

void iteration(struct Cell *i){
	printf("Key %s Hash %li Value %d\n", i->key, i->hash, i->value);
	if(i->next!=0){
		iteration(i->next);
	}
	else{
		return;
	}
}

void iterate(){
	int i;
	for(i=0;i<size;i++){
		if(Chains[i]!=0)
		iteration(Chains[i]);
	}
}

void frequency(struct Cell *i){
	if(i->next != 0){
		frequency(i->next);
		if(i->value > counter2){
			counter2 = i->value;
			strcpy(frequent, i->key);
		}
	}
	else{
		if(i->value > counter2){
			counter2 = i->value;
			strcpy(frequent, i->key);
		}
	}
}

void bookanalise(){
	int i, z=0;
	counter=0;
	counter2 = 0;
	for(i=0;i<size;i++){
		if(Chains[i] != 0){
			if(Chains[i] != 0)
			count(Chains[i]);
			frequency(Chains[i]);
			z = z + counter;
			counter = 0;
		}
	}
	printf("There are %d different words. The most frequent word is \"%s\" with %d mentions\n", z, frequent, counter2);
}
