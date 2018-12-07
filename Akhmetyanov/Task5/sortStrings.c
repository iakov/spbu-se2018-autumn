#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void swapChars(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void *mallocCheck(size_t n)
{
    //Checking for NULL malloc return value
    void *memPtr = malloc(n);
    if (memPtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory!\n");
        exit(EXIT_FAILURE);
    }
    return memPtr;
}

void bubbleSort(char **strArr, int arrLen)
{
    for (int i = 0; i < arrLen; i++)
    {
        for (int j = i + 1; j < arrLen; j++)
        {
            if (strcmp(strArr[i], strArr[j]) > 0)
            {
                swapChars(&strArr[i], &strArr[j]);
            }
        }
    }
}

void insertionSort(char **strArr, int arrLen)
{
    int j = 0;

    for (int i = 1; i < arrLen; i++)
    {
        j = i;
        while ((j > 0) && (strcmp(strArr[j - 1], strArr[j]) > 0))
        {
            swapChars(&strArr[j - 1], &strArr[j]);
            j--;
        }
    }
}

void mergeSort(char **strArr, int arrLen)
{
    int mid = arrLen / 2;
    if (mid > 1)
    {
        mergeSort(strArr, mid);
    }
    if (arrLen - mid > 1)
    {
        mergeSort(strArr + mid, arrLen - mid);
    }
    int leftPos = 0;
    int rightPos = mid;
    int pos = 0;
    char ** temp = mallocCheck((arrLen) * sizeof(char *));
    while (leftPos < mid && rightPos < arrLen)
    {
        if (strcmp(strArr[leftPos], strArr[rightPos]) < 0)
        {
            temp[pos++] = strArr[leftPos++];
        }
        else
        {
            temp[pos++] = strArr[rightPos++];
        }
    }
    while (leftPos < mid)
    {
        temp[pos++] = strArr[leftPos++];
    }
    while (rightPos < arrLen)
    {
        temp[pos++] = strArr[rightPos++];
    }
    for (pos = 0; pos < arrLen; pos++)
    {
        strArr[pos] = temp[pos];
    }
    free(temp);
}

void quickSort(char **strArr, int arrLen)
{
    int leftPos = 0;
    int rightPos = arrLen - 1;
    char *mid = strArr[arrLen / 2];
    while (leftPos < rightPos)
    {
        while (strcmp(strArr[leftPos], mid) < 0)
        {
            leftPos++;
        }

        while (strcmp(strArr[rightPos], mid) > 0)
        {
            rightPos--;
        }

        if (leftPos < rightPos)
        {
            swapChars(&strArr[rightPos], &strArr[leftPos]);
            rightPos--;
            leftPos++;
        }
    }
    if (leftPos > 1)
    {
    	quickSort(strArr, leftPos);
    }
    if (arrLen - leftPos > 1)
    {
    	quickSort(strArr + leftPos, arrLen - leftPos);
    }
}

void heapify(char **strArr, int root, int num) 
{
    /*
    strArr[root + 1]..[k] is already a heap,
    strArr[root] is being added
    */

    int child;
    while(2 * root + 1 < num) 
    {
        child = 2 * root + 1;
        if (child < num - 1 && strcmp(strArr[child], strArr[child + 1]) < 0) 
        {
            child++;
        }
        if (strcmp(strArr[root], strArr[child]) > 0) 
        {
            break; 
        }
        swapChars(&strArr[root], &strArr[child]);
        root = child;
    }
}

void heapSort(char **strArr, int arrLen)
{
    for (int i = arrLen / 2 - 1; i >= 0; i--)
    {
        heapify(strArr, i, arrLen);
    }
    for (int i = arrLen - 1; i >= 0; i--)
    {
        swapChars(&strArr[0], &strArr[i]);
        heapify(strArr, 0, i);
    }
}

int main(int argc, char *argv[]) 
{
    //Checking input arguments
    if (argc != 4)
    {
        printf("Invalid argument number!\n");
        exit(EXIT_FAILURE);
    }
    int arrLen = atoi(argv[1]);
    char *filename = argv[2];
    char algorithm = argv[3][0];

    //Reading text file
    FILE *textFile = fopen(filename, "r");   
    if (textFile == NULL) 
    {
        fprintf(stderr, "Unable to open file!\n");
        exit(EXIT_FAILURE);
    }
    char **strArr = mallocCheck(arrLen * sizeof(char *));
    char *buffer = mallocCheck(LINE_MAX);
    for (int i = 0; i < arrLen; i++)
    {
        if (fgets(buffer, LINE_MAX, textFile) == NULL)
        {
            fprintf(stderr, "Unable to read input!\n");
            for (int j = 0; j < arrLen; j++)
            {
                free(strArr[j]);
            }
            free(strArr);
            free(buffer);
            exit(EXIT_FAILURE);
        }
        strArr[i] = mallocCheck((strlen(buffer) + 1) * sizeof(char));
        strcpy(strArr[i], buffer);
    }
    fclose(textFile);
    free(buffer);

    switch (algorithm)
    {
        case 'q' :
            quickSort(strArr, arrLen);
            break;
        case 'm' :
            mergeSort(strArr, arrLen);
            break;
        case 'b' :
            bubbleSort(strArr, arrLen);
            break;
        case 'i' :
            insertionSort(strArr, arrLen);
            break;
        case 'h' :
            heapSort(strArr, arrLen);
            break;
        default:
            printf("Unknown algorithm!\n");
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < arrLen; i++)
    {
        printf("%s", strArr[i]);
    }
    for (int i = 0; i < arrLen; i++)
    {
        free(strArr[i]);
    }
    free(strArr);
    return 0;
}
