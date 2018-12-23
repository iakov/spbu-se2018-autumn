#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int MAX_LENGTH = 100;

void bubbleSort(char *arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void insertionSort(char *arr[], int n)
{
    int i, j;
    char *key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(char *arr[], int left, int mid, int right)
{
    int indFirst, indSecond, indMiddle;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    char **leftArr, **rightArr;
    leftArr = (char**) malloc(n1 * sizeof(char*));
    rightArr = (char**) malloc(n2 * sizeof(char*));
    if (leftArr == NULL || rightArr == NULL)
    {
        printf("Cannot allocate memory for subarrays.\n");
        exit(4);
    }

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    indFirst = 0;
    indSecond = 0;
    indMiddle = left;

    while (indFirst < n1 && indSecond < n2)
    {
        if (strcmp(leftArr[indFirst], rightArr[indSecond]) <= 0)
        {
            arr[indMiddle] = leftArr[indFirst];
            indFirst++;
        }
        else
        {
            arr[indMiddle] = rightArr[indSecond];
            indSecond++;
        }
        indMiddle++;
    }

    while (indFirst < n1)
    {
        arr[indMiddle] = leftArr[indFirst];
        indFirst++;
        indMiddle++;
    }
    while (indSecond < n2)
    {
        arr[indMiddle] = rightArr[indSecond];
        indSecond++;
        indMiddle++;
    }

    free(leftArr);
    free(rightArr);
}

void mergeSort(char *arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(char *arr[], int first, int last)
{
    if (first < last)
    {
        int left = first, right = last;
        char *middle = arr[(left + right) / 2];
        do
        {
            while (strcmp(arr[left], middle) < 0)
                left++;
            while (strcmp(arr[right], middle) > 0)
                right--;
            if (left <= right)
            {
                char *tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        }
        while (left <= right);
        quickSort(arr, first, right);
        quickSort(arr, left, last);
    }
}

void heapify(char *arr[], int n, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && strcmp(arr[left], arr[largest]) > 0)
        largest = left;
    if (right < n && strcmp(arr[right], arr[largest]) > 0)
        largest = right;

    if (largest != i)
    {
        char* temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(char *arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        char* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
		printf("Wrong number of parameters.\n");
		exit(1);
	}

    int linesAmount = atoi(argv[1]);
    char *fileName = argv[2];
    char *sortName = argv[3];

    char **data = (char**) malloc(linesAmount * sizeof(char*));
    if (data == NULL)
    {
        printf("Cannot allocate memory for array.\n");
        exit(4);
    }

    char *buffer = (char*) malloc(MAX_LENGTH * sizeof(char));
    if (buffer == NULL)
    {
        free(data);
        printf("Cannot allocate memory for buffer.\n");
        exit(4);
    }

    FILE *stringsFile;
    stringsFile = fopen(fileName, "r");
    if (stringsFile == NULL)
    {
        printf("Cannot open file.\n");
        exit(2);
    }

    for (int i = 0; i < linesAmount; i++)
    {
        if (fgets(buffer, MAX_LENGTH, stringsFile) == NULL)
        {
            linesAmount = i;
            break;
        }
        data[i] = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (data[i] == NULL)
        {
            printf("Cannot allocate memory for next string, %d.\n", i);
            free(buffer);
            for (int j = 0; j < i; j++)
                free(data[j]);
            free(data);
            exit(4);
        }
        strcpy(data[i], buffer);
    }

    fclose(stringsFile);
    free(buffer);

    if (strcmp(sortName, "bubble") == 0)
    {
        bubbleSort(data, linesAmount);
    }
    else if (strcmp(sortName, "insertion") == 0)
    {
        insertionSort(data, linesAmount);
    }
    else if (strcmp(sortName, "merge") == 0)
    {
        mergeSort(data, 0, linesAmount - 1);
    }
    else if (strcmp(sortName, "quick") == 0)
    {
        quickSort(data, 0, linesAmount - 1);
    }
    else if (strcmp(sortName, "radix") == 0 || strcmp(sortName, "heap") == 0)
    {
        heapSort(data, linesAmount);
    }
    else
    {
        printf("Wrong algorithm\n");
        exit(1);
    }

    for (int i = 0; i < linesAmount; i++)
        printf("%s", data[i]);

    for (int i = 0; i < linesAmount; i++)
        free(data[i]);

    free(data);
    return 0;
}
