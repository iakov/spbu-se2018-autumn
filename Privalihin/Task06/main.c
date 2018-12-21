#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "MD5.h"

#define memoryErrorMessage "Insufficient memory!\n"


struct HashTableSlot
{
    char *key;
    uint32_t *hash;
    uint32_t value;
};

struct HashTable
{
    struct HashTableSlot *data;
    uint32_t size;
    uint32_t numberOfElements;
};

struct HashTable newHashTable(uint32_t size)
{
    struct HashTable hashTable;
    hashTable.data = (struct HashTableSlot *)calloc(size, sizeof(struct HashTableSlot));

    if (hashTable.data == NULL)
    {
        printf(memoryErrorMessage);
        exit(4);
    }

    hashTable.size = size;
    hashTable.numberOfElements = 0;
    return hashTable;
}

void clear(struct HashTable *hashTable)
{
    for (uint32_t i = 0; i < hashTable->size; i++)
    {
        if (hashTable->data[i].key != NULL)
        {
            free(hashTable->data[i].key);
            free(hashTable->data[i].hash);
        }
    }

    free(hashTable->data);
    hashTable->size = 0;
    hashTable->numberOfElements = 0;
}

void resize(struct HashTable *hashTable, uint32_t size)
{
    struct HashTableSlot *newData = (struct HashTableSlot *)calloc(size, sizeof(struct HashTableSlot));

    if (newData == NULL)
    {
        printf(memoryErrorMessage);
        exit(4);
    }

    for (uint32_t i = 0; i < hashTable->size; i++)
    {
        if (hashTable->data[i].key != NULL)
        {
            uint32_t pos = hashTable->data[i].hash[0] % size;

            while (newData[pos].key != NULL)
            {
                pos++;
                if (pos >= size)
                    pos = 0;
            }

            newData[pos] = hashTable->data[i];
        }
    }

    free(hashTable->data);
    hashTable->data = newData;
    hashTable->size = size;
}

uint32_t getIndex(struct HashTable *hashTable, char *key)
{
    uint32_t *hash = (uint32_t *)calloc(4, sizeof(uint32_t));

    if (hash == NULL)
    {
        printf(memoryErrorMessage);
        exit(4);
    }

    md5((uint8_t *)key, strlen(key), (uint8_t *)hash);
    uint32_t pos = hash[0] % hashTable->size;

    while (hashTable->data[pos].key != NULL && strcmp(key, hashTable->data[pos].key) != 0)
    {
        pos++;
        if (pos == hashTable->size)
            pos = 0;
    }

    free(hash);

    if (hashTable->data[pos].key == NULL)
    {
        return hashTable->size;
    }

    return pos;
}

uint32_t get(struct HashTable *hashTable, char *key)
{
    uint32_t pos = getIndex(hashTable, key);

    if (pos == hashTable->size)
    {
        return 0;
    }

    return hashTable->data[pos].value;
}

void add(struct HashTable *hashTable, char *key, uint32_t value)
{
    uint32_t index = getIndex(hashTable, key);

    if (index < hashTable->size)
    {
         hashTable->data[index].value = value;
         free(hashTable->data[index].key);
         hashTable->data[index].key = key;
         return;
    }

    hashTable->numberOfElements++;

    if (hashTable->numberOfElements > hashTable->size / 2)
    {
        resize(hashTable, hashTable->size * 2);
    }

    uint32_t *hash = (uint32_t *)calloc(4, sizeof(uint32_t));

    if (hash == NULL)
    {
        printf(memoryErrorMessage);
        exit(4);
    }

    md5((uint8_t *)key, strlen(key), (uint8_t *)hash);
    uint32_t pos = hash[0] % hashTable->size;

    while (hashTable->data[pos].key != NULL)
    {
        pos++;
        if (pos >= hashTable->size)
            pos = 0;
    }

    hashTable->data[pos].hash = hash;
    hashTable->data[pos].key = key;
    hashTable->data[pos].value = value;
}

int main(int argc, char *argv[])
{
    if (argc > 1 || argv[0] == NULL)
    {
        exit(1);
    }

    struct HashTable hashTable = newHashTable(256);
    char word[10000];
    char *buffer;
    char inputSymbol;
    int wordLen = 0;

    while ((inputSymbol = getchar()) != EOF)
    {
        if ((inputSymbol <= 'Z' && inputSymbol >= 'A'))
        {
            word[wordLen++] = inputSymbol;// - 'A' + 'a';
        }
        else if (inputSymbol <= 'z' && inputSymbol >= 'a')
        {
            word[wordLen++] = inputSymbol;
        }
        else if (wordLen > 0 && (inputSymbol == '-' || inputSymbol == '\'')) //for words like ill-spoken, well-known, it's etc.
        {
            word[wordLen++] = inputSymbol;
        }
        else if (wordLen)
        {
            while (word[wordLen - 1] == '\'' || word[wordLen - 1] == '-')
            {
                word[wordLen--] = '\0';
            }
            word[wordLen] = '\0';
            buffer = (char *)calloc(strlen(word) + 1, sizeof(char));
            if (buffer == NULL)
            {
                printf(memoryErrorMessage);
                return 1;
            }

            strcpy(buffer, word);
            add(&hashTable, buffer, get(&hashTable, buffer) + 1);
            //the buffer pointer is not lost, it's still accessible via hashTable.data[???].key
            wordLen = 0;
        }
    }

    uint32_t maxWordCount = 0;

    for (uint32_t i = 0; i < hashTable.size; i++)
    {
        if (hashTable.data[i].key != NULL)
        {
            printf("%s %d\n", hashTable.data[i].key, hashTable.data[i].value);
            if (hashTable.data[i].value > maxWordCount)
            {
                maxWordCount = hashTable.data[i].value;
            }
        }
    }

    for (uint32_t i = 0; i < hashTable.size; i++)
    {
        if (hashTable.data[i].key != NULL && hashTable.data[i].value == maxWordCount)
        {
            fprintf(stderr, "%s %d\n", hashTable.data[i].key, hashTable.data[i].value);
        }
    }

    clear(&hashTable);
    return 0;
}
