#pragma once

#include "utils.h"

typedef struct tagEntry Entry;
struct tagEntry
{
    Entry* next;
    char* key;
    uint64_t keySize;
    int value;
};

typedef struct tagTable
{
    Entry* allocated;
    Entry** lists;

    uint64_t count;
    uint64_t used;
} Table;

typedef void (*Iterator)( const char* key, int value, void* dataPointer );

extern Table* createTable( uint64_t count );

extern void resizeTable( Table* table, uint64_t count, Bool needCleansing );

extern void insertValue( Table* table, const char* key, uint64_t keySize, int value );

extern int getValue( Table* table, const char* key, uint64_t keySize );

extern int* getValuePointer( Table* table, const char* key, uint64_t keySize );

extern void iterateTable( Table* table, Iterator iterator, void* dataPointer );

extern void destroyTable( Table* table );
