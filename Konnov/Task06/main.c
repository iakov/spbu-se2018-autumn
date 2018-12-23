#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "MD5.h"

void StopProgram(char *message, int value)
{
	printf("%s", message);
	exit(value);
}

struct HashTableItem
{
	char *key;
	int value;
};

struct HashTable
{
	struct HashTableItem *item;
	uint32_t size;
	uint32_t realSize;
};

struct HashTable NewTable(int size)
{
	struct HashTable newTable;
	newTable.size = size;
	newTable.realSize = 0;
	if(NULL == (newTable.item = calloc(size, sizeof(struct HashTableItem))))
	{
		StopProgram("cant allocate memory for item of a table in NewTable function",4);
	}
	return newTable;
}

void FreeTable(struct HashTable *table)
{
	uint32_t i;
	for(i = 0; i < table->size; i++)
	{
		if(table->item[i].key != NULL)
		{
			free(table->item[i].key);
		}
	}
	free(table->item);
	table->size = 0;
	table->realSize = 0;
}

int Get(struct HashTable *table, char *key)
{
	uint32_t *hash = calloc(4, sizeof(int));
	if(NULL == hash)
	{
		StopProgram("cant allocate memory for hash in Get function",4);
	}
	md5((uint8_t *) key, strlen(key), (uint8_t *) hash);
	uint32_t pos = hash[0] % table->size;
	while((table->item[pos].key != NULL) && (strcmp(key,table->item[pos].key) != 0))
	{
		pos++;
		if(pos == table->size)
		{
			pos = 0;
		}
	}
	free(hash);
	if(table->item[pos].key == NULL)
	{
		return 0;
	}
	return table->item[pos].value;
}

void IncreaseTable(struct HashTable *table, uint32_t newSize)
{
	struct HashTableItem *newTableItem = calloc(newSize, sizeof(struct HashTableItem));
	if(NULL == newTableItem)
	{
		StopProgram("cant allocate memory for a table in IncreaseTable function",4);
	}
	uint32_t i;
	for(i = 0; i < table->size; i++)
	{
		if(table->item[i].key != NULL)
		{
			uint32_t *hash = calloc(4, sizeof(int));
			if(NULL == hash)
			{
				StopProgram("cant allocate memory for hash in IncreaseTable function",4);
			}
			md5((uint8_t *) table->item[i].key, strlen(table->item[i].key), (uint8_t *) hash);
			uint32_t pos = hash[0] % newSize;
			while(newTableItem[pos].key != NULL)
			{
				pos++;
				if(pos == newSize)
				{
					pos = 0;
				}
			}
			free(hash);
			newTableItem[pos] = table->item[i];
		}
	}
	free(table->item);
	table->item = newTableItem;
	table->size = newSize;
}

void Add(struct HashTable *table, char *key, int value)
{
	uint32_t *hash = calloc(4, sizeof(int));
	if(NULL == hash)
	{
		StopProgram("cant allocate memory for a hash in Add function",4);
	}
	md5((uint8_t *) key, strlen(key), (uint8_t *) hash);
	uint32_t pos = hash[0] % table->size;
	while(table->item[pos].key != NULL && strcmp(key, table->item[pos].key) != 0)
	{
		pos++;
		if(pos == table->size)
		{
			pos = 0;
		}
	}
	free(hash);
	if(table->item[pos].key != NULL)
	{
		table->item[pos].value = value;
		free(table->item[pos].key);
		table->item[pos].key = key;
		return;
	}
	table->realSize++;
	if(table->realSize >= table->size / 2)
	{
		IncreaseTable(table, table->size * 2);
	}
	hash = calloc(4, sizeof(int));
	if(NULL == hash)
	{
		StopProgram("cant allocate memory for a hash in Add function",4);
	}
	md5((uint8_t *) key, strlen(key), (uint8_t *) hash);
	pos = hash[0] % table->size;
	while(table->item[pos].key != NULL)
	{
		pos++;
		if(pos == table->size)
		{
			pos = 0;
		}
	}
	table->item[pos].value = value;
	table->item[pos].key = key;
	free(hash);
}

int main(int argc, char *argv[])
{
	if(argv[0]) // anti-warning
	{
	}
	uint32_t i;
	if(argc != 1)
	{
		StopProgram("wrong number of args", 1);
	}
	struct HashTable table = NewTable(512);
	char input;
	int len = 0;
	char word[100000];
	char *buf = malloc(sizeof(char));
	while((input = getchar()) != EOF)
	{
		if((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z'))
		{
			word[len++] = input;
		}
		else if(len > 0 && (input == '-' || input == '\''))
		{
			word[len++] = input;
		}
		else if(len != 0)
		{
			while(word[len - 1] == '\'' || word[len - 1] == '-')
			{
				word[len--] = '\0';
			}
			word[len] = '\0';
			if(NULL == (buf = (char *) calloc(strlen(word) + 1, sizeof(char))))
			{
				StopProgram("cant allocate memory for buffer in main function",4);
			}
			strcpy(buf,word);
			Add(&table, buf, Get(&table, buf) + 1);
			len = 0;
		}
	}
	int maxWord = 0;
	for(i = 0; i < table.size; i++)
	{
		if(table.item[i].key != NULL)
		{
			printf("%s %i\n", table.item[i].key, table.item[i].value);
			if(table.item[i].value > maxWord)
			{
				maxWord = table.item[i].value;
			}
		}
	}
	for(i = 0; i < table.size; i++)
	{
		if(table.item[i].key != NULL && table.item[i].value == maxWord)
		{
			fprintf(stderr, "%s %i\n", table.item[i].key, table.item[i].value);
		}
	}
	FreeTable(&table);
	return 0;
}
