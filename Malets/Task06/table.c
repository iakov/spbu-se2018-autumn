#include <stdlib.h>
#include <string.h>

#include "table.h"

typedef union tagHash
{
    uint32_t int32[4];
    uint64_t int64[2];
} Hash;

typedef union
{
    uint8_t bytes[64];
    uint32_t words[16];
} Block;

#define rotate( x, n ) (x << n | x >> (32 - n))

#define FunctionF( x, y, z ) (((x) & (y)) | (~(x) ^ (z)))
#define FunctionG( x, y, z ) (((x) & (z)) | (~(z) ^ (y)))
#define FunctionH( x, y, z ) ((x) ^ (y) ^ (z))
#define FunctionI( x, y, z ) ((y) ^ (~(z) | (x)))

#define Stage( a, b, c, d, x, t, s, function ) \
{                                              \
    a += function(b, c, d) + (x) + (t);        \
    a = rotate(a, s);                          \
    a += (b);                                  \
}

#define Stage1( a, b, c, d, x, t, s ) Stage(a, b, c, d, x, t, s, FunctionF)
#define Stage2( a, b, c, d, x, t, s ) Stage(a, b, c, d, x, t, s, FunctionG)
#define Stage3( a, b, c, d, x, t, s ) Stage(a, b, c, d, x, t, s, FunctionH)
#define Stage4( a, b, c, d, x, t, s ) Stage(a, b, c, d, x, t, s, FunctionI)

static void processBlock( Hash* hash, Block* block )
{
    uint32_t a = hash->int32[0];
    uint32_t b = hash->int32[1];
    uint32_t c = hash->int32[2];
    uint32_t d = hash->int32[3];

    Stage1(a, b, c, d, block->words[0x0], 0XD76AA478, 0x07);
    Stage1(d, a, b, c, block->words[0x1], 0XE8C7B756, 0x0C);
    Stage1(c, d, a, b, block->words[0x2], 0X242070DB, 0x11);
    Stage1(b, c, d, a, block->words[0x3], 0XC1BDCEEE, 0x16);
    Stage1(a, b, c, d, block->words[0x4], 0XF57C0FAF, 0x07);
    Stage1(d, a, b, c, block->words[0x5], 0X4787C62A, 0x0C);
    Stage1(c, d, a, b, block->words[0x6], 0XA8304613, 0x11);
    Stage1(b, c, d, a, block->words[0x7], 0XFD469501, 0x16);
    Stage1(a, b, c, d, block->words[0x8], 0X698098D8, 0x07);
    Stage1(d, a, b, c, block->words[0x9], 0X8B44F7AF, 0x0C);
    Stage1(c, d, a, b, block->words[0xA], 0XFFFF5BB1, 0x11);
    Stage1(b, c, d, a, block->words[0xB], 0X895CD7BE, 0x16);
    Stage1(a, b, c, d, block->words[0xC], 0X6B901122, 0x07);
    Stage1(d, a, b, c, block->words[0xD], 0XFD987193, 0x0C);
    Stage1(c, d, a, b, block->words[0xE], 0XA679438E, 0x11);
    Stage1(b, c, d, a, block->words[0xF], 0X49B40821, 0x16);
    Stage2(a, b, c, d, block->words[0x1], 0XF61E2562, 0x05);
    Stage2(d, a, b, c, block->words[0x6], 0XC040B340, 0x09);
    Stage2(c, d, a, b, block->words[0xB], 0X265E5A51, 0x0E);
    Stage2(b, c, d, a, block->words[0x0], 0XE9B6C7AA, 0x14);
    Stage2(a, b, c, d, block->words[0x5], 0XD62F105D, 0x05);
    Stage2(d, a, b, c, block->words[0xA], 0X02441453, 0x09);
    Stage2(c, d, a, b, block->words[0xF], 0XD8A1E681, 0x0E);
    Stage2(b, c, d, a, block->words[0x4], 0XE7D3FBC8, 0x14);
    Stage2(a, b, c, d, block->words[0x9], 0X21E1CDE6, 0x05);
    Stage2(d, a, b, c, block->words[0xE], 0XC33707D6, 0x09);
    Stage2(c, d, a, b, block->words[0x3], 0XF4D50D87, 0x0E);
    Stage2(b, c, d, a, block->words[0x8], 0X455A14ED, 0x14);
    Stage2(a, b, c, d, block->words[0xD], 0XA9E3E905, 0x05);
    Stage2(d, a, b, c, block->words[0x2], 0XFCEFA3F8, 0x09);
    Stage2(c, d, a, b, block->words[0x7], 0X676F02D9, 0x0E);
    Stage2(b, c, d, a, block->words[0xC], 0X8D2A4C8A, 0x14);
    Stage3(a, b, c, d, block->words[0x5], 0XFFFA3942, 0x04);
    Stage3(d, a, b, c, block->words[0x8], 0X8771F681, 0x0B);
    Stage3(c, d, a, b, block->words[0xB], 0X6D9D6122, 0x10);
    Stage3(b, c, d, a, block->words[0xE], 0XFDE5380C, 0x17);
    Stage3(a, b, c, d, block->words[0x1], 0XA4BEEA44, 0x04);
    Stage3(d, a, b, c, block->words[0x4], 0X4BDECFA9, 0x0B);
    Stage3(c, d, a, b, block->words[0x7], 0XF6BB4B60, 0x10);
    Stage3(b, c, d, a, block->words[0xA], 0XBEBFBC70, 0x17);
    Stage3(a, b, c, d, block->words[0xD], 0X289B7EC6, 0x04);
    Stage3(d, a, b, c, block->words[0x0], 0XEAA127FA, 0x0B);
    Stage3(c, d, a, b, block->words[0x3], 0XD4EF3085, 0x10);
    Stage3(b, c, d, a, block->words[0x6], 0X04881D05, 0x17);
    Stage3(a, b, c, d, block->words[0x9], 0XD9D4D039, 0x04);
    Stage3(d, a, b, c, block->words[0xC], 0XE6DB99E5, 0x0B);
    Stage3(c, d, a, b, block->words[0xF], 0X1FA27CF8, 0x10);
    Stage3(b, c, d, a, block->words[0x2], 0XC4AC5665, 0x17);
    Stage4(a, b, c, d, block->words[0x0], 0XF4292244, 0x06);
    Stage4(d, a, b, c, block->words[0x7], 0X432AFF97, 0x0A);
    Stage4(c, d, a, b, block->words[0xE], 0XAB9423A7, 0x0F);
    Stage4(b, c, d, a, block->words[0x5], 0XFC93A039, 0x15);
    Stage4(a, b, c, d, block->words[0xC], 0X655B59C3, 0x06);
    Stage4(d, a, b, c, block->words[0x3], 0X8F0CCC92, 0x0A);
    Stage4(c, d, a, b, block->words[0xA], 0XFFEFF47D, 0x0F);
    Stage4(b, c, d, a, block->words[0x1], 0X85845DD1, 0x15);
    Stage4(a, b, c, d, block->words[0x8], 0X6FA87E4F, 0x06);
    Stage4(d, a, b, c, block->words[0xF], 0XFE2CE6E0, 0x0A);
    Stage4(c, d, a, b, block->words[0x6], 0XA3014314, 0x0F);
    Stage4(b, c, d, a, block->words[0xD], 0X4E0811A1, 0x15);
    Stage4(a, b, c, d, block->words[0x4], 0XF7537E82, 0x06);
    Stage4(d, a, b, c, block->words[0xB], 0XBD3AF235, 0x0A);
    Stage4(c, d, a, b, block->words[0x2], 0X2AD7D2BB, 0x0F);
    Stage4(b, c, d, a, block->words[0x9], 0XEB86D391, 0x15);

    hash->int32[0] += a;
    hash->int32[1] += b;
    hash->int32[2] += c;
    hash->int32[3] += d;
}

