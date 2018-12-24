#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "MD5.h"
#include "main.h"

int main(int arg_counter, char * arguments[])
{
    if(arg_counter > 1 || arguments[0] == NULL)
    {        
        PrintError("Invalid arguments.", 1);
    }

    struct HashTable hashTable = CreateHashTable(256);
    char word[10000];
    char *buffer;
    char inputSymbol;
    int word_length = 0;

    while ((inputSymbol = getchar()) != EOF)
    {
        if(((inputSymbol >= 'A') && (inputSymbol <= 'Z')) || ((inputSymbol >= 'a') && (inputSymbol <= 'z')))
        {
            word[word_length++] = inputSymbol;
        }
        else if((word_length > 0) && (inputSymbol == '-' || inputSymbol == '\''))
        {
            word[word_length++] = inputSymbol;
        }
        else if(word_length)
        {
            while((word[word_length - 1] == '\'') || (word[word_length - 1] == '-'))
            {
                word[word_length--] = '\0';
            }
            word[word_length] = '\0';
            buffer = (char *)calloc(strlen(word) + 1, sizeof(char));
            if(buffer == NULL)
            {
                PrintError("I can not allocate memory in Main for \"buffer\"", 4);
            }

            strcpy(buffer, word);
            Add(&hashTable, buffer, Get(&hashTable, buffer) + 1);
            word_length = 0;
        }
    }

    uint32_t Maximum_Word_Counter = 0;

    for(uint32_t i = 0; i < hashTable.size; i++)
    {
        if(hashTable.data[i].key != NULL)
        {
            printf("%s %d\n", hashTable.data[i].key, hashTable.data[i].value);
            if(hashTable.data[i].value > Maximum_Word_Counter)
            {
                Maximum_Word_Counter = hashTable.data[i].value;
            }
        }
    }

    for(uint32_t i = 0; i < hashTable.size; i++)
    {
        if((hashTable.data[i].key != NULL) && (hashTable.data[i].value == Maximum_Word_Counter))
        {
            fprintf(stderr, "%s %d\n", hashTable.data[i].key, hashTable.data[i].value);
        }
    }

    Clear(&hashTable);
    return 0;
}

void Add(struct HashTable *hashTable, char *key, uint32_t value)
{
    uint32_t index = GetIndex(hashTable, key);

    if(index < hashTable->size)
    {
         hashTable->data[index].value = value;
         free(hashTable->data[index].key);
         hashTable->data[index].key = key;
         return;
    }

    hashTable->numberOfElements++;

    if(hashTable->numberOfElements > hashTable->size / 2)
    {
        Resize(hashTable, hashTable->size * 2);
    }

    uint32_t *hash = (uint32_t *)calloc(4, sizeof(uint32_t));
    if(hash == NULL)
    {
        PrintError("I can not allocate memory in Add for \"*hash\"", 4);
    }

    md5((uint8_t *)key, strlen(key), (uint8_t *)hash);
    uint32_t pos = hash[0] % hashTable->size;

    while(hashTable->data[pos].key != NULL)
    {
        pos++;
        if (pos >= hashTable->size)
        {
            pos = 0;
        }
    }

    hashTable->data[pos].hash = hash;
    hashTable->data[pos].key = key;
    hashTable->data[pos].value = value;
}

void Resize(struct HashTable *hashTable, uint32_t size)
{
    struct HashTableSlot *newData = (struct HashTableSlot *)calloc(size, sizeof(struct HashTableSlot));
    if(newData == NULL)
    {
        PrintError("I can not allocate memory in Resize for \"*newData\"", 4);
    }

    for(uint32_t i = 0; i < hashTable->size; i++)
    {
        if(hashTable->data[i].key != NULL)
        {
            uint32_t pos = hashTable->data[i].hash[0] % size;
            while(newData[pos].key != NULL)
            {
                pos++;
                if(pos >= size)
                {
                    pos = 0;
                }
            }
            newData[pos] = hashTable->data[i];
        }
    }

    free(hashTable->data);

    hashTable->data = newData;
    hashTable->size = size;
}

uint32_t Get(struct HashTable *hashTable, char *key)
{
    uint32_t pos = GetIndex(hashTable, key);

    if(pos == hashTable->size)
    {
        return 0;
    }

    return hashTable->data[pos].value;
}

uint32_t GetIndex(struct HashTable *hashTable, char *key)
{
    uint32_t *hash = (uint32_t *)calloc(4, sizeof(uint32_t));
    if(hash == NULL)
    {
        PrintError("I can not allocate memory in GetIndex for \"*hash\"", 4);
    }

    md5((uint8_t *)key, strlen(key), (uint8_t *)hash);
    uint32_t pos = hash[0] % hashTable->size;

    while(hashTable->data[pos].key != NULL && strcmp(key, hashTable->data[pos].key) != 0)
    {
        pos++;
        if(pos == hashTable->size)
        {
            pos = 0;
        }
    }

    free(hash);

    if(hashTable->data[pos].key == NULL)
    {
        return hashTable->size;
    }

    return pos;
}

void Clear(struct HashTable *hashTable)
{
    for(uint32_t i = 0; i < hashTable->size; i++)
    {
        if(hashTable->data[i].key != NULL)
        {
            free(hashTable->data[i].key);
            free(hashTable->data[i].hash);
        }
    }

    free(hashTable->data);
    hashTable->size = 0;
    hashTable->numberOfElements = 0;
}

void PrintError(char * string, int ExitCode)
{
    printf("\n[!] Error: %s.\n\n", string);
    fflush(stdin);
    exit(ExitCode);
}
