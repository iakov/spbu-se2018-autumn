#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        exit(4);
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

int partition(char **strArr, int left, int right)
{
    char *pivotVal = strArr[left];
    int leftPos = left;
    int rightPos = right;
    while (leftPos < rightPos)
    {
        while (strcmp(strArr[leftPos], pivotVal) < 0)
        {
            leftPos++;
        }
        while (strcmp(strArr[rightPos], pivotVal) > 0)
        {
            rightPos--;
        }
        if (leftPos >= rightPos)
            return rightPos;
        swapChars(&strArr[rightPos], &strArr[leftPos]);
    }
    return 0;
}

void quickSort(char **strArr, int left, int right)
{
    if (left < right)
    {
        int splitPoint = partition(strArr, left, right);
        quickSort(strArr, left, splitPoint);
        quickSort(strArr, splitPoint + 1, right);
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
        exit(1);
    }
    int lineMaxLen = 1000000;
    int arrMaxLen = atoi(argv[1]);
    char *filename = argv[2];
    char *algorithm = argv[3];

    //Reading text file
    FILE *textFile = fopen(filename, "r");   
    if (textFile == NULL) 
    {
        fprintf(stderr, "Unable to open file!\n");
        exit(2);
    }
    char **strArr = mallocCheck(arrMaxLen * sizeof(char *));
    char *buffer = mallocCheck(lineMaxLen);
    int arrLen = 0;
    for (arrLen = 0; arrLen < arrMaxLen; arrLen++)
    {
        if (fgets(buffer, lineMaxLen, textFile) == NULL)
        {
            //Amount of strings is less than max amount from arguments
            break;
        }
        strArr[arrLen] = mallocCheck((strlen(buffer) + 1) * sizeof(char));
        strcpy(strArr[arrLen], buffer);
    }
    fclose(textFile);
    free(buffer);

    if (strcmp(algorithm, "bubble") == 0)
    {
        bubbleSort(strArr, arrLen);
    }
    else if (strcmp(algorithm, "heap") == 0)
    {
        heapSort(strArr, arrLen);
    }
    else if (strcmp(algorithm, "insertion") == 0)
    {
        insertionSort(strArr, arrLen);
    }
    else if (strcmp(algorithm, "merge") == 0)
    {
        mergeSort(strArr, arrLen);
    }
    else if (strcmp(algorithm, "quick") == 0)
    {
        quickSort(strArr, 0, arrLen - 1);
    }
    else if (strcmp(algorithm, "radix") == 0)
    {
        heapSort(strArr, arrLen);
    }
    else
    {
        printf("Unknown algorithm!\n");
        exit(1);
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
