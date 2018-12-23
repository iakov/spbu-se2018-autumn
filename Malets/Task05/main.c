#include <stdio.h>
#include <stdlib.h>

#include "sort.h"

int main( int argc, char** argv )
{
    atexit(releaseResources);

    fprintf(stderr, "initialization...\n");
    initialize(argc, argv);
    
    fprintf(stderr, "sorting...\n");
    sort();

    fprintf(stderr, "printing...\n");
    print();

    forceExit("Success", REASON_NONE);
}
