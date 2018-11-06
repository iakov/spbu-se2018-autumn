#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <getopt.h>

extern void sort(int *arr, int length);

int main( int argc, char *argv[] ) 
{
    int from = INT_MIN;
    int to = INT_MAX;

    //getting "from", "to" values using getopt
    int opt;
    
    while (true)
    {
        static struct option long_options[] = 
        {
            {"from", required_argument, 0, 'f'},
            {"to", required_argument, 0, 't'},
            {0, 0, 0, 0}
        };
        int index = 0;
        opt = getopt_long(argc, argv, "f:t:", long_options, &index);

        if (opt == -1) break;

        switch (opt)
        {
            case 'f':
                from = atoi(optarg);
                break;
            case 't':
                to = atoi(optarg);
                break;
            default:
                break;
        }
    }
    
    int array[100] = {0};
    int count = 0;
    int number = 0;
    char nextSymbol = ' ';

    while (nextSymbol != '\n')
    {
        scanf("%d%c", &number, &nextSymbol);
        if (number > from && number < to)
        {
            array[count] = number;
            count++;
        }
        else if (number <= from) fprintf(stdout, "%d ", number);
        else if (number >= to) fprintf(stderr, "%d ", number);       
    }

    int sortArray[100];
    memcpy(sortArray, array, 100);
    sort(sortArray, count);
    
    int changedPos = 0;
    //elements which changed positions after sorting
    for (int i = 0; i < count; i++)
    {
        if (sortArray[i] != array[i]) changedPos++;
    }
    
    return changedPos;
}
