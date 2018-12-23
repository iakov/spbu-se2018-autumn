#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MD5.h"

void punctuationExtermination(char  word[])
{
	int length = strlen(word);
	int newPos = 0;
	char *buff = (char *) malloc(length * sizeof(char));
	if (buff == NULL)
		{
			fprintf(stderr, "Out of memory (buff)\n");
			exit(4);
		}
	for (int pos = 0; pos < length; ++pos)
	{
		if (((word[pos] >= 'a') && (word[pos] <= 'z')) ||
			((word[pos] >= 'A') && (word[pos] <= 'Z')) ||
			(((word[pos] == '\'') || (word[pos] == '-')) &&
			(pos != 0) && (pos != length - 1)))
		{
			buff[newPos] = (word[pos]);
			++newPos;
		}

	}
	buff[newPos] = '\0';
	strcpy(word, buff);
	free(buff);
}

typedef struct hashSlot
{
	char *key;
	int value;
	struct hashSlot *ptr; // realization of list
} Node;

typedef struct
{
	Node **table;
	int size;
	int *depth;
} HashTable;

HashTable hashTable;

uint32_t getIndex(HashTable *hashTable, char *key)
{
   uint32_t *hash;
   if ((hash = (uint32_t*) calloc(4, sizeof(uint32_t))) == NULL)
   {
   	fprintf(stderr, "Our of memory (hash(getIndex))\n");
   	exit(4);
   };
   md5((uint8_t *) key, strlen(key), (uint8_t*) hash);
   uint32_t index = 0;
 //  for (int i = 0; i < 4; ++i)
//	   index = (index * 16 + (int) hash[i]) % hashTable->size;
   index = hash[0];
   free(hash);
   return index % hashTable->size;
}

void createHashTable(HashTable *hashTable, int size)
{
	if ((hashTable->table = calloc(size, sizeof(Node *))) == NULL)
	{
		fprintf(stderr, "Out of memory (hashTable.table)\n");
		exit(4);
	}
	if ((hashTable->depth = calloc(size, sizeof(int))) == NULL)
	{
		fprintf(stderr, "Out of memory (hashTable.depth)\n");
		exit(4);
	};
		hashTable->size = size;
}

Node * nextNode(HashTable * hashTable, Node * present)
{
	uint32_t index;
	if (present == NULL)
	{
		index = 0;
		while (hashTable->table[index] == NULL && (int) index < hashTable->size)
			++index;
		if ((int) index >= hashTable->size)
			return NULL;
		return hashTable->table[index];
	}
	if (present->ptr == NULL)
	{
		index = getIndex(hashTable, present->key) + 1;
		while (hashTable->table[index] == NULL && (int) index < hashTable->size)
			++index;
		if ((int) index >= hashTable->size)
			return NULL;
		return hashTable->table[index];
	}
	return present->ptr;
}

void freeHashTable(HashTable *hashTable)
{
	for (int i = 0; i < hashTable->size; ++i)
	{
		while (hashTable->table[i] != NULL)
		{
			hashTable->table[i] = hashTable->table[i]->ptr;
			free(hashTable->table[i]);
			hashTable->table[i] = NULL;
			hashTable->depth[i] = 0;
		}
	}
	free(hashTable->table);
}

int find(HashTable *hashTable, char *key)
{
	uint32_t index = getIndex(hashTable, key);
	Node* present = hashTable->table[index];
	while (present != NULL)
	{
		if (strcmp(present->key, key) == 0)
			return present->value;
		present = present->ptr;
	}
	return 0;
}

void add(HashTable *hashTable, char *key)
{
	uint32_t index = getIndex(hashTable, key);
	Node* present = hashTable->table[index];
	while (present != NULL)
	{
		if (strcmp(present->key, key) == 0)
			break;
		present = present->ptr;
	}
	if (present != NULL)
	{
		present->value += 1;
		return;
	}
	Node *newSlot = malloc(sizeof(Node));
	if (newSlot == NULL)
	{
		fprintf(stderr, "Out of memory (newSlot)\n");
		exit(4);
	}
	hashTable->depth[index]++;
	newSlot->key = key;
	newSlot->value = 1;
	if (hashTable->table[index] == NULL)
	{
		newSlot->ptr = NULL;
		hashTable->table[index] = newSlot;
	}
	else
	{
		newSlot->ptr = hashTable->table[index]->ptr;
		hashTable->table[index]->ptr = newSlot;
	}
}

void printStats(HashTable *hashTable)
{
	int maxValue = 0;
	for (int i = 0; i < hashTable->size; ++i)
	{
		Node *present = hashTable->table[i];
		while (present != NULL)
		{
			if (present->value > maxValue)
				maxValue = present->value;
			printf("%s %d\n", present->key, present->value);
			present = present->ptr;
		}
	}
	for (int i = 0; i < hashTable->size; ++i)
	{
		Node *present = hashTable->table[i];
		while (present != NULL)
		{
			if (present->value == maxValue)
			fprintf(stderr, "%s %d\n", present->key, present->value);
			present = present->ptr;
		}
	}
}
/*
void printExtraStats(HashTable *hashTable)
{
    int maxValue = 0;
	int maxDepth = 0;
	int totalAmount = 0;
	Node * maxNode = NULL;
	for (int i = 0; i < hashTable->size; ++i)
	{
		Node * present = hashTable->table[i];
		if (hashTable->depth[i] > maxDepth)
			maxDepth = hashTable->depth[i];
		while (present != NULL)
		{
			totalAmount += present->value;
			if (present->value > maxValue)
			{
				maxValue = present->value;
				maxNode = present;
			}
			present = present->ptr;
		}
	}
	FILE* f = fopen("Results.txt", "w");
	fprintf(f, "Amount of different words = %d\n", totalAmount);
	fprintf(f, "Most frequent word = %s has met %d times\n", maxNode->key, maxNode->value);
	fprintf(f, "Max depth of list is %d for size = %d\n", maxDepth, hashTable->size);
}*/

int main()
{
	int size = 1000;
	char word[500];
	char *buffer;
	createHashTable(&hashTable , size);
	//scanf("%s", word);
	//FILE *f = fopen(word, "r");
	//while (!feof(f))
	for (; scanf("%s", word) != EOF; )
	{
		if ((buffer = malloc(500*sizeof(char))) == NULL)
        {
            fprintf(stderr, "Out of memory (buffer)\n");
            exit(4);
        }
        //fscanf(f, "%s", word);
		//if (strcmp(word, "stop") == 0)
		//	break;
		punctuationExtermination(word);
		strcpy(buffer, word);
		if (strlen(buffer) > 0)
        {
            add(&hashTable, buffer);
        }
        else
            free(buffer);
	}
	printStats(&hashTable);
	//printExtraStats(&hashTable);
	freeHashTable(&hashTable);
	return 0;
}
