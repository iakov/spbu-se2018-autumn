#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "md5_new.h"

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
    /*
    MD5_CTX hashGenerator;
    char *md5 = calloc(MD5_SIZE, sizeof(char));

    md5_init(&hashGenerator);
    md5_update(&hashGenerator, input, (size_t) strlen(input));
    md5_final(&hashGenerator, md5);

    int hash = 0;
    for (int i = 0; i < (int) strlen(md5); ++i)
        hash = ( ( hash * 16 + (int) md5[i] ) % size + size) % size;
    free(md5);
    */
    int *md5_hash = calloc(4, sizeof(int));

    if (md5_hash == NULL)
    {
        printf("Memory allocation error\n");
        exit(4);
    }

    md5((uint8_t *) input, strlen(input), (uint8_t *) md5_hash);
    uint32_t hash = md5_hash[0];
    free(md5_hash);

    return hash % size;
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
        while (map->table[i] != NULL)
        {
            ListItem *temp = map->table[i];
            map->table[i] = map->table[i]->nextPtr;
            free(temp->key);
            free(temp);
        }
    }
    free(map->table);
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
        free(key);
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

    if (map->table[hashOfString] == NULL)
    {
        newItem->nextPtr = NULL;
        map->table[hashOfString] = newItem;
    }
    else
    {
        newItem->nextPtr = map->table[hashOfString]->nextPtr;
        map->table[hashOfString]->nextPtr = newItem;
    }

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
    int maxFreqValue = 0;

    for (int i = 0; i < map->size; ++i)
    {
        ListItem *current = map->table[i];
        while (current != NULL)
        {
            if (current->value > maxFreqValue)
            {
                maxFreqValue = current->value;
            }
            current = current->nextPtr;
        }
    }

    for (int i = 0; i < map->size; ++i)
    {
        ListItem *current = map->table[i];
        while (current != NULL)
        {
            if (current->value == maxFreqValue)
            {
                fprintf(stderr, "%s %d\n", current->key, current->value);
            }
            current = current->nextPtr;
        }
    }
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


int main()
{
    int size = 1000;
    init(&map, size);
    int wordLength = 500;
    char word[wordLength];
    char *buffer;
    for ( ; scanf("%s", word) != EOF; )
    {
        if (strcmp(word, "!!!") == 0) break;
        if (strlen(word) != 0)
        {
            int i = 0;
            for ( ; i < (int) strlen(word); i++)
            {
                buffer = malloc(wordLength * sizeof(char));
                if (buffer == NULL)
                {
                    fprintf(stderr, "Memory allocation error");
                    exit(4);
                }
                int bufLen = 0;
                while (isLetter(word[i]) && i < (int) strlen(word))
                {
                    buffer[bufLen++] = word[i];
                    i++;
                }


                if (bufLen > 0)
                {
                    buffer[bufLen] = '\0';
                    add(&map, buffer, 1);
                }
                else
                {
                    free(buffer);
                }
            }

        }
    }
    filter(&map, print);
    getStat(&map);
    clear(&map);
    return 0;
}

