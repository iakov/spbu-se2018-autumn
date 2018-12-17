#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "md5.h"



const int MD5_SIZE = 64;

typedef struct item
{
    char *key;
    int value;

    struct item *nextPtr;

} ListItem;


typedef struct
{
    ListItem **table;
    int *length;
    int size;

} HashMap;

HashMap map;


int getHash(char input[], int size)
{
    MD5_CTX hashGenerator;
    char *md5 = calloc(MD5_SIZE, sizeof(char));

    md5_init(&hashGenerator);
    md5_update(&hashGenerator, input, (size_t) strlen(input));
    md5_final(&hashGenerator, md5);

    int hash = 0;
    for (int i = 0; i < (int) strlen(md5); ++i)
        hash = ( ( hash * 16 + (int) md5[i] ) % size + size) % size;
    free(md5);

    return hash;
}



void init(HashMap *map, int size)
{
    map->table = calloc(size, sizeof(ListItem*));
    map->size = size;
    map->length = calloc(size, sizeof(int));

    if (map->table == NULL || map->length == NULL)
    {
        fprintf(stderr, "Memory allocation error");
        exit(4);
    }
}



ListItem *nextItem(HashMap *map, ListItem *current)
{
    if (current == NULL)
    {
        int position = 0;
        while (position < map->size && map->table[position] == NULL)
        {
            position++;
        }
        if (position >= map->size)
        {
            return NULL;
        }
        return map->table[position];
    }

    if (current->nextPtr == NULL)
    {
        int position = getHash(current->key, map->size) + 1;
        while (position < map->size && map->table[position] == NULL)
        {
            position++;
        }

        if (position >= map->size)
        {
            return NULL;
        }
        return map->table[position];
    }
    else
    {
        return current->nextPtr;
    }
}



void filter(HashMap *map, int (*function) (char*, int) )
{
    ListItem *current = nextItem(map, NULL);
    while (current != NULL)
    {
        current->value = function(current->key, current->value);
        current = nextItem(map, current);
    }
}



void clear(HashMap *map)
{
    for (int i = 0; i < map->size; ++i)
    {
        if (map->table[i] == NULL)
        {
            continue;
        }
        ListItem *current = map->table[i]->nextPtr;
        while (current != NULL)
        {
            map->table[i]->nextPtr = current->nextPtr;
            free(current);
            current = map->table[i]->nextPtr;
        }
        free(map->table[i]);

        map->table[i] = NULL;
        map->length[i] = 0;
    }
}



ListItem *find(HashMap *map, int hash, char *key)
{
    ListItem *current = map->table[hash];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current;
        }
        current = current->nextPtr;
    }
    return NULL;
}



void add(HashMap *map, char *key, int value)
{
    int hashOfString = getHash(key, map->size);
    ListItem *target = find(map, hashOfString, key);

    if (target != NULL)
    {
        target->value += value;
        return;
    }

    ListItem *newItem = malloc(sizeof(ListItem));

    if (newItem == NULL)
    {
        fprintf(stderr, "Memory allocation error");
        exit(4);
    }

    newItem->key = key;
    newItem->value = value;
    newItem->nextPtr = map->table[hashOfString];

    map->table[hashOfString] = newItem;
    map->length[hashOfString]++;
}



int get(HashMap *map, char *key)
{
    int hashOfString = getHash(key, map->size);
    ListItem *target = find(map, hashOfString, key);

    if (target != NULL)
    {
        return target->value;
    }

    return 0;
}



void getStat(HashMap *map)
{
    int chainAmount = 0;
    float avgChainLen = 0;
    int maxChainLen = 0;
    int differentKeyAmount = 0;
    char *mostFreqKey;
    int maxFreqValue = 0;
    int total = 0;

    for (int i = 0; i < map->size; ++i)
    {
        differentKeyAmount += map->length[i];
        if (map->length[i] != 0)
        {
            chainAmount++;
        }
        if (maxChainLen < map->length[i])
        {
            maxChainLen = map->length[i];
        }


        ListItem *current = map->table[i];
        while (current != NULL)
        {
            total += current->value;
            if (current->value > maxFreqValue)
            {
                maxFreqValue = current->value;
                mostFreqKey = current->key;
            }
            current = current->nextPtr;
        }
    }
    avgChainLen = (float) (differentKeyAmount) / chainAmount;
    printf("Statistics of hash-table:\n");
    printf("   Table size: %d\n", map->size);
    printf("   Chains amount: %d\n", chainAmount);
    printf("   Average value of chains' length: %f\n", avgChainLen);
    printf("   Total keys amount: %d\n", total);
    printf("   Different keys amount: %d\n", differentKeyAmount);
    printf("   The most frequently used key: '%s' - %d times\n", mostFreqKey, maxFreqValue);
}



_Bool isLetter(char symbol)
{
    if ('a' <= symbol && symbol <= 'z')
        return 1;
    if ('A' <= symbol && symbol <= 'Z')
        return 1;
    return 0;
}



int print(char *key, int value)       // example function for filter()
{
    printf("%s %d\n", key, value);
    return value;
}

char *word;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Invalid number of arguments");
        exit(1);
    }

    int size = atoi(argv[1]);
    FILE *file = fopen(argv[2], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Can not open file");
        exit(2);
    }
    //clock_t timeStart = clock();
    init(&map, size);
    for (;;)
    {
        word = malloc(100);
        if (word == NULL)
        {
            fprintf(stderr, "Memory allocation error");
            exit(4);
        }
        char input;
        int len = 0;
        while ( isLetter(input = (char) fgetc(file)) )
        {
            input = (char) tolower(input);
            len++;
            word[len - 1] = input;
        }
        word[len] = '\0';

        if (input == EOF)
        {
            break;
        }
        if (len != 0)
        {
            add(&map, word, 1);
        }
    }
    //clock_t timeEnd = clock();

    getStat(&map);
    //printf("   Time: %f", (float) (timeEnd - timeStart) / CLOCKS_PER_SEC);
    //filter(&map, print);
    clear(&map);
    free(word);

    return 0;
}