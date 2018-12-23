#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils.h"

void* allocateMemory( uint64_t size )
{
    void* pointer = calloc(1, size);

    if (pointer == NULL && size != 0)
        forceExit("Can not allocate memory", REASON_SYSTEM_ERROR);

    return pointer;
}

void freeMemory( void* pointer )
{
    if (pointer != NULL)
        free(pointer);
}

void forceExit( const char* suicideNote, Reason suicideReason )
{
    fprintf(stderr, "%s\n", suicideNote);
    exit(suicideReason);
}

const char* skipWhiteSpaces( const char* string )
{
    while (isblank(*string))
        string++;

    return string;
}
