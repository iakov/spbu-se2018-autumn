#ifndef FILESORT_ERRORS_H
#define FILESORT_ERRORS_H

#include <stdio.h>
#include <stdlib.h>

void ExitWithArgumentError(int argc)
{
    fprintf(stderr, "Invalid number of arguments! (%d) 4 expected\n", argc);
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
void ExitWithMemoryError()
{
    fprintf(stderr, "Unable to allocate enough memory!");
    exit(4);
}

#endif //FILESORT_ERRORS_H
