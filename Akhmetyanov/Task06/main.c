#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

#define BLOCK_MD5 16
#define WORD_MAX 1000

void *callocCheck(size_t items, size_t size)
{
    void *memPtr = calloc(items, size);
    if (memPtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory!\n");
        exit(4);
    }
    return memPtr;
}

void *reallocCheck(void *memPtr, size_t size)
{
    memPtr = realloc(memPtr, size);
    if (memPtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory!\n");
        exit(4);
    }
    return memPtr;
}

struct tableItem
{
    char *key;
    uint32_t value;
};

struct chain
{
    struct tableItem *items;
    size_t used;
    size_t size;
};

void initChain(struct chain *keyChain, size_t initSize)
{
    keyChain->items = (struct tableItem *)callocCheck(initSize, sizeof(struct tableItem));
    keyChain->used = 0;
    keyChain->size = initSize;
}

void insertInChain(struct chain *keyChain, char *key, uint32_t value)
{
    if (keyChain->used == keyChain->size)
    {
        keyChain->size *= 2;
        keyChain->items = (struct tableItem *)reallocCheck(keyChain->items, keyChain->size * sizeof(struct tableItem));
    }
    uint32_t wordMaxLen = WORD_MAX;
    keyChain->items[keyChain->used].key = (char *)callocCheck(wordMaxLen, sizeof(char));
    strcpy(keyChain->items[keyChain->used].key, key);
    keyChain->items[keyChain->used++].value = value;

}

struct hashTable
{
    struct chain *keyChains;
    uint32_t chainsCount;
    uint32_t size;
};

struct hashTable new(uint32_t chainsCount)
{
    struct hashTable table;
    table.keyChains = (struct chain *)callocCheck(chainsCount, sizeof(struct chain));
    uint32_t initSize = 5;
    for (uint32_t i = 0; i < chainsCount; i++)
    {
        initChain(&table.keyChains[i], initSize);
    }
    table.chainsCount = chainsCount;
    return table;
}

void clear(struct hashTable *table)
{
     for (uint32_t i = 0; i < table->chainsCount; i++)
    {
        for (uint32_t j = 0; j < table->keyChains[i].used; j++)
        {
            free(table->keyChains[i].items[j].key);
        }
        free(table->keyChains[i].items);
    }
    free(table->keyChains);

}

uint32_t getIndex(struct hashTable *table, char *key, int *indexInChain)
{
    uint8_t *hash = (uint8_t *)callocCheck(BLOCK_MD5, sizeof(uint8_t));
    md5((uint8_t *) key, strlen(key), hash);
    uint32_t pos = 0;
    for (int i = 0; i < BLOCK_MD5; i++)
    {
        pos  = pos * BLOCK_MD5 + (uint32_t)hash[i];
        pos %= table->chainsCount;
    }
    //indexInChain is -1 if none is found
    *indexInChain = -1;
    char *keyCurr;
    for (uint32_t i = 0; i < table->keyChains[pos].used; i++)
    {
        if (table->keyChains[pos].items[i].key != NULL)
        {
            keyCurr = table->keyChains[pos].items[i].key;
            if (strcmp(keyCurr, key) == 0)
            {
                *indexInChain = i;
                break;
            }
        }
    }
    free(hash);
    return pos;
}

void add(struct hashTable *table, char* key, uint32_t value)
{
    int indexInChain;
    uint32_t pos = getIndex(table, key, &indexInChain);
    //only if there is no such key in chain
    if (indexInChain == -1)
    {
        insertInChain(&table->keyChains[pos], key, value);
    }
    else
    {
        table->keyChains[pos].items[indexInChain].value += value;
    }
}

uint32_t get(struct hashTable *table, char *key)
{
    int indexInChain;
    uint32_t pos = getIndex(table, key, &indexInChain);
    return table->keyChains[pos].items[indexInChain].value;
}

int main()
{
    uint32_t tableSize = 1000;
    struct hashTable table = new(tableSize);
    //reading stdin
    char inputChar;
    uint32_t wordMaxLen = WORD_MAX;
    char *word = (char *)callocCheck(wordMaxLen, sizeof(char));
    int index = 0;
    while ((inputChar = (char)fgetc(stdin)) != EOF)
    {
        index = 0;
        while ( !((inputChar >= 'A' && inputChar <= 'Z') ||
                (inputChar >= 'a' && inputChar <= 'z')) &&
                inputChar != EOF)
        {
            inputChar = (char)fgetc(stdin);
        }
        while ( (inputChar >= 'A' && inputChar <= 'Z') ||
                (inputChar >= 'a' && inputChar <= 'z') ||
                (inputChar == '-') || (inputChar == '\''))
        {
            word[index] = inputChar;
            index++;
            inputChar = (char)fgetc(stdin);
        }
        word[index] = '\0';
        if (index != 0)
        {
            add(&table, word, 1);

        }
    }
    free(word);

    uint32_t countMax = 0;
    char *keyCurr;
    uint32_t valCurr;
    for (uint32_t i = 0; i < table.chainsCount; i++)
    {
        for (uint32_t j = 0; j < table.keyChains[i].used; j++)
        {
            if (table.keyChains[i].items[j].key != NULL)
            {
                keyCurr = table.keyChains[i].items[j].key;
                valCurr = table.keyChains[i].items[j].value;
                fprintf(stdout, "%s %d\n", keyCurr, valCurr);
            }

            if (table.keyChains[i].items[j].key != NULL &&
                table.keyChains[i].items[j].value > countMax)
            {
                countMax = table.keyChains[i].items[j].value;
            }
        }
    }

    for (uint32_t i = 0; i < tableSize; i++)
    {
        for (uint32_t j = 0; j < table.keyChains[i].used; j++)
        {
            if (table.keyChains[i].items[j].key != NULL &&
                table.keyChains[i].items[j].value == countMax)
            {
                keyCurr = table.keyChains[i].items[j].key;
                valCurr = table.keyChains[i].items[j].value;
                fprintf(stderr, "%s %d\n", keyCurr, valCurr);
            }
        }
    }
    clear(&table);
}
