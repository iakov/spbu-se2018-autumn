#include <stdio.h>

#include "sort.h"

int main( int argc, char** argv )
{
    fprintf(stderr, "initialization...\n");
    if (initialize(argc, argv))
    {
        fprintf(stderr, "sorting...\n");
        sort();

        fprintf(stderr, "printing...\n");
        print();
    }
    else
        fprintf(stderr, "failed\n");

    releaseResources();

    return 0;
}
