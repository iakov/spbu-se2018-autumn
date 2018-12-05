#pragma once

#include <stdint.h>

#define TRUE  1
#define FALSE 0

typedef struct
{
    uint8_t* begin;
    uint64_t size;
} Line;

extern Line* g_lines;
extern int64_t g_count;

extern int64_t initialize( int argumentsCount, char** arguments );

extern void (* sort)();

extern void print();

extern void releaseResources();

extern void sortBubble();

extern void sortInsertion();

extern void sortQuick();

extern void sortMerge();

extern void sortHeap();
