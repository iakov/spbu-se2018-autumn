#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **sorted, **data;
int *len, *lenOfSorted;

void swapStrings(char **first, char **second)
{
    char *temp = *first;
    *first = *second;
    *second = temp;
}

void mergeSort(char **array, int left, int right)
{
    if (left == right - 1)
    {
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid, right);

    char **buffer = malloc((right - left) * sizeof(char*));
    int leftPtr = left;
    int rightPtr = mid;
    int current = 0;

    while (left + current < right && leftPtr < mid && rightPtr < right)
    {
        if (strcmp(array[leftPtr], array[rightPtr]) == -1)
        {
            buffer[current] = array[leftPtr];
            current++;
            leftPtr++;
        }
        if (strcmp(array[rightPtr], array[leftPtr]) <= 0)
        {
            buffer[current] = array[rightPtr];
            current++;
            rightPtr++;
        }
    }
    while (leftPtr < mid)
    {
        buffer[current] = array[leftPtr];
        current++;
        leftPtr++;
    }
    while (rightPtr < right)
    {
        buffer[current] = array[rightPtr];
        current++;
        rightPtr++;
    }


    for (int i = 0; i < right - left; ++i)
        array[left + i] = buffer[i];

    free(buffer);
}

void bubbleSort(char **array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (strcmp(array[j], array[j + 1]) == 1)
            {
                swapStrings(&array[j], &array[j + 1]);
            }
        }
    }
}

void insertionSort(char **array, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (strcmp(array[j], array[j + 1]) == 1)
            {
                swapStrings(&array[j], &array[j + 1]);
            }
        }
    }
}

void quickSort(char **array, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int leftPtr = left, rightPtr = right;
    char *mid = array[(left + right) / 2];

    while (leftPtr <= rightPtr)
    {
        while (strcmp(mid, array[leftPtr]) == 1)
        {
            leftPtr++;
        }
        while (strcmp(array[rightPtr], mid) == 1)
        {
            rightPtr--;
        }

        if (leftPtr <= rightPtr)
        {
            swapStrings(&array[leftPtr], &array[rightPtr]);
            leftPtr++;
            rightPtr--;
        }
    }

    if (left < rightPtr)
    {
        quickSort(array, left, rightPtr);
    }
    if (leftPtr < right)
    {
        quickSort(array, leftPtr, right);
    }
}

void radixSort(char **array, int size)
{
    int maxLen = 0, maxCode = 0;
    len = malloc(size * sizeof(int));
    lenOfSorted = malloc(size * sizeof(int));
    sorted = malloc(size * sizeof(char*));

    if (len == NULL || lenOfSorted == NULL || sorted == NULL)
    {
        fprintf(stderr, "Memory allocation error");
        exit(4);
    }

    for (int i = 0; i < size; ++i)
    {
        len[i] = strlen(array[i]);
        for (int j = 0; j < len[i]; ++j)
        {
            if ((int) array[i][j] > maxCode)
            {
                maxCode = (int) array[i][j];
            }
        }
        if (maxLen < len[i])
        {
            maxLen = len[i];
        }
    }

    maxCode++;
    int *dict = calloc(maxCode, sizeof(int));

    if (dict == NULL)
    {
        fprintf(stderr, "Memory allocation error");
        exit(4);
    }

    for (int charNum = maxLen - 1; charNum >= 0; --charNum)
    {
        for (int i = 0; i < maxCode; ++i)
        {
            dict[i] = 0;
        }

        for (int i = 0; i < size; ++i)
        {
            int x = (charNum >= len[i]) ? 0 : (int) array[i][charNum];
            dict[x]++;
        }

        int sum = 0;

        for (int i = 0; i < maxCode; ++i)
        {
            int temp = dict[i];
            dict[i] = sum;
            sum += temp;
        }

        for (int i = 0; i < size; ++i)
        {
            int x = (charNum >= len[i]) ? 0 : ((int) array[i][charNum]);
            sorted[dict[x]] = array[i];
            lenOfSorted[dict[x]] = len[i];
            dict[x]++;
        }

        for (int i = 0; i < size; ++i)
        {
            len[i] = lenOfSorted[i];
        }
        for (int i = 0; i < size; ++i)
        {
            array[i] = sorted[i];
        }
    }
    free(dict);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Invalid number of arguments");
        exit(1);
    }
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file");
        exit(2);
    }
    int n = atoi(argv[1]);
    data = malloc((n + 1) * sizeof(char*));
    for (int i = 0; ; ++i)
    {
        if (i > n)
        {
            fprintf(stderr, "Invalid data");
            exit(3);
        }

        data[i] = malloc(sizeof(char));
        if (data[i] == NULL)
        {
            fprintf(stderr, "Memory allocation error");
            exit(4);
        }

        char input;
        int len = 0;
        int size = 1;
        while ((input = fgetc(file)) != '\n')
        {
            if (input == EOF)
            {
                break;
            }
            len++;
            if (size <= len)
            {
                size <<= 1;
                data[i] = (char*) realloc(data[i], size * sizeof(char));
                if (data[i] == NULL)
                {
                    fprintf(stderr, "Memory allocation error");
                    exit(4);
                }
            }
            data[i][len - 1] = input;
            data[i][len] = '\0';
        }
        if (input == EOF)
        {
            break;
        }
    }

    char *type = argv[3];

    if (strcmp(type, "bubble") == 0)
    {
        bubbleSort(data, n);
    }
    else if (strcmp(type, "insertion") == 0)
    {
        insertionSort(data, n);
    }
    else if (strcmp(type, "merge") == 0)
    {
        mergeSort(data, 0, n);
    }
    else if (strcmp(type, "quick") == 0)
    {
        quickSort(data, 0, n - 1);
    }
    else if (strcmp(type, "radix") == 0)
    {
        radixSort(data, n);
    }
    else
    {
        fprintf(stderr, "Invalid algo name");
        exit(1);
    }


    //clock_t t2 = clock();
    for (int i = 0; i < n; ++i)
    {
        printf("%s\n", data[i]);
        free(data[i]);
    }
    free(data[n]);
    //printf("Time: %.20f\n", ((double) (t2 - t1) / CLOCKS_PER_SEC));

    fclose(file);

    return 0;
}
