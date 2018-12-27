#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
/*
 * errors.h includes:
 *
 * all functions exit with the appropriate
 * code and print an error message
 *
 * 1) void ExitWithArgumentError(int argc)
 * 2) void ExitWithFileError(char *path)
 * 3) void ExitWithInputDataError(char *filename)
 * 4) void ExitWithMemoryError()
 *
 ==================================================
 *
 * Input file must contain N lines of 10 characters
 *
 * Application exit codes:
 *
 * 1 - invalid program argument
 * 2 - missing required file
 * 3 - incorrect input data
 * 4 - system function call error
 * 5 - reserved
 */

void strSwap(char **x, char **y)
{
    char *temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(char **str_array, int strNum)
{
    for (int i = 0; i < strNum; i++)
    {
        for (int j = i + 1; j < strNum; j++)
        {
            if (strcmp(str_array[i], str_array[j]) > 0)
                strSwap(&str_array[i], &str_array[j]);
        }
    }
}

void insertionSort(char **str_array, int strNum)
{
    int j = 0;

    for (int i = 1; i < strNum; i++)
    {
        j = i;
        while ((j > 0) && (strcmp(str_array[j - 1], str_array[j]) > 0))
        {
            strSwap(&str_array[j - 1], &str_array[j]);
            j--;
        }
    }
}

void merge(char **str_array, int strNum)
{
    int middle = strNum / 2;

    char **tmp = malloc(strNum * sizeof(char *));
    if (tmp == NULL)
    {
        printf("Not enough memory\n");
        exit(4);    //4 - system function call error exit code
    }
    int left = 0, right = middle, cur_pos = 0;
    while (left < middle)
    {
        if (right >= strNum || strcmp(str_array[right], str_array[left]) > 0)
            tmp[cur_pos++] = str_array[left++];
        else
            tmp[cur_pos++] = str_array[right++];
    }
    while (right < strNum)
        tmp[cur_pos++] = str_array[right++];
    for (int i = 0; i < strNum; i++)
        str_array[i] = tmp[i];
    free(tmp);
}
void mergeSort(char **str_array, int strNum)
{
    if (strNum <= 1) return;
    int middle = strNum / 2;
    mergeSort(str_array, middle);
    mergeSort(str_array + middle, strNum - middle);

    merge(str_array, strNum);
}

void quickSort(char **str_array, int left, int right)
{
    int l_pointer = left;
    int r_pointer = right;
    char *pivot = str_array[(left + (right - left)/2)];
    do
    {
        while((strcmp(str_array[l_pointer], pivot) < 0))
        {
            l_pointer++;
        }
        while((strcmp(str_array[r_pointer], pivot) > 0))
        {
            r_pointer--;
        }
        if(l_pointer <= r_pointer)
        {
            if((strcmp(str_array[l_pointer], str_array[r_pointer]) > 0))
            {
                strSwap(&str_array[l_pointer], &str_array[r_pointer]);
            }
            l_pointer++;
            if (r_pointer > 0)
            {
                r_pointer--;
            }
        }
    } while (l_pointer <= r_pointer);

    if(l_pointer < right)
    {
        quickSort(str_array, l_pointer, right);
    }
    if(r_pointer > left)
    {
        quickSort(str_array, left, r_pointer);
    }
}

void heapify(char* str_array[], int strNum, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < strNum && strcmp(str_array[left], str_array[largest]) > 0)
    {
        largest = left;
    }

    if (right < strNum && strcmp(str_array[right], str_array[largest]) > 0)
    {
        largest = right;
    }

    if (largest != i)
    {
        strSwap(&str_array[i], &str_array[largest]);
        heapify(str_array, strNum, largest);
    }
}
void heapSort(char **str_array, int strNum)
{
    for (int i = strNum / 2 - 1; i >= 0; i--)
    {
        heapify(str_array, strNum, i);
    }

    for (int i = strNum - 1; i >= 0; i--)
    {
        strSwap(&str_array[0], &str_array[i]);
        heapify(str_array, i, 0);
    }
}

void sort(char **str_array, int linesNumber, const char *alg)
{
    if (strcmp(alg,"bubble") == 0)
    {
        bubbleSort(str_array, linesNumber);
    }
    else if (strcmp(alg,"insertion") == 0)
    {
        insertionSort(str_array, linesNumber);
    }
    else if (strcmp(alg,"merge") == 0)
    {
        mergeSort(str_array, linesNumber);
    }
    else if (strcmp(alg,"quick") == 0)
    {
        quickSort(str_array, 0, linesNumber - 1);
    }
    else if (strcmp(alg,"heap") == 0)
    {
        heapSort(str_array, linesNumber);
    }
    else if (strcmp(alg,"radix") == 0)
    {
        heapSort(str_array, linesNumber);
    }
    else
    {
        fprintf(stderr, "Unknown sorting algorithm! (%s)\n", alg);
        exit(1);    //1 - invalid program argument exit code
    }
}

void ReleaseMemory(char **str_array, int str_array_size, char* temp)
{
    for (int i = 0; i < str_array_size; i++)
    {
        free(str_array[i]);
    }
    free(str_array);
    free(temp);
}

const int LINE_LENGTH = 1337228;

int main(int argc, char *argv[])
{
    if (argc != 4)
        ExitWithArgumentError(argc);

    int LINES_NUMBER = (int)strtol(argv[1], NULL, 10);
    char *IN_FILE_NAME = argv[2];
    char *ALG_NAME = argv[3];

    FILE *i_file = fopen(IN_FILE_NAME, "r");
    if (i_file == NULL)
        ExitWithFileError(IN_FILE_NAME);

    char **str_array = malloc(LINES_NUMBER * sizeof(char *));
    if (str_array == NULL)
        ExitWithMemoryError();

    char *temp = malloc(LINE_LENGTH);
    if (temp == NULL)
        ExitWithMemoryError();

    int current_line_number = 0;
    for (current_line_number = 0; current_line_number < LINES_NUMBER; current_line_number++)
    {
        if (fgets(temp, LINE_LENGTH, i_file) == NULL)
        {
            if (current_line_number < LINE_LENGTH)
                ExitWithInputDataError(IN_FILE_NAME);
            break;
        }

        str_array[current_line_number] = malloc((strlen(temp) + 1) * sizeof(char));
        if (str_array[current_line_number] == NULL)
        {
            ReleaseMemory(str_array, current_line_number, temp);
            ExitWithMemoryError();
        }
        strcpy(str_array[current_line_number], temp);
    }

    if (current_line_number > 0)
        sort(str_array, current_line_number, ALG_NAME);

    for (int i = 0; i < current_line_number; i++)
    {
        printf("%s", str_array[i]);
    }

    ReleaseMemory(str_array, current_line_number, temp);
    fclose(i_file);

    return 0;
}