#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "md5.h"
#include "main.h"

int main()
{
    hash_table_var table = InitTable(128);
    const int max_word_length = 4096;
    char buffer[max_word_length];    
    int word_length = 0, words_counter = 0;
    char ch = getchar();

    while(ch != EOF)
    {
        if ((ch >= 'a' && ch <='z') || (ch >= 'A' && ch <= 'Z'))
        {
        	word_length++;
            buffer[word_length] = ch;
        }
        else if (word_length > 0)
        {
            buffer[word_length] = '\0';
            char *word = (char*)calloc(word_length + 1, sizeof(char));
            if(word == NULL)
            {
				PrintError("I can not allocate memory in Main for \"*word\"", 4);
            }
            strncpy(word, buffer, word_length);
            Add(&table, word);
            word_length = 0;
        }
        ch = getchar();
    }

    int counter_of_maximum = 0;

    for(unsigned int i = 0; i < table.capacity; ++i)
    {
        if(table.data[i].key != NULL)
        {
            printf("%s %d\n", table.data[i].key, table.data[i].value);

            ++words_counter;
            if(table.data[i].value > counter_of_maximum)
            {
                counter_of_maximum = table.data[i].value;
            }
        }
    }
    for(unsigned int i = 0; i < table.capacity; ++i)
    {
        if((table.data[i].key != NULL) && (table.data[i].value == counter_of_maximum))
        {
            fprintf(stderr, "%s %d\n", table.data[i].key, table.data[i].value);
        }
    }

    FreeTable(&table);

    return 0;
}

hash_table_var InitTable(int init_capacity)
{
    hash_table_var table;
    table.data = (table_item_var*)calloc(init_capacity, sizeof(table_item_var));
    if(table.data == NULL)
    {
		PrintError("I can not allocate memory in Main for \"table.data\"", 4);
    }
    table.capacity = init_capacity;
    table.size = 0;
    return table;
}

void Resize(hash_table_var *table)
{
    int resized_capacity = 2 * table->capacity;
    table_item_var *resized_data = (table_item_var*)calloc(resized_capacity, sizeof(table_item_var));
    if(resized_data == NULL)
    {
		PrintError("I can not allocate memory in Main for \"*resized_data\"", 4);
    }

    for(int i = 0; i < table->capacity; ++i)
    {
        if(table->data[i].key != NULL)
        {
            int position = find_position(resized_data, resized_capacity, table->data[i].key);
            resized_data[position] = table->data[i];
        }
    }

    free(table->data);

    table->data = resized_data;
    table->capacity = resized_capacity;
}

void Add(hash_table_var *table, char *key)
{
    int position = find_position(table->data, table->capacity, key);
    if( (table->data[position].key == NULL) || (strcmp(table->data[position].key, key)) )
    {
        table->size++;
        if(table->size > table->capacity / 2)
        {
           Resize(table);
        }
        position = find_position(table->data, table->capacity, key);
        table->data[position].key = key;
        table->data[position].value = 1;
    }
    else
    {
        ++table->data[position].value;
        free(key);
    }
}

int find_position(table_item_var *data, int capacity, char *key)
{
    uint8_t *hash = (uint8_t*)malloc(16 * sizeof(uint8_t));
    if(hash == NULL)
    {
		PrintError("I can not allocate memory in Main for \"*hash\"", 4);
    }
    int position = 0;
    md5((uint8_t*)key, strlen(key), hash);
    for(int i = 0; i < 16; ++i)
    {
        position += (int)hash[i] % capacity;
    }
    position %= capacity;

    free(hash);

    while( (data[position].key != NULL) && (strcmp(key, data[position].key)) )
    {
        ++position;
        position %= capacity;
    }

    return position;
}

void FreeTable(hash_table_var *table)
{
    for(int i = 0; i < table->capacity; ++i)
    {
        if(table->data[i].key != NULL)
        {
            free(table->data[i].key);
        }
    }
    free(table->data);

    table->size = 0;
    table->capacity = 0;
}

void PrintError(char * string, int ExitCode)
{
	printf("\n[!] Error: %s.\n\n", string);
	fflush(stdin);
	exit(ExitCode);
}