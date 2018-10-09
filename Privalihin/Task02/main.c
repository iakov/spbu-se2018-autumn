#include<stdio.h>

extern void sort(int *begin, int len);

int main(int argc, char **argv)
{
    int hasLowerBound = 0;
    int hasUpperBound = 0;
    int lowerBound, upperBound;
    int i;
    for (i = 1; i < argc; i++)
    {
        int pos = 0;
        int number = 0;
        for (; (argv[i][pos] > '9') || (argv[i][pos] < '0'); pos++);
        while ((argv[i][pos] >= '0') && (argv[i][pos] <= '9'))
        {
            number = number * 10 + (int)(argv[i][pos++] - '0');
        }
        if (argv[i][2] == 'f')
        {
            hasLowerBound = 1;
            lowerBound = number;
        }
        else if (argv[i][2] == 't')
        {
            hasUpperBound = 1;
            upperBound = number;
        }
    }

    int numbers[100], backupNumbers[100];
    int len = 0;
    for (i = 0; i < 100; i++)
        numbers[i] = 0;
    int notEmpty = 0;
    int currentNumber = 0;
    char c;
    while ((c = getchar()) != EOF)
    {
        if ((c >= '0') && (c <= '9'))
        {

            notEmpty = 1;
            currentNumber = currentNumber * 10 + (int)(c - '0');
        }
        else if (notEmpty)
        {
            notEmpty = 0;
            if (hasLowerBound && (currentNumber <= lowerBound))
            {
                printf("%d ", currentNumber);
            }
            else if (hasUpperBound && (currentNumber >= upperBound))
            {
                fprintf(stderr, "%d ", currentNumber);
            }
            else
            {
                backupNumbers[len] = currentNumber;
                numbers[len++] = currentNumber;
            }
            currentNumber = 0;
        }
    }
    sort(numbers, len);
    int changedPosition = 0;
    for (i = 0; i < len; i++)
        if (numbers[i] != backupNumbers[i])
            changedPosition++;
    return changedPosition;
}
