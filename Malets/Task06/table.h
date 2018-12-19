#pragma once

#include "utils.h"

typedef struct tagEntry Entry;
struct tagEntry
{
    Entry* next;
    char* key;
    uint64_t keySize;
    int64_t value;
};

typedef struct tagTable
{
    Entry* allocated;
    Entry** lists;

    uint64_t count;
    uint64_t used;
} Table;

typedef struct tagStatistics
{
    Entry* maximumEntry;
    uint64_t maximumChainLength;
    uint64_t chainsCount;
} Statistics;

typedef void (*Iterator)( Entry* entry, void* dataPointer );

Table* createTable( uint64_t count );

void resizeTable( Table* table, uint64_t count, Bool needCleansing );

void insertValue( Table* table, const char* key, uint64_t keySize, int64_t value );

int64_t getValue( Table* table, const char* key, uint64_t keySize );

int64_t* getValuePointer( Table* table, const char* key, uint64_t keySize );

void getStatistics( Table* table, Statistics* statistics );

void iterateTable( Table* table, Iterator iterator, void* dataPointer );

void destroyTable( Table* table );
