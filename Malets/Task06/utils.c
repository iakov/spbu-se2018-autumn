#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void* reallocateMemory( void* memory, uint64_t size )
{
    void* pointer = realloc(memory, size);

    if (pointer == NULL && size != 0)
        suicide("Can not allocate memory", REASON_SYSTEM_ERROR);

    return pointer;
}

extern void suicide( const char* suicideNote, Reason suicideReason )
{
    fprintf(stderr, "%s\n", suicideNote);
    exit(suicideReason);
}
