#pragma once

#include <stdint.h>

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef enum
{
    REASON_DESIRE_TO_DIE = 0,
    REASON_INVALID_ARGUMENTS = 1,
    REASON_NONEXISTENT_FILES = 2,
    REASON_INVALID_DATA = 3,
    REASON_SYSTEM_ERROR = 4,
} Reason;

extern void suicide( const char* suicideNote, Reason suicideReason );

extern void* reallocateMemory( void* memory, uint64_t size );

#define allocateMemory(size) reallocateMemory(NULL, size)

#define freeMemory(memory) reallocateMemory(memory, 0)
