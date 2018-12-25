#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "md5.h"

void ForcedExit(char *message, int errcode) {
	printf("%s\n", message);
	exit(errcode);
}
#define CHECK_NULL(value) if(value == NULL) ForcedExit("Error no memory", 4) //copied by Daniel Log, because it's so nice


#define MAXWORD 100


struct list
{
    int value;
    char *key;
    struct list *next;
};


struct hash_t
{    
	struct list **arr_lst;
    int size, allwords;
	int *listcount;
};


void init(int size, struct hash_t *table)
{
	table->size = size;
	
	table->arr_lst = (struct list**)calloc(size, sizeof(struct list*));
	
	CHECK_NULL(table->arr_lst);
	
	table->listcount = (int*)calloc(size, sizeof(int));
	
	CHECK_NULL(table->listcount);
	
	table->allwords = 0;

}


int hashFunc(char *key, struct hash_t *table)
{
	
	uint8_t *res;

	res = (uint8_t*)calloc(16, sizeof(uint8_t));
	
	CHECK_NULL(res);
	
	size_t len = strlen(key);

	md5((uint8_t*)key, len, res);
	
	uint32_t newkey = res[0];
	
	free(res);
	
	return newkey % table->size;
}


struct list *listSearch(struct hash_t *table, char *search_key, int hash_i)
{
	struct list *l = table->arr_lst[hash_i];
	
	while (l != NULL)
	{
		if (strcmp(l->key, search_key) == 0)
		{
			return l;
		}
		l = l->next;
	}
	
	return NULL;
}



void hashAdd(struct hash_t *table, char *add_key)
{
	int hash_i = hashFunc(add_key, table);
	struct list *l = table->arr_lst[hash_i];
	struct list *last = NULL;
	while (l != NULL)
	{
		if (strcmp(l->key, add_key) == 0)
			break;
		last = l;
		l = l->next;
	}
	if (l != NULL)
	{
		l->value += 1;
		return;
	}
	if (last == NULL)
	{
		table->arr_lst[hash_i] = (struct list*)malloc(sizeof(struct list));
		CHECK_NULL(table->arr_lst[hash_i]);
		l = table->arr_lst[hash_i];
	}
	else
	{
		last->next = (struct list*)malloc(sizeof(struct list));
		if (last->next == NULL)
		{
			CHECK_NULL(last->next);
		}
		l = last->next;
	}
	l->value = 1;
	l->key = (char *)malloc((strlen(add_key) + 1) * sizeof(char));
	if (l->key == NULL)
	{
		CHECK_NULL(l->key);
	}
	strcpy(l->key, add_key);
	l->next = NULL;
	table->listcount[hash_i]++;

}

	
int getvalue(struct hash_t *table, char *key)
{
	int hash_i = hashFunc(key, table);
	
	struct list *find = listSearch(table, key, hash_i);

	if (find != NULL)
	{
		return find->value;
	}

	return 0;
}

void printStat(struct hash_t *table)
{
	int mostFreq = 0;
	for (int i = 0; i < table->size; i++)
	{
		struct list *current = table->arr_lst[i];
		while (current != NULL)
		{
			if (current->value > mostFreq)
			{
				mostFreq = current->value;
			}
			fprintf(stdout, "%s %d\n", current->key, current->value);
			current = current->next;
		}
	}
	for (int i = 0; i < table->size; i++)
	{
		struct list *current = table->arr_lst[i];
		while (current != NULL)
		{
			if (current->value == mostFreq)
				fprintf(stderr, "%s %d\n", current->key, current->value);
			current = current->next;
		}
	}
}

void hashDelete(struct hash_t *table)
{
	for (int i = 0; i < table->size; ++i)
	{
		while (table->arr_lst[i] != NULL)
		{
			struct list *l = table->arr_lst[i];
			table->arr_lst[i] = table->arr_lst[i]->next;
			free(l->key);
			free(l);
		}
	}
	free(table->arr_lst);
	free(table->listcount);
}

int main()
{

	int size = 10000;

	struct hash_t table; //show init
	
	init(size, &table);

	char word[MAXWORD];
	char *buffer;
	char symbol;
	int count = 0;


	while ((symbol = getchar()) != EOF)
	{
		if ((symbol <= 'Z' && symbol >= 'A') || (symbol <= 'z' && symbol >= 'a') || (symbol == '-' || symbol == '\''))
		{
			word[count++] = symbol;
		}
		else if (count != 0)
		{
			while (word[count - 1] == '-' || word[count - 1] == '\'') 
			{
				word[count--] = '\0';
			}
			word[count] = '\0';
			buffer = (char *)calloc((strlen(word) + 1), sizeof(char));
			CHECK_NULL(buffer);
			strcpy(buffer, word);
			hashAdd(&table, buffer);
			free(buffer);
			count = 0;
		}

	}
	
	printStat(&table);
	hashDelete(&table);

	return 0;
}
