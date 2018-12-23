#pragma once

#include <stdint.h>

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef enum
{
    REASON_NONE = 0,
    REASON_INVALID_ARGUMENTS = 1,
    REASON_NONEXISTENT_FILES = 2,
    REASON_INVALID_DATA = 3,
    REASON_SYSTEM_ERROR = 4,
} Reason;

extern void forceExit( const char* suicideNote, Reason suicideReason );

extern void* allocateMemory( uint64_t size );

extern void freeMemory( void* pointer );

extern const char* skipWhiteSpaces( const char* string );

#define isWhiteString(string) (*skipWhiteSpaces(string) == '\0')
