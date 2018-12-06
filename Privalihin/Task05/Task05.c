#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swapCStrings(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapSort(char **array, int len)
{
    int heapSize = 4 * len;
    char **heap = calloc(heapSize, sizeof(char *));
    if (heap == NULL)
    {
        printf("Failed to allocate memory for the heap\n");
        fflush(stdout);
        return;
    }
    for (int i = 0; i < len; i++)
    {
        int pos = 1;
        while (heap[pos] != NULL)
        {
            if (0 < strcmp(heap[pos], array[i]))
            {
                swapCStrings(heap + pos, array + i);
            }
            /*We balance the tree by randomly choosing the branch to add the new element.
            The element stored in heap[pos] has children stored in heap[2 * pos] and heap[2 * pos + 1]*/
            pos = 2 * pos + (rand() & 1);
            /*If choosing the random branch has led us too far, we can just start again.
            Since heapSize is 4 times bigger than the actual amount of elements,
            we are quite likely to find a good place for the element soon enough. */
            if (pos > heapSize)
                pos = 1;
        }
        heap[pos] = array[i];
    }
    for (int i = 0; i < len; i++)
    {
        array[i] = heap[1];
        int pos = 1;
        while (pos < heapSize)
        {
            if (2 * pos > heapSize || heap[2 * pos] == NULL)
            {
                if (2 * pos + 1 > heapSize || heap[2 * pos + 1] == NULL)
                {
                    heap[pos] = NULL;
                    break;
                }
                else
                {
                    heap[pos] = heap[2 * pos + 1];
                    pos = 2 * pos + 1;
                }
            }
            else if (2 * pos + 1 > heapSize || heap[2 * pos + 1] == NULL || strcmp(heap[2 * pos + 1], heap[2 * pos]) > 0)
            {
                heap[pos] = heap[2 * pos];
                pos = 2 * pos;
            }
            else
            {
                heap[pos] = heap[2 * pos + 1];
                pos = 2 * pos + 1;
            }
        }
    }
    free(heap);
}

void bubbleSort(char **array, int len)
{
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            if (strcmp(array[i], array[j]) > 0)
                swapCStrings(array + i, array + j);
}

void mergeSort(char **array, int len)
{
    if (len <= 1)
        return;
    int m = len / 2;
    mergeSort(array, m);
    mergeSort(array + m, len - m);
    char ** tmp = malloc(len * sizeof(char *));
    if (tmp == NULL)
    {
        printf("Failed to allocate memory for the mergeSort\n");
        fflush(stdout);
        return;
    }
    int posLeft = 0, posRight = m, pos = 0;
    while (posLeft < m)
    {
        if (posRight >= len || strcmp(array[posRight], array[posLeft]) > 0)
            tmp[pos++] = array[posLeft++];
        else
            tmp[pos++] = array[posRight++];
    }
    while (posRight < len)
       tmp[pos++] = array[posRight++];
    for (int i = 0; i < len; i++)
        array[i] = tmp[i];
    free(tmp);
}

void insertionSort(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        for (; j < i &&  strcmp(array[i], array[j]) > 0; j++);
        for (; j < i; j++)
            swapCStrings(array + i, array + j);
    }
}

void quickSort(char **array, int len)
{
    if (len <= 1)
        return;
    char *separator = array[rand() % len];
    int l = 0, r = len - 1;
    while (l < r)
    {
        while (strcmp(array[l], separator) < 0)
            l++;
        while (strcmp(separator, array[r]) < 0)
            r--;
        if (l >= r)
            break;
        swapCStrings(array + r, array + l);
        r--;
        l++;
    }
    quickSort(array, l);
    quickSort(array + l, len - l);
}

void sortWithGivenAlgorithm(char **array, int len, char *algorithm)
{
    //This is not the most reliable way to do this, but unfortunately switch doesn't work with C strings, since it uses the actual value
    switch (algorithm[0])
    {
    case 'b':
        bubbleSort(array, len);
        break;
    case 'h':
        heapSort(array, len);
        break;
    case 'i':
        insertionSort(array, len);
        break;
    case 'm':
        mergeSort(array, len);
        break;
    case 'q':
        quickSort(array, len);
        break;
    default:
        printf("Error detected! Unknown algorithm requested! Initiating godSort, ETA 999 years...\n");
        break;
    }
}


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Invalid number of arguments!\n");
        return 1;
    }
    srand(time(0));
    FILE *infile = fopen(argv[2], "r");
    if (infile == NULL)
    {
        printf("Unable to open file\n");
        fflush(stdout);
        return 0;
    }
    int linesCount = atoi(argv[1]);
    int lineSize = 1000000;
    char **text = (char **)malloc(linesCount * sizeof(char *));
    if (text == NULL)
    {
        printf("Unable to allocate enough memory\n");
        fflush(stdout);
        return 0;
    }
    char *buffer = (char *)malloc(lineSize);
    if (buffer == NULL)
    {
        free(text);
        printf("Unable to allocate enough memory\n");
        fflush(stdout);
        return 0;
    }
    int len;
    for (len = 0; len < linesCount ; len++)
    {
        if (fgets(buffer, lineSize, infile) == NULL)
        {
            free(buffer);
            for (int i = 0; i < len; i++)
                free(text[i]);
            free(text);
            printf("Unable to read more than %d lines\n", len);
            fflush(stdout);
            return 0;
        }
        text[len] = malloc((strlen(buffer) + 1) * sizeof(char));
        if (text[len] == NULL)
        {
            free(buffer);
            for (int i = 0; i < len; i++)
                free(text[i]);
            free(text);
            printf("Unable to allocate enough memory\n");
            fflush(stdout);
            return 0;
        }
        strcpy(text[len], buffer);
    }
    sortWithGivenAlgorithm(text, len, argv[3]);
    for (int i = 0; i < len; i++)
        printf("%s", text[i]);
    for (int i = 0; i < linesCount; i++)
        free(text[i]);
    free(text);
    free(buffer);
    fflush(stdout);
    fclose(infile);
    return 0;
}
