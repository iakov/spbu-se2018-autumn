#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum limits_of_strings {ALPHABET = 256, MAX_STR_LENGTH = 10000};
long number_of_strings = 0;
FILE *InputFile;

#define NULL_CHECK( x )\
{\
 if( NULL == ( x ) )\
  {\
    printf("Can`t allocate memory.\n");\
    exit(4);\
  }\
}


#include "sort.h"
/*

    int bubble(char **);
    int insertion(char **);
    int merge(char **, long, long);
    int quick(char **, long, long);
    int radix(char **);

*/


#include "helper.h"
/*

    char input(char **);
    int read_file(FILE *, char **);
    int choise_sort(char, char **);
    int print_sorted(char **);
    int memory_flush(char **);

*/
