#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "sort.h"

#define BUFFER_SIZE (1 << 20)

Line* g_lines = NULL;
int64_t g_linesCount = 0;

SortingMethod sort = NULL;

static uint8_t* g_chars = NULL;
static int64_t g_isMapped = FALSE;

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
    if (g_lines != NULL)
        free(g_lines);

    if (g_isMapped)
    {
        munmap(g_chars, g_fileSize);
    }
    else if (g_chars != NULL && g_chars != MAP_FAILED)
    {
        free(g_chars);
    }

    if (g_fileDescriptor != -1)
        close(g_fileDescriptor);
}

static int64_t validateLinesCount( const char* argument )
{
    int64_t count = 0;
    
    for (int64_t i = 0, symbol; (symbol = argument[i]) != '\0'; i++)
    {
        if (symbol < '0' || symbol > '9')
            return FALSE;

        count *= 10;
        count += symbol - '0';
    }

    g_lines = malloc(count * sizeof(Line));

    if (g_lines == NULL)
        return FALSE;

    g_linesCount = count;

    return TRUE;
}

static int64_t validateFile( const char* argument )
{
    g_fileDescriptor = open(argument, O_RDONLY);

    if (g_fileDescriptor == -1)
        return FALSE;

    g_fileSize = (uint64_t) lseek(g_fileDescriptor, 0, SEEK_END);

    if (g_fileSize == 0 || g_fileSize == (uint64_t) -1)
        return FALSE;

    return TRUE;
}

static int64_t validateMethod( const char* argument )
{
    uint64_t id = 0;

    for (int64_t i = 0, symbol; (symbol = argument[i]) != '\0'; i++)
    {
        if (symbol < 'a' || symbol > 'z' || i == 9)
            return FALSE;

        id <<= 7;
        id += symbol;
    }

    sort = getSortingMethod(id);

    if (sort == NULL)
        return FALSE;

    return TRUE;
}

static int64_t mapFile()
{
    g_chars = mmap(NULL, g_fileSize, PROT_READ, MAP_SHARED, g_fileDescriptor, 0);

    if (g_chars == MAP_FAILED)
        return FALSE;

    g_isMapped = TRUE;

    return TRUE;
}

static int64_t loadFile()
{
    g_chars = malloc(g_fileSize);

    if (g_chars == NULL)
        return FALSE;

    lseek(g_fileDescriptor, 0, SEEK_SET);

    uint64_t bufferSize = BUFFER_SIZE;
    uint64_t offset = 0;

    while (offset < g_fileSize)
    {
        if (bufferSize + offset > g_fileSize)
            bufferSize = g_fileSize - offset;

        if (read(g_fileDescriptor, g_chars + offset, bufferSize) != (int64_t) bufferSize)
            return FALSE;

        offset += bufferSize;
    }

    return TRUE;
}

int64_t initialize( int argumentsCount, char** arguments )
{
    if (argumentsCount < 4 || argumentsCount > 5)
    {
        fprintf(stderr, "Invalid count of arguments: '%d'\n", argumentsCount);
        return FALSE;
    }

    if (!validateMethod(arguments[3]))
    {
        fprintf(stderr, "Invalid method name: '%s'\n", arguments[3]);
        return FALSE;
    }

    if (!validateLinesCount(arguments[1]))
    {
        fprintf(stderr, "Invalid count of lines: '%s'\n", arguments[1]);
        return FALSE;
    }

    if (!validateFile(arguments[2]))
    {
        fprintf(stderr, "Can not open file: '%s'\n", arguments[2]);
        return FALSE;
    }

    if (argumentsCount == 5)
    {
        if (!mapFile())
        {
            fprintf(stderr, "Can not map file.\n");
            return FALSE;
        }
    }
    else if (!loadFile())
    {
        fprintf(stderr, "Can not load file. Try using mmap.\n");
        return FALSE;
    }

    int64_t allocatedCount = g_linesCount;
    g_linesCount = 0;

    g_lines[0].begin = g_chars;

    uint8_t* end = g_chars + g_fileSize - 1;

    for (uint8_t* i = g_chars; i < end; i++)
    {
        if (*i == '\n')
        {
            g_lines[g_linesCount].size = i - g_lines[g_linesCount].begin;

            g_linesCount++;

            if (g_linesCount >= allocatedCount)
                break;

            g_lines[g_linesCount].begin = i + 1;
        }
    }

    if (g_linesCount < allocatedCount)
    {
        g_lines[g_linesCount].size = end - g_lines[g_linesCount].begin;
        g_linesCount++;
    }

    return TRUE;
}
