#include <stdio.h>
#include <stdlib.h>

const int Lim = 100;    //limit of array

extern void quickSort(int* s_arr, int first, int last);

int StrToInt(char *str, int symb)   //interpretaion of "atoi" function
{
    int num = 0; int sign = 1;
    if (str[symb] == '-')
    {
        sign = - 1;
        ++symb;
    }
    while(str[symb] != '\0')
    {
        num *= 10;
        num += str[symb] - '0';
        symb++;
    }
    return num*sign;
}

int Parametrs_Scan(char * argv[], int i, int k)
{
    if ((argv[i][k] <= '9' && argv[i][k] >='0') || argv[i][k] == '-')
                    return StrToInt(argv[i], k);
                else
                    if ((argv[i+1][0] <= '9' && argv[i+1][0] >='0') || argv[i+1][0] == '-')
                        return StrToInt(argv[i+1], 0);
                    else
                        if ((argv[i+1][1] <= '9' && argv[i+1][1] >='0') || argv[i+1][1] == '-')
                            return StrToInt(argv[i+1], 1);
                        else return StrToInt(argv[i+2], 0);
}

int main(int argc, char * argv[])
{
    int from = -2147483647; int to = 2147483647;  //parametrs values
    int unsorted[Lim], sorted[Lim];
    int count = 0; //un-/sorted array's index
    int changes = 0;   //amount of changed numbers after sort
    int i, var;
    char symb = ' ';

for (int i = 1; i < argc; i++)  // Reading parametrs
    {
            if (argv[i][2] == 't')
                to = Parametrs_Scan(argv, i, 5);
            if (argv[i][2] == 'f')
                from = Parametrs_Scan(argv, i, 7);
    }

    while (symb != '\n' && symb != '\0')               /* Reading number and next symbol,
                                                                            until meet end of range (\n).
                                                                            Placing numbers either in array or in stderr/out*/
        {
          scanf("%d%c", &var, &symb);
            if (var > from && var < to)
            {
                unsorted[count] = var;
                count++;
            }
            else if (var <= from)
                fprintf(stdout, "%d ", var);
            if (var >= to)
                fprintf(stderr, "%d ", var);
        }

    for (int i = 0; i <count; i++)
        sorted[i] = unsorted[i];

    quickSort(sorted, 0, count - 1);

    for (int i = 0; i < count; i++)  //Counting of changed positions
        if (unsorted[i] != sorted[i])
            changes++;

    return changes;
}
