#pragma once

#include <stdint.h>

#define TRUE  1
#define FALSE 0

typedef void (* SortingMethod)();

typedef struct
{
    uint8_t* begin;
    uint64_t size;
} Line;

extern Line* g_lines;
extern int64_t g_linesCount;

extern SortingMethod sort;

extern int64_t initialize( int argumentsCount, char** arguments );

extern void print();

extern void releaseResources();

extern SortingMethod getSortingMethod( uint64_t id );
