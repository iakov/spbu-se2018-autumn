#include <stdio.h>
#include <stdlib.h>

const int Lim = 100;

extern quicksort(int *s_arr, int first, int last);

int strToInt(char *str, int symb)
{
    int num = 0, sign = 1;
    if (str[symb] == '-')
    {
        sign = -1;
        symb++;
    }
    while (str[symb] != '\0')
    {
        num = num * 10 + sign * (str[symb] - '0');
        symb++;
    }
    return num;
}

int getFromOrToValue(char * argv[], int index, int pos)
{
    if ((argv[index][pos] == '-') || ((argv[index][pos] >= '0') && (argv[index][pos] <= '9')))
        return strToInt(argv[index], pos);
    else if ((argv[index + 1][0] == '-') || ((argv[index + 1][0] >= '0') && (argv[index + 1][0] <= '9')))
        return strToInt(argv[index + 1], 0);
    else if ((argv[index + 1][0] == '=') && (argv[index + 1][1] != '\0'))
        return strToInt(argv[index + 1], 1);
    else
        return strToInt(argv[index + 2], 0);
}

int main(int argc, char * argv[])
{
    int from, to, flagfrom = 0, flagto = 0;
    int unsorted[Lim], sorted[Lim];
    int numcount = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][2] == 'f')
        {
            flagfrom = 1;
            from = getFromOrToValue(argv, i, 7);
        }
        if (argv[i][2] == 't')
        {
            flagto = 1;
            to = getFromOrToValue(argv, i, 5);
        }
    }

    char space = ' ';
    int num;

    while (space != '\n')
    {
        scanf("%d%c", &num, &space);
        if (flagfrom && (num <= from))
            fprintf(stdout, "%d ", num);
        else if (flagto && (num >= to))
            fprintf(stderr, "%d ", num);
        else
        {
            unsorted[numcount] = num;
            numcount++;
        }
    }

    for (int i = 0; i < numcount; i++)
        sorted[i] = unsorted[i];

    quicksort(sorted, 0, numcount - 1);

    int diff = 0;

    for (int i = 0; i < numcount; i++)
        if (unsorted[i] != sorted[i])
            diff++;

    return diff;
}
