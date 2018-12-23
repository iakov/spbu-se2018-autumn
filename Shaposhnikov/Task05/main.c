#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void bubbleSort(char *arr[], int num)
{
    if (num < 2)
        return;
    for (int i = 0; i < num-1; i++)
       for (int j = 0; j < num-i-1; j++)
           if (strcmp(arr[j], arr[j+1]) > 0)
            swap(&arr[j], &arr[j+1]);
}

void insertionSort(char * arr[], int num)
{
    int i, j;
    char *key;
    for (i = 1; i < num; i++)
    {
        key = arr[i];
        j = i-1;
        while (j >= 0 && (strcmp(arr[j], key) > 0))
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

void merge(char *arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 =  right - mid;
    int i, j;
    char **L;
    if ((L = (char **)malloc(n1*sizeof(char *))) == NULL)
    {
        fprintf(stderr, "Out of memory(L)\n");
        exit(4);
    }
    char **R;
    if ((R = (char **)malloc(n2*sizeof(char *))) == NULL)
    {
        fprintf(stderr, "Out of memory (R)\n");
        exit(4);
    }
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1+ j];
    i = 0;
    j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i], R[j]) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(char * arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left+(right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(char *s_arr[], int first, int last)
{
    if (first < last)
    {
        int left = first, right = last;
        char *middle = s_arr[(left + right) / 2];
        do
        {
            while (strcmp(s_arr[left], middle) < 0) left++;
            while (strcmp(s_arr[right], middle) > 0) right--;
            if (left <= right)
            {
                char *tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(s_arr, first, right);
        quickSort(s_arr, left, last);
    }
}

void heapify(char * arr[], int num, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < num && strcmp(arr[l], arr[largest]) > 0)
        largest = l;
    if (r < num && strcmp(arr[r], arr[largest]) > 0)
        largest = r;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, num, largest);
    }
}

void heapSort(char *arr[], int num)
{
    for (int i = num / 2 - 1; i >= 0; i--)
        heapify(arr, num, i);
    for (int i=num-1; i>=0; i--)
    {
        if (strcmp(arr[0], arr[i]) != 0) 
            swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void sort(char *algorithm, char *array[], int strnum)
{
    if (strcmp("bubble", algorithm) == 0)
        bubbleSort(array, strnum);
        else if (!strcmp("insertion", algorithm))
            insertionSort(array, strnum);
            else if(!strcmp("merge", algorithm))
                mergeSort(array, 0, strnum -1);
                else if(!strcmp("quick", algorithm))
                    quickSort(array, 0, strnum - 1);
                    else if(!strcmp("radix", algorithm) || !strcmp("heap", algorithm))
                        heapSort(array, strnum);
                        else
                            {
                                fprintf(stderr, "Wrong name of algorithm\n");
                                exit(1);
                            }
}


int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Wrong amount of parameters\n");
        exit(1);
    }
    char *filename = argv[2];
    char *algorithm = argv[3];
    char *num = argv[1];
    char *temp;
    if ((temp = (char *)malloc(1000000*sizeof(char))) == NULL)
    {
        fprintf(stderr, "Out of memory (temp(main))\n");
        exit(4);
    }
    long int i;
    long int strnum = atoi(num);
    FILE * ptrFile = fopen(filename, "r");
    if (ptrFile == NULL)
    {
        fprintf(stderr, "Couldn't open a File");
        exit(2);
    }
    char **array;
    if ((array = (char **)malloc (strnum*sizeof(char*))) == NULL)
    {
        fprintf(stderr, "Out of memory (array)\n");
        exit(4);
    }
    for (i = 0; i < strnum; i++)
    {
        if (fgets(temp, 1000000, ptrFile) == NULL)
        {
            fprintf(stderr, "Couldn't scan\n");
            free(array);
            free(temp);
            exit(3);
        }
        if ((array[i] = (char *)malloc((strlen(temp)+1)*sizeof(char))) == NULL)
        {
            fprintf(stderr, "Out of memory (array[%ld]\n", i);
            free(array);
            free(temp);
            exit(4);
        }
        strcpy(array[i], temp);
    }
        sort(algorithm, array, strnum);
    for(i = 0; i < strnum; ++i)
    {
        printf("%s", array[i]);
        free(array[i]);
    }
    free(array);
    fclose (ptrFile);
    free(temp);
    return 0;
}
