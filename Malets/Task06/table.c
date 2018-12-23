#include <string.h>

#include "table.h"
#include "hash.h"

static Entry* findPreviousEntry( Table* table, const char* key, uint64_t keySize )
{
    Hash hash = computeHash(key, keySize);

    uint64_t index = hash.int64[0] % table->count;
    
    Entry* entry = (Entry*)(table->lists + index);

    for (Entry* next = entry->next; next != NULL; entry = next, next = entry->next)
    {
        if (keySize == next->keySize && memcmp(key, next->key, keySize) == 0)
            break;
    }

    return entry;
}

Table* createTable( uint64_t size )
{
    Table* table = allocateMemory(sizeof(Table));

    table->used = 0;
    table->allocated = NULL;
    resizeTable(table, size, TRUE);

    return table;
}

void resizeTable( Table* table, uint64_t count, Bool needCleansing )
{
    needCleansing |= table->used > count;

    if (needCleansing)
    {
        while (table->used > 0)
        {
            table->used--;
            freeMemory(table->allocated[table->used].key);
        }
    }

    uint64_t memorySize = sizeof(Entry) * count + sizeof(Entry*) * count;
    table->allocated = reallocateMemory(table->allocated, memorySize);
    table->lists = (Entry**) (table->allocated + count);
    table->count = count;

    if (memorySize != 0)
        memset(table->allocated + table->used, 0, memorySize - sizeof(Entry) * table->used);

    if (!needCleansing)
    {
        for (uint64_t i = 0; i < table->used; i++)
        {
            Entry* entry = table->allocated + i;
            entry->next = NULL;

            findPreviousEntry(table, entry->key, entry->keySize)->next = entry;
        }
    }
}

void insertValue( Table* table, const char* key, uint64_t keySize, int value )
{
    if (table->used >= table->count)
        resizeTable(table, 1 + table->used + (table->used >> 1), FALSE);

    Entry* entry = findPreviousEntry(table, key, keySize);

    if (entry->next == NULL)
    {
        entry->next = table->allocated + table->used++;
        entry->next->key = allocateMemory(keySize + 1);

        memcpy(entry->next->key, key, keySize);
        entry->next->key[keySize] = '\0';
        entry->next->keySize = keySize;
    }

    entry->next->value = value;
}

int getValue( Table* table, const char* key, uint64_t keySize )
{
    Entry* entry = findPreviousEntry(table, key, keySize)->next;

    if (entry == NULL)
        return 0;

    return entry->value;
}

int* getValuePointer( Table* table, const char* key, uint64_t keySize )
{
    Entry* entry = findPreviousEntry(table, key, keySize)->next;

    if (entry == NULL)
        return NULL;

    return &entry->value;
}

void iterateTable( Table* table, Iterator iterator, void* pointer )
{
    for (uint64_t i = 0; i < table->used; i++)
    {
        Entry* entry = table->allocated + i;
        iterator(entry->key, entry->value, pointer);
    }
}

void destroyTable( Table* table )
{
    resizeTable(table, 0, TRUE);
    freeMemory(table);
}
