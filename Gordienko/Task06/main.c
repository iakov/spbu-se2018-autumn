#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MD5.h"

#define MAX_WORD_LENGTH 100
#define MAX_ARRAY_SIZE 10000

typedef struct el
{
    char *key;
    int value;
    struct el *next;
} node;

typedef struct
{
    node **listArr;
    int size, wordsCount;
    int *listLength;
} hashTable;

hashTable newHashTable(int size)
{
    hashTable newTable;
    newTable.listArr = (node**) calloc(size, sizeof(node*));
    if (newTable.listArr == NULL)
    {
        printf("Cannot allocate memory for list array.\n");
        exit(4);
    }
    newTable.size = size;
    newTable.listLength = (int*) calloc(size, sizeof(int));
    if (newTable.listLength == NULL)
    {
        printf("Cannot allocate memory for list length\n");
        exit(4);
    }
    newTable.wordsCount = 0;
    return newTable;
}

uint32_t getHash(char *key)
{
    uint32_t *res = (uint32_t *)calloc(4, sizeof(uint32_t));
    if (res == NULL)
    {
        printf("Cannot allocate memory for hash result\n");
        exit(4);
    }
    md5((uint8_t *)key, strlen(key), (uint8_t *)res);
    uint32_t hash = res[0];
    free(res);
    return hash;
}

void clear(hashTable table)
{
    for (int i = 0; i < table.size; i++)
    {
        while (table.listArr[i] != NULL)
        {
            node *currNode = table.listArr[i];
            table.listArr[i] = table.listArr[i]->next;
            free(currNode->key);
            free(currNode);
        }
    }
    free(table.listArr);
    free(table.listLength);
}

void add(hashTable *table, char *key)
{
    uint32_t hash = getHash(key) % table->size;

    node *currNode = table->listArr[hash];
    node *prevNode = NULL;
    while (currNode != NULL)
    {
        if (strcmp(currNode->key, key) == 0)
            break;
        prevNode = currNode;
        currNode = currNode->next;
    }

    if (currNode == NULL)
    {
        if (prevNode == NULL)
        {
            table->listArr[hash] = (node*)malloc(sizeof(node));
            currNode = table->listArr[hash];
        }
        else
        {
            prevNode->next = (node*)malloc(sizeof(node));
            currNode = prevNode->next;
        }

        if (currNode == NULL)
        {
            printf("Cannot allocate memory for node\n");
            exit(4);
        }

        currNode->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
        if (currNode->key == NULL)
        {
            printf("Cannot allocate memory for node key\n");
            free(currNode);
            exit(4);
        }

        strcpy(currNode->key, key);
        currNode->value = 1;
        currNode->next = NULL;

        table->listLength[hash]++;
        table->wordsCount ++;
    }
    else
        currNode->value++;
}

int getValue(hashTable table, char *key)
{
    uint32_t hash = getHash(key) % table.size;
    node *currNode = table.listArr[hash];
    while (currNode != NULL)
    {
        if (strcmp(currNode->key, key) == 0)
            return currNode->value;
        currNode = currNode->next;
    }
    return 0;
}

void printStat(hashTable table)
{
    int maxValue = 0;
    for (int i = 0; i < table.size; i++)
    {
        node *currNode = table.listArr[i];
        while (currNode != NULL)
        {
            if (currNode->value > maxValue)
                maxValue = currNode->value;
            fprintf(stdout, "%s %d\n", currNode->key, currNode->value);
            currNode = currNode->next;
        }
    }
    for (int i = 0; i < table.size; i++)
    {
        node *currNode = table.listArr[i];
        while (currNode != NULL)
        {
            if (currNode->value == maxValue)
                fprintf(stderr, "%s %d\n", currNode->key, currNode->value);
            currNode = currNode->next;
        }
    }
}

void printStatAdvanced(hashTable table)
{
    int maxValue = 0;
    int maxListLength = 0;
    int totalWordsValue = 0;
    node *maxNode = NULL;
    for (int i = 0; i < table.size; i++)
    {
        node *currNode = table.listArr[i];
        while (currNode != NULL)
        {
            if (currNode->value > maxValue)
            {
                maxValue = currNode->value;
                maxNode = currNode;
            }
            totalWordsValue += currNode->value;
            currNode = currNode->next;
        }
        if (table.listLength[i] > maxListLength)
        {
            maxListLength = table.listLength[i];
        }
    }

    printf("Total amount of words: %d\n", totalWordsValue);
    printf("Max word frequency: %d for word %s\n", maxValue, maxNode->key);
    printf("Avg word frequency: %f\n", (double)totalWordsValue / table.wordsCount);
    printf("Max list length: %d for table size of %d\n", maxListLength, table.size);
}

int main(int argc, char *argv[])
{
    if (argc > 1 || argv[0] == NULL)
    {
        fprintf(stderr, "Wrong arguments");
        exit(1);
    }

    int size = MAX_ARRAY_SIZE;
    hashTable table = newHashTable(size);
    char word[MAX_WORD_LENGTH];
    char input;
    char *buffer;
    int count = 0;

    while ((input = getchar()) != EOF)
    {
        if ((input <= 'Z' && input >= 'A') || (input <= 'z' && input >= 'a') || (input == '-' || input == '\''))
        {
            word[count++] = input;
        }
        else if (count != 0)
        {
            while (word[count - 1] == '-' || word[count - 1] == '\'' )
                word[count--] = '\0';
            word[count] = '\0';

            buffer = (char *)calloc(strlen(word) + 1, sizeof(char));
            if (buffer == NULL)
            {
                printf("Cannot allocate memory for buffer\n");
                exit(4);
            }

            strcpy(buffer, word);
            add(&table, buffer);
            count = 0;
            free(buffer);
        }
    }

    printStat(table);
    clear(table);
    return 0;
}
