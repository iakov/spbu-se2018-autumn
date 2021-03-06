#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "md5.h"

struct hashblock {
	char *key;
	int value;
	struct hashblock *next;
};

struct hashtable {
    int size;
	struct hashblock *block;
};

void createtable (struct hashtable *table, int size)
{
    table->size = size;
    table->block = (struct hashblock *) malloc (size*sizeof(struct hashblock));
    if (table->block == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(4);
    }
    for (int i=0; i<size; i++)
    {
        table->block[i].value=0;
        table->block[i].next=NULL;
    }



}

void add (struct hashtable *table, char *word, int val)
{
    uint8_t result[16];
    md5((uint8_t*)word, strlen(word), result);
    int block_index=0;
    for (int i=0; i<15; i++)
        block_index = ((block_index + result[i])*17)%(table->size);

    struct hashblock *tmpblock = &table->block[block_index];
    if (tmpblock->value==0)
    {
        tmpblock->key = word;
        tmpblock->value = val;
        return;
    }
    int true = 1;
    while (true == 1)
    {
        if (strcmp (word, tmpblock->key)==0)
        {
            free (word);
            tmpblock->value = tmpblock->value + val;
            return;
        }
        if (tmpblock->next==NULL) break;
        else tmpblock = tmpblock->next;
    }

    struct hashblock *newblock = (struct hashblock *) malloc (sizeof(struct hashblock));
    if (newblock == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(4);
    }
    newblock->key = word;
    newblock->value = val;
    newblock->next = NULL;
    tmpblock->next = newblock;

}

int getvalue (struct hashtable *table, char *word)
{
    uint8_t result[16];
    int i;
    md5((uint8_t*)word, strlen(word), result);
    int block_index=0;
    for (i=0; i<15; i++)
        block_index = ((block_index + result[i])*16)%(table->size);

    struct hashblock *tmpblock = &table->block[block_index];
    if (tmpblock->value==0)
    {
        return 0;
    }
    int true = 1;
    while (true == 1)
    {
        if (strcmp (word, tmpblock->key)==0)
        {
            return tmpblock->value;
        }
        if (tmpblock->next==NULL) break;
        else tmpblock = tmpblock->next;
    }
    return 0;


}

void printstatistic (struct hashtable *table)
{
    int often_word_value=0;
    struct hashblock *tmpblock;
    for (int i=0; i<table->size; i++)
    {
        tmpblock = &table->block[i];
        int true = 1;
        while (true == 1)
        {
            if (tmpblock->value == 0) break;
            printf ("%s %d\n", tmpblock->key, tmpblock->value);
            if (tmpblock->value > often_word_value)
            {
                often_word_value = tmpblock->value;
            }
            if (tmpblock->next == NULL) break;
            else tmpblock = tmpblock->next;
        }
    }
    for (int i=0; i<table->size; i++)
    {
        tmpblock = &table->block[i];
        int true = 1;
        while (true == 1)
        {
            if (tmpblock->value == 0) break;
            if (tmpblock->value == often_word_value)
            {
                fprintf(stderr, "%s %d\n", tmpblock->key, tmpblock->value);
            }
            if (tmpblock->next == NULL) break;
            else tmpblock = tmpblock->next;
        }
    }

}

void delete_table (struct hashtable *table)
{
    for (int i=0; i<table->size; i++)
    {
        int flag = 1;
        if (table->block[i].value == 0)
            flag = 0;

        struct hashblock *currentblock = &table->block[i];
        int len = 1;
        while (flag==1)
        {
            struct hashblock *tmpblock;
            tmpblock = currentblock;
            if (currentblock->next == NULL)
                flag = 0;
            else
                currentblock = currentblock->next;
            if (len>1)
            {
                free (tmpblock->key);
                free (tmpblock);
            }
            else
                free (tmpblock->key);

            len++;
        }
    }
    free (table->block);

}

int main ()
{
    int tablesize = 100000;
    struct hashtable table;
    createtable (&table, tablesize);

    char buffer[10000];
    char symbol;
    char *word;
    int len = 0;
    while ( (symbol = getchar()) != EOF)
    {
        if (( symbol >= 'a' && symbol <= 'z' ) || ( symbol >= 'A' && symbol <= 'Z' ))
        {
            buffer[len] = symbol;
            len++;
        }
        else if (len > 0)
        {
            buffer[len] = '\0';
            word = (char *) malloc((strlen(buffer)+1)*sizeof(char));
            if (word == NULL)
            {
                printf("Failed to allocate memory\n");
                exit(4);
            }
            strcpy(word, buffer);
            add (&table, word, 1);
            len = 0;
        }
    }

    printstatistic(&table);
    delete_table(&table);

    return 0;
}
