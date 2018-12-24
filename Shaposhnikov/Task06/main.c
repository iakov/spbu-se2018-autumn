#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MD5.h"

#define MAX_WORD_LENGTH 500
#define MAX_TABLE_SIZE 1000

/*
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
*/

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
	if ((hashTable->table = (Node **) calloc(size, sizeof(Node *))) == NULL)
	{
		fprintf(stderr, "Out of memory (hashTable.table)\n");
		exit(4);
	}
	if ((hashTable->depth = (int*) calloc(size, sizeof(int))) == NULL)
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
			Node *present = hashTable->table[i];
			hashTable->table[i] = hashTable->table[i]->ptr;
			free(present->key);
			free(present);
		}
	}
	free(hashTable->table);
	free(hashTable->depth);
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
	Node* previous = NULL;
	while (present != NULL)
	{
		if (strcmp(present->key, key) == 0)
			break;
		previous = present;
		present = present->ptr;
	}
	if (present != NULL)
	{
		present->value += 1;
		return;
	}
	if (previous == NULL)
	{
		hashTable->table[index] = (Node *) malloc(sizeof(Node));
		if (hashTable->table[index] == NULL)
		{
			fprintf(stderr, "Out of memory (table[%s]", key);
			exit(4);
		}
		present = hashTable->table[index];
	}
	else
	{
		previous->ptr = (Node *) malloc(sizeof(Node));
		if (previous->ptr == NULL)
		{
			fprintf(stderr, "Out of memory (previous->ptr");
			exit(4);
		}
		present = previous->ptr;
	}
	present->value = 1;
	present->key = (char *) malloc((strlen(key)+1)*sizeof(char));
	if (present->key == NULL)
	{
		fprintf(stderr, "Out of memory (present>key)");
		exit(4);
	}
	strcpy(present->key, key);
	present->ptr = NULL;
	hashTable->depth[index]++;

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
	int size = MAX_TABLE_SIZE;
	char word[MAX_WORD_LENGTH];
	char buffChar;
	createHashTable(&hashTable , size);
	int bufPos = 0;	
	while ((buffChar = getchar()) != EOF)
	{
		if(buffChar == '=')
			break;
		if ((buffChar >= 'A'&& buffChar <= 'Z') || (buffChar >= 'a' && buffChar <= 'z'))
		{
			word[bufPos] = buffChar;
			bufPos++;
		}
		else if (bufPos > 0)
			{
				word[bufPos] = '\0';
				char *key = (char*) malloc((strlen(word)+1)*sizeof(char));
				if (key == NULL)
				{
					fprintf(stderr, "Out of memory (key)\n");
					exit(4);
				}
				strcpy(key, word);
				add(&hashTable, key);
				bufPos = 0;
				free(key);
			}
	}
	printStats(&hashTable);
	//printExtraStats(&hashTable);
	freeHashTable(&hashTable);
	return 0;
}
