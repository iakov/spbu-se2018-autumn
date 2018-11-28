#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void swapCharPointers(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapSort(char **array, int len)
{
    int heapSize = 4 * len;
    char **heap = calloc(heapSize, sizeof(char *));
    for (int i = 0; i < len; i++)
    {
        int pos = 1;
        while (heap[pos] != NULL)
        {

            if (0 < strcmp(heap[pos], array[i]))
            {
                swapCharPointers(heap + pos, array + i);
            }
            pos = 2 * pos + (rand() & 1);
            if (pos > heapSize)//если рандомный выбор ветки завел нас не туда, всегда можно начать заново!
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
                swapCharPointers(array + i, array + j);
}

void mergeSort(char **array, int len)
{
    if (len == 1)
        return;
    int m = len / 2;
    mergeSort(array, m);
    mergeSort(array + m, len - m);
    char ** tmp = malloc(len * sizeof(char *));
    int pos1 = 0, pos2 = m, pos = 0;
    while (pos1 < m)
    {
        if (pos2 >= len || strcmp(array[pos2], array[pos1]) > 0)
            tmp[pos++] = array[pos1++];
        else
            tmp[pos++] = array[pos2++];
    }
    while (pos2 < len)
       tmp[pos++] = array[pos2++];
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
            swapCharPointers(array + i, array + j);
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
        swapCharPointers(array + r, array + l);
        r--;
        l++;
    }
    quickSort(array, l);
    quickSort(array + l, len - l);
}

void hubSort(char **array, int len, char *algorithm)
{
    if (!strcmp(algorithm, "bubble"))
        bubbleSort(array, len);
    else if (!strcmp(algorithm, "insertion"))
        insertionSort(array, len);
    else if (!strcmp(algorithm, "merge"))
        mergeSort(array, len);
    else if (!strcmp(algorithm, "quick"))
        quickSort(array, len);
    else if (!strcmp(algorithm, "heap"))
        heapSort(array, len);
    else
        printf("Error detected! Unknown algorithm requested! Initiating godSort, ETA 999 years...\n");
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
    int linesCount = atoi(argv[1]);
    int lineSize = 1000000;
    char **text = (char **)malloc(linesCount * sizeof(char *));
    char *buffer = (char *)malloc(lineSize);
    int len;
    for (len = 0; len < linesCount ; len++)
    {
        if (fgets(buffer, lineSize, infile) == NULL)
            break;
        text[len] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(text[len], buffer);
    }
    hubSort(text, len, argv[3]);
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
