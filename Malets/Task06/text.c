#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "text.h"

#define TEXT_SIZE 1024
#define BEGIN_SIZE 1024

static void processText( const char* text, Table* table )
{
    uint64_t textSize = strlen(text);

    char word[textSize];
    uint64_t wordSize = 0;

    for (uint64_t i = 0; i <= textSize; i++)
    {
        if (!isalpha(text[i]))
        {
            if (wordSize != 0)
            {
                int* frequency = getValuePointer(table, word, wordSize);

                if (frequency == NULL)
                    insertValue(table, word, wordSize, 1);
                else
                    *frequency += 1;

                wordSize = 0;
            }
        }
        else
        {
            word[wordSize] = text[i];
            wordSize++;
        }
    }
}

static void readText( Table* table )
{
    char text[TEXT_SIZE];

    while (scanf("%s", text) == 1)
    {
        processText(text, table);
    }
}

static void printAll( const char* key, int value, int* maximum )
{
    if (value > *maximum)
        *maximum = value;

    printf("%s %d\n", key, value);
}

static void printMostFrequent( const char* key, int value, int* maximum )
{
    if (value == *maximum)
        fprintf(stderr, "%s %d\n", key, value);
}

void analizeText()
{
    Table* table = createTable(BEGIN_SIZE);

    readText(table);

    int maximum = 0;

    iterateTable(table, (Iterator) printAll, &maximum);
    iterateTable(table, (Iterator) printMostFrequent, &maximum);

    destroyTable(table);
}
