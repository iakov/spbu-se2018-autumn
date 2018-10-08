#include <stdio.h>
#include <stdlib.h>

const int Lim = 100;

extern quicksort(int *s_arr, int first, int last);

int strtoint(char *str, int symb)
{
    int num = 0;
    while (str[symb] != '\0')
    {
        num *= 10;
        num += str[symb] - '0';
        symb++;
    }
    return num;
}

int main(int argc, char * argv[])
{
    int from, to;
    int flagto = 0, flagfrom = 0;
    int errors[Lim], unsorted[Lim], sorted[Lim];
    int ierr = 0, iuns = 0;
    int diff = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            int num = strtoint(argv[i], 0);
            if ((flagto && flagfrom && (num > from) && (num < to)) ||
                (flagto && !flagfrom && (num < to)) ||
                (!flagto && flagfrom && (num > from)) ||
                (!flagto && !flagfrom))
            {
                unsorted[iuns] = num;
                iuns++;
            }
            else
            {
                errors[ierr] = num;
                ierr++;
            }
        }
        else
        {
            if (argv[i][2] == 't')
            {
                flagto = 1;
                to = strtoint(argv[i], 5);
            }
            if (argv[i][2] == 'f')
            {
                flagfrom = 1;
                from = strtoint(argv[i], 7);
            }
        }
    }

    for (int i = 0; i < iuns; i++)
        sorted[i] = unsorted[i];

    quicksort(sorted, 0, iuns - 1);

    for (int i = 0; i < iuns; i++)
        printf("%d ", sorted[i]);

    for (int i = 0; i < ierr; i++)
    {
        if (flagfrom && (errors[i] <= from))
            fprintf(stdout, "%d ", errors[i]);
        if (flagto && (errors[i] >= to))
            fprintf(stderr, "%d ", errors[i]);
    }

    for (int i = 0; i < iuns; i++)
        if (unsorted[i] != sorted[i])
            diff++;

    return diff;
}
