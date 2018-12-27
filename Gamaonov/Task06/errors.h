#ifndef HASH_ERRORS_H
#define HASH_ERRORS_H

#include <stdio.h>
#include <stdlib.h>

void ExitWithArgumentError(int argc)
{
    fprintf(stderr, "Invalid number of arguments! (%d)", argc);
    exit(1);
}
void ExitWithFileError(char *path)
{
    fprintf(stderr, "Invalid path to file! (%s)\n", path);
    exit(2);
}
void ExitWithInputDataError(char *filename)
{
    fprintf(stderr, "Wrong input data! (%s)\n", filename);
    exit(3);
}
void ExitWithMemoryError(size_t size)
{
    fprintf(stderr, "Unable to allocate enough memory! (%d bytes)", (int)size);
    exit(4);
}

#endif //HASH_ERRORS_H
