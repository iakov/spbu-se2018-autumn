#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "text.h"

static int g_fileDescriptor = -1;
static uint64_t g_fileSize = 0;
static char* g_chars = MAP_FAILED;

static void releaseResources( void )
{
    if (g_chars != MAP_FAILED)
        munmap(g_chars, g_fileSize);

    if (g_fileDescriptor != -1)
        close(g_fileDescriptor);
}

int main( int argc, char** argv )
{
    atexit(releaseResources);

    if (argc != 2)
        suicide("Too few arguments", REASON_INVALID_ARGUMENTS);

    g_fileDescriptor = open(argv[1], O_RDONLY);

    if (g_fileDescriptor == -1)
        suicide("Cannot open file", REASON_NONEXISTENT_FILES);

    g_fileSize = (uint64_t) lseek(g_fileDescriptor, 0, SEEK_END);
    if (g_fileSize == (uint64_t)-1)
        suicide("Can not ind out file size", REASON_SYSTEM_ERROR);

    g_chars = mmap(NULL, g_fileSize, PROT_READ, MAP_SHARED, g_fileDescriptor, 0);
    if (g_chars == MAP_FAILED)
        suicide("Cannot map file", REASON_SYSTEM_ERROR);

    analizeText(g_chars, g_fileSize);

    suicide("Success", REASON_DESIRE_TO_DIE);
}
