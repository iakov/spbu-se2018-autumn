#include <stdio.h>
#include <ctype.h>

#include "text.h"

#define MIN_BEGIN_SIZE (1 << 10)
#define MAX_BEGIN_SIZE (1 << 30)

static uint64_t readText( const char* text, uint64_t textSize, Table* table )
{
    uint64_t wordsCount = 0;
    uint64_t wordBegin = 0;

    for (uint64_t i = 0; i <= textSize; i++)
    {
        if (i == textSize || (!isalpha(text[i]) && !isdigit(text[i])))
        {
            if (i != wordBegin)
            {
                const char* word = text + wordBegin;
                uint64_t wordSize = i - wordBegin;

                int64_t* frequency = getValuePointer(table, word, wordSize);

                if (frequency == NULL)
                    insertValue(table, word, wordSize, 1);
                else
                    *frequency += 1;

                wordsCount++;
            }

            wordBegin = i + 1;
        }
    }

    return wordsCount;
}

void analizeText( const char* text, uint64_t textSize )
{
    Table* table = createTable(0);

    for (uint64_t i = MIN_BEGIN_SIZE; i <= MAX_BEGIN_SIZE; i += i >> 1)
    {
        resizeTable(table, i, TRUE);

        uint64_t wordsCount = readText(text, textSize, table);

        Statistics statistics;
        getStatistics(table, &statistics);

        if (i == MIN_BEGIN_SIZE)
        {
            printf("Total count of words: %lu\n", wordsCount);
            printf("Count of different words: %lu\n", table->used);
            printf("Most frequent word: \"%s\" (%ld times)\n",
                   statistics.maximumEntry->key, statistics.maximumEntry->value);
        }
        printf("\nBegin table size: %lu\n", i);
        printf("Final table size: %lu\n", table->count);
        printf("Count of chains: %lu\n", statistics.chainsCount);
        printf("Maximum chain length: %lu\n", statistics.maximumChainLength);

        if (statistics.maximumChainLength <= 2)
            break;
    }

    destroyTable(table);
}
