#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "sort.h"

Line* g_lines = NULL;
int64_t g_linesCount = 0;

SortingMethod sort = NULL;

static uint8_t* g_chars = MAP_FAILED;
static int g_fileDescriptor = -1;
static uint64_t g_fileSize = 0;

void print()
{
    for (int64_t i = 0; i < g_linesCount; i++)
    {
        fwrite(g_lines[i].begin, g_lines[i].size, 1, stdout);
        printf("\n");
    }
}

void releaseResources()
{
    freeMemory(g_lines);

    if (g_chars != MAP_FAILED)
        munmap(g_chars, g_fileSize);

    if (g_fileDescriptor != -1)
        close(g_fileDescriptor);
}

static void validateLinesCount( const char* argument )
{
    Bool isChanged = FALSE;

    argument = skipWhiteSpaces(argument);

    for (int64_t i = 0, symbol; (symbol = argument[i]) != '\0'; i++)
    {
        if (symbol < '0' || symbol > '9')
        {
            if (isChanged && isWhiteString(argument))
                return;
            
            suicide("Invalid count of lines", REASON_INVALID_ARGUMENTS);
        }

        isChanged = TRUE;

        g_linesCount *= 10;
        g_linesCount += symbol - '0';
    }
}

static void validateFile( const char* argument )
{
    g_fileDescriptor = open(argument, O_RDONLY);

    if (g_fileDescriptor == -1)
        suicide("Can not open file", REASON_NONEXISTENT_FILES);

    g_fileSize = (uint64_t) lseek(g_fileDescriptor, 0, SEEK_END);
    
    if (g_fileSize == (uint64_t) -1)
        suicide("Can not find out file size", REASON_SYSTEM_ERROR);

    if (g_fileSize != 0)
    {
        g_chars = mmap(NULL, g_fileSize, PROT_READ, MAP_SHARED, g_fileDescriptor, 0);

        if (g_chars == MAP_FAILED)
            suicide("Can not map file", REASON_SYSTEM_ERROR);
    }
}

static void validateMethod( const char* argument )
{
    uint64_t id = 0;

    for (int64_t i = 0, symbol; (symbol = argument[i]) != '\0'; i++)
    {
        if (symbol < 'a' || symbol > 'z' || i == 9)
            suicide("Invalid method name", REASON_INVALID_ARGUMENTS);

        id <<= 7;
        id += symbol;
    }

    sort = getSortingMethod(id);

    if (sort == NULL)
        suicide("Invalid method name", REASON_INVALID_ARGUMENTS);
}

void initialize( int argumentsCount, char** arguments )
{
    if (argumentsCount != 4)
        suicide("Invalid count of arguments", REASON_INVALID_ARGUMENTS);

    validateLinesCount(arguments[1]);
    validateMethod(arguments[3]);
    validateFile(arguments[2]);

    g_lines = allocateMemory(g_linesCount * sizeof(Line));

    int64_t allocatedCount = g_linesCount;
    g_linesCount = 0;

    uint8_t* begin = g_chars;
    uint8_t* end = g_chars + g_fileSize - 1;

    for (uint8_t* i = g_chars; i <= end; i++)
    {
        if (*i == '\n')
        {
            if (g_linesCount == allocatedCount)
                return;

            g_lines[g_linesCount].begin = begin;
            g_lines[g_linesCount].size = i - begin;
            g_linesCount++;

            begin = i + 1;
        }
    }

    if (g_linesCount < allocatedCount && begin <= end)
    {
        g_lines[g_linesCount].begin = begin;
        g_lines[g_linesCount].size = end - begin + 1;
        g_linesCount++;
    }
}
