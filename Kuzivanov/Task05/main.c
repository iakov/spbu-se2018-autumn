#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int *arr, *buffer, n;
char *file_str;
const int MAX_LEN_STR = 10000;
const int MAX_LEN_FILE = 1000000000;

void bubble_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < n-i; j++)
        {
            if (strcmp(file_str + arr[j], file_str + arr[j-1]) < 0)
            {
                swap_in_array(j, j - 1, arr);
            }
        }
    }
}

void insertion_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i - 1; j >= 0 && strcmp(file_str + arr[i], file_str + arr[j]) < 0; j--) {}
        shift_in_array(j+1, i, arr);
    }
}

void merge_sort(int left, int right)
{
    if (left == right-1) return;
    int middle = (left + right) / 2, left_ptr = left, right_ptr = middle, i;
    merge_sort(left, middle);
    merge_sort(middle, right);
    for (i = left; i < right; i++)
    {
        if (left_ptr == middle || (right_ptr != right && strcmp(file_str + arr[right_ptr], file_str + arr[left_ptr]) < 0))
        {
            buffer[i] = arr[right_ptr];
            right_ptr++;
        }
        else
        {
            buffer[i] = arr[left_ptr];
            left_ptr++;
        }
    }
    for (i = left; i < right; i++) arr[i] = buffer[i];
}

void quick_sort(int left, int right)
{
    if (left + 1 >= right) return;
    int middle = (2 * left + right - 1) / 3, left_ptr = left, right_ptr = right - 1;
    while (left_ptr != right_ptr)
    {
        while (left_ptr < right_ptr && strcmp(file_str + arr[left_ptr], file_str + arr[middle]) < 0)
            left_ptr++;
        while (left_ptr < right_ptr && strcmp(file_str + arr[middle], file_str + arr[right_ptr]) < 0)
            right_ptr--;
        swap_in_array(left_ptr, right_ptr, arr);
        if (middle == left_ptr || middle == right_ptr)
            middle = left_ptr + right_ptr - middle;
        if (strcmp(file_str + arr[left_ptr], file_str + arr[right_ptr]) >= 0 && left_ptr < right_ptr)
            left_ptr++;
    }
    quick_sort(left, left_ptr);
    quick_sort(right_ptr + 1, right);
}

void radix_sort(int left, int right, int pos)
{
    if (left + 1 >= right) return;
    int char_quant[257], i, j, ptr = left;
    for (i = 1; i < 257; i++)
        char_quant[i] = 0;
    char_quant[0] = left;
    for (i = left; i < right; i++)
    {
        char_quant[file_str[arr[i] + pos] + 1]++;
        buffer[i] = arr[i];
    }
    for (i = 1; i < 257; i++)
        char_quant[i] += char_quant[i-1];
    for (i = 0; i < 257; i++)
    {
        for (j = left; j < right; j++)
        {
            if (file_str[buffer[j] + pos] == i)
            {
                arr[ptr] = buffer[j];
                ptr++;
            }
        }
    }
    for (i = 1; i < 256; i++)
        radix_sort(char_quant[i], char_quant[i+1], pos+1);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Error: Incorrect number of parameters.");
        exit(1);
    }
    FILE *file_input = fopen(argv[2], "r");
    if (file_input == 0)
    {
        printf("Error: File \"%s\" was not found.", argv[2]);
        exit(2);
    }
    int line_ptr, char_ptr;
    for (char_ptr = 0; argv[1][char_ptr]; char_ptr++)
    {
        if (argv[1][char_ptr] < '0' || argv[1][char_ptr] > '9')
        {
            printf("Error: \"%s\" is NaN.", argv[1]);
            exit(1);
        }
        n = n * 10 + argv[1][char_ptr] - '0';
    }
    file_str = malloc(MAX_LEN_FILE);
    if (file_str == 0)
    {
        printf("Error: Unable to allocate memory of required size.");
        exit(5);
    }
    arr = malloc(4 * n + 4);
    if (arr == 0)
    {
        printf("Error: Unable to allocate memory of required size.");
        exit(5);
    }
    arr[0] = 0;
    char reading_str[MAX_LEN_STR];
    for (line_ptr = 0; line_ptr < n; line_ptr++)
    {
        if (fgets(reading_str, MAX_LEN_STR, file_input) == 0)
        {
            printf("Error: Insufficient number of lines in the file \"%s\"", argv[2]);
            exit(3);
        }
        for (char_ptr = 0; reading_str[char_ptr] != '\n' && reading_str[char_ptr]; char_ptr++)
        {
            file_str[arr[line_ptr] + char_ptr] = reading_str[char_ptr];
        }
        file_str[arr[line_ptr] + char_ptr] = '\0';
        arr[line_ptr + 1] = arr[line_ptr] + char_ptr + 1;
    }
    switch (argv[3][0])
    {
    case 'b':
        if (strcmp(argv[3], "bubble") == 0)
        {
            bubble_sort();
        }
        else
        {
            printf("Error: Sort \"%s\" was not found.", argv[3]);
            exit(1);
        }
        break;
    case 'i':
        if (strcmp(argv[3], "insertion") == 0)
        {
            insertion_sort();
        }
        else
        {
            printf("Error: Sort \"%s\" was not found.", argv[3]);
            exit(1);
        }
        break;
    case 'm':
        if (strcmp(argv[3], "merge") == 0)
        {
            buffer = malloc(4 * n + 4);
            if (buffer == 0)
            {
                printf("Error: Unable to allocate memory of required size.");
                exit(5);
            }
            merge_sort(0, n);
            free(buffer);
        }
        else
        {
            printf("Error: Sort \"%s\" was not found.", argv[3]);
            exit(1);
        }
        break;
    case 'q':
        if (strcmp(argv[3], "quick") == 0)
        {
            quick_sort(0, n);
        }
        else
        {
            printf("Error: Sort \"%s\" was not found.", argv[3]);
            exit(1);
        }
        break;
    case 'h':
    case 'r':
        if (strcmp(argv[3], "radix") * strcmp(argv[3], "heap") == 0)
        {
            buffer = malloc(4 * n + 4);
            if (buffer == 0)
            {
                printf("Error: Unable to allocate memory of required size.");
                exit(5);
            }
            radix_sort(0, n, 0);
            free(buffer);
        }
        else
        {
            printf("Error: Sort \"%s\" was not found.", argv[3]);
            exit(1);
        }
        break;
    default:
        printf("Error: Sort \"%s\" was not found.", argv[3]);
        exit(1);
    }
    for (line_ptr = 0; line_ptr < n; line_ptr++)
    {
        for (char_ptr = arr[line_ptr]; file_str[char_ptr]; char_ptr++) printf("%c", file_str[char_ptr]);
        printf("\n");
    }
    free(arr);
    free(file_str);
    fclose(file_input);
    exit(0);
}
