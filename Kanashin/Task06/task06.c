#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "md5.h"

#define MAX_SIZE_TABLE 5000
#define MAX_WORD_LENGTH 500

typedef struct HashList
{
    char* key;
    int numberReplies;
    struct HashList *ptrNext;
}List;

typedef struct
{
    List **lists;
    int *lenghtList;
    int sizeOfTable;

}HashTable;


HashTable newHashTable(int size)
{
    HashTable newTable;
    newTable.lists = (List **) calloc(size, sizeof(List*));
    if (newTable.lists == NULL)
    {
        fprintf(stderr, "Cannot allocate memory for creating hash table");
        exit(4);
    }
    newTable.sizeOfTable = size;
    newTable.lenghtList = (int *) calloc(size, sizeof(int));
    if (newTable.lenghtList == NULL)
    {
        fprintf(stderr, "Cannot allocate memory for counter of Length each of lists");
        exit(4);
    }
    return newTable;

}

uint32_t getHash(char *key)
{
    uint32_t hashRes = 0;
    uint32_t *res = (uint32_t *)calloc(4, sizeof(uint32_t));
    if (res == NULL)
    {
        fprintf(stderr, "Cannot allocate memory for buffer of Hash");
        exit(4);
    }
    md5((uint8_t *)key, strlen(key), (uint8_t *)res);
    hashRes = res[0];
    free(res);
    return hashRes;
}

List *findWord(HashTable *table, uint32_t index, char* word )
{
    List *currElemList;
    currElemList = table->lists[index];
    while (currElemList != NULL)
    {
        if (strcmp(currElemList->key , word) == 0)
        {
            return currElemList;
        }
        currElemList = currElemList->ptrNext;
    }
    return NULL;
}


void addWord(char *word, HashTable *table)
{
    uint32_t index = getHash(word) % table->sizeOfTable;

    List * newElemList = findWord(table, index, word);
    if (newElemList != NULL)
    {
        newElemList->numberReplies++;
        return;
    }

    if (table->lists[index] == NULL)
    {
        table->lists[index] = (List*)malloc(sizeof(List));
        if (table->lists[index] == NULL)
        {
            fprintf(stderr, "Cannot allocate memory for the head of lists");
            exit(4);
        }
        newElemList = table->lists[index];
    }
    else
    {
        List *prevElemList = table->lists[index];
        while (prevElemList->ptrNext != NULL)
        {
            prevElemList = prevElemList->ptrNext;
        }

        newElemList = (List*)malloc(sizeof(List));
        if (newElemList == NULL)
        {
            fprintf(stderr, "Cannot allocate memory for new element of list in the table");
            exit(4);
        }

        prevElemList->ptrNext = newElemList;
    }
    newElemList->key = (char *)malloc((strlen(word) + 1) * sizeof(char));
    if (newElemList->key == NULL)
    {
        fprintf(stderr, "Cannot allocate memory for word in the table");
        exit(4);
    }

    strcpy(newElemList->key, word);
    newElemList->ptrNext = NULL;
    newElemList->numberReplies = 1;
}

int getValueWord(HashTable *table, char* word)
{
    uint32_t index = getHash(word) % table->sizeOfTable;
    List *elemList;
    elemList = findWord(table, index, word);
    if (elemList == NULL)
    {
        printf("There is no here current word\n");
        return 0;
    }

    return elemList->numberReplies;

}
void getStat(HashTable *table)
{
    int maxNumberReplies = 0;
    /*int avgLengthList = 0;
    int amountLists = 0;
    int amountWords = 0;
    int maxList = 0;
    int totalWords = 0;*/
    for (int i = 0; i < table->sizeOfTable; i++)
    {
        /*int currLenghList = 0;
        if (table->lenghtList[i] != 0)
        {
            avgLengthList += table->lenghtList[i];
            amountLists++;
        }*/

        List *currElemList = table->lists[i];
        while (currElemList != NULL)
        {
            //currLenghList++;
            //int currNumberReplies = getValueWord(table, currElemList->key);
            //amountWords ++;
            //totalWords += currNumberReplies;
            if (currElemList->numberReplies > maxNumberReplies)
            {
                maxNumberReplies = currElemList->numberReplies;
            }
            fprintf(stdout, "%s %d\n", currElemList->key, currElemList->numberReplies);
            currElemList = currElemList->ptrNext;
        }
        /*if (currLenghList > maxList)
        {
            maxList = currLenghList;
        }*/
    }

    for (int i = 0; i < table->sizeOfTable; i++)
    {
        List *currElemList = table->lists[i];
        while (currElemList != NULL)
        {
            if (currElemList->numberReplies == maxNumberReplies)
            {
                fprintf(stderr, "%s %d\n", currElemList->key, currElemList->numberReplies);
            }
            currElemList = currElemList->ptrNext;
        }
    }
    /*printf("Total words are %d\n", totalWords);
    printf("Total words are %d\n", amountWords);
    printf("Average length of Lists is %d\n", avgLengthList/amountLists);
    printf("Max length of Lists is %d", maxList);
    */

}


void deleteTable(HashTable *table)
{
    for (int i = 0; i < table->sizeOfTable; i++)
    {
        List *currElemList = table->lists[i];
        while(currElemList != NULL)
        {
            List *buff = currElemList;
            currElemList = currElemList->ptrNext;
            free(buff->key);
            free(buff);
        }
    }
    free(table->lenghtList);
    free(table->lists);
}

int main(int argc, char *argv[])
{
    if (argc > 1 || argv[0] == NULL)
    {
       fprintf(stderr, "Incorrect parameters input");
       exit(1);
    }

    char buffer[MAX_WORD_LENGTH];
    HashTable table = newHashTable(MAX_SIZE_TABLE);
    char symb;
    char *word;
    int position = 0;

    while ( (symb = getchar()) != EOF)
    {
        if (( symb >= 'a' && symb <= 'z' ) ||
            ( symb >= 'A' && symb <= 'Z' ))
        {
            buffer[position++] = symb;
        }
        else if (position > 0)
        {
            buffer[position] = '\0';
            word = (char *)malloc((strlen(buffer)+1)*sizeof(char));
            if (word == NULL)
            {
                fprintf(stderr, "Cannot allocate memory for new word");
                exit(4);
            }

            strcpy(word, buffer);
            addWord(word, &table);
            free(word);
            position = 0;
        }


    }
    getStat(&table);
    deleteTable(&table);


    return 0;
}
