#include <stdio.h>
#include <limits.h>
#include <string.h>

int from = INT_MIN, to = INT_MAX;
extern void quickSortR(int *a, int low, int high);

int stringToInt(char *str, int index)
{
    int resultNumber = 0;
    int sign = 1;

    for (int i = index; i < strlen(str); i++)
    {
        if (str[i] == '-')  //sign check
        {
            sign = -1;
            continue;
        }
        resultNumber = resultNumber * 10 + (str[i] - '0');
    }

    return resultNumber * sign;
}

void defineBounds(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][2] == 'f')  //if we read --from
        {
            from = stringToInt(argv[i], 7);
        }
        if (argv[i][2] == 't')  //if we read --to
        {
            to = stringToInt(argv[i], 5);
        }
    }
}

int main(int argc, char *argv[])
{
    defineBounds(argc, argv);

    int raw_numbers[100]; //for non-sorted numbers
    int numbers[100];     //for sorted numbers

    char input_char = ' ';
    int number, index = 0;

    while (input_char != '\n' && input_char != '\0')
    {
        scanf("%d%c", &number, &input_char);
        if (number < to && number > from)
        {
            raw_numbers[index] = number;
            index++;
        }
        else if (number <= from) fprintf(stdout, "%d ", number);
        if (number >= to) fprintf(stderr, "%d ", number);
    }

    for (int i = 0; i < index; i++)
    {
        numbers[i] = raw_numbers[i];
    }

    quickSortR(numbers, 0, index - 1);

    int differenceCounter = 0;
    printf("\nSorted: ");
    for (int i = 0; i < index; i++)
    {
        if (numbers[i] != raw_numbers[i]) differenceCounter++;
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}