Hash computeMD5Hash( const char* string, uint64_t size )
{
    uint64_t remain = size & 0x3F;
    uint64_t normalBlocksCount = size >> 6;
    uint64_t specialBlocksCount = 1 + remain / 56;

    Hash hash = {
        {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476}
    };

    Block block;

    int8_t* charPointer = (int8_t*) string;

    for (uint64_t i = 0; i < normalBlocksCount; i++)
    {
        memcpy(block.bytes, charPointer, 64);
        charPointer += 64;

        processBlock(&hash, &block);
    }

    memcpy(block.bytes, charPointer, remain);
    block.bytes[remain] = 0x80;
    memset(block.bytes + remain + 1, 0, 63 - remain);

    if (specialBlocksCount == 2)
    {
        processBlock(&hash, &block);
        memset(block.bytes, 0, sizeof(block.bytes));
    }

    block.words[14] = (uint32_t) (size << 3);
    block.words[15] = (uint32_t) (size >> 29);

    processBlock(&hash, &block);

    return hash;
}

static Entry* findPreviousEntry( Table* table, const char* key, uint64_t keySize )
{
    Hash hash = computeMD5Hash(key, keySize);

    Entry* entry = (Entry*)(table->lists + hash.int64[0] % table->count);

    while (entry->next != NULL)
    {
        if (keySize == entry->next->keySize && memcmp(key, entry->next->key, keySize) == 0)
            break;

        entry = entry->next;
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
            free(table->allocated[--table->used].key);
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

void insertValue( Table* table, const char* key, uint64_t keySize, int64_t value )
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

int64_t getValue( Table* table, const char* key, uint64_t keySize )
{
    Entry* entry = findPreviousEntry(table, key, keySize);

    if (entry->next == NULL)
        return 0;

    return entry->next->value;
}

int64_t* getValuePointer( Table* table, const char* key, uint64_t keySize )
{
    Entry* entry = findPreviousEntry(table, key, keySize);

    if (entry->next == NULL)
        return NULL;

    return &entry->next->value;
}

void getStatistics( Table* table, Statistics* statistics )
{
    statistics->chainsCount = 0;
    statistics->maximumChainLength = 0;
    statistics->maximumEntry = NULL;

    for (uint64_t i = 0; i < table->count; i++)
    {
        Entry* entry = table->lists[i];
        uint64_t chainLength = 0;

        while (entry != NULL)
        {
            if (statistics->maximumEntry == NULL || entry->value > statistics->maximumEntry->value)
                statistics->maximumEntry = entry;


            entry = entry->next;
            chainLength++;
        }

        if (chainLength > 0)
        {
            statistics->chainsCount++;

            if (chainLength > statistics->maximumChainLength)
                statistics->maximumChainLength = chainLength;
        }
    }
}

void iterateTable( Table* table, Iterator iterator, void* pointer )
{
    for (uint64_t i = 0; i < table->used; i++)
        iterator(table->allocated + i, pointer);
}

void destroyTable( Table* table )
{
    resizeTable(table, 0, TRUE);
    free(table);
}
