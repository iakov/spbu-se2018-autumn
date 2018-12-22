#include<stdio.h>

extern void sort(int *begin, int len);

int intFromString(char *s)
{
    int pos = 0;
    int intFound = 0;
    int sign = 1;
    int res = 0;
    while (s[pos] != 0)
    {
        if ((s[pos] >= '0') && (s[pos] <= '9'))
        {
            res = res * 10 + (int)(s[pos] - '0');
            intFound = 1;
        }
        else if (s[pos] == '-')
            sign = -1;
        else if (!intFound)
            sign = 1;
        else
            break;
        pos++;
    }
    res = res * sign;
    return res;
}

int main(int argc, char **argv)
{
    int hasLowerBound = 0;
    int hasUpperBound = 0;
    int lowerBound = 0, upperBound = 0;
    int i;
    int garbageCan;
    int *currentReading = &garbageCan;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][1] != 0 && argv[i][2] == 'f')
        {
            hasLowerBound = 1;
            currentReading = &lowerBound;
        }
        else if (argv[i][1] != 0 && argv[i][2] == 't')
        {
            hasUpperBound = 1;
            currentReading = &upperBound;
        }
        *currentReading = intFromString(argv[i]);
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
