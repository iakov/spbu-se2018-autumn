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
    FILE *file_input = fopen(argv[2], "r");
    int line_ptr, char_ptr;
    n = 0;
    for (char_ptr = 0; argv[1][char_ptr]; char_ptr++) n = n * 10 + argv[1][char_ptr] - '0';
    file_str = malloc(MAX_LEN_FILE);
    arr = malloc(4 * n + 4);
    arr[0] = 0;
    char reading_str[MAX_LEN_STR];
    for (line_ptr = 0; line_ptr < n && fgets(reading_str, MAX_LEN_STR, file_input); line_ptr++)
    {
        for (char_ptr = 0; reading_str[char_ptr] != '\n' && reading_str[char_ptr]; char_ptr++)
            file_str[arr[line_ptr] + char_ptr] = reading_str[char_ptr];
        file_str[arr[line_ptr] + char_ptr] = '\0';
        arr[line_ptr + 1] = arr[line_ptr] + char_ptr + 1;
    }
    switch (argv[3][0])
    {
    case 'b': bubble_sort(); break;
    case 'i': insertion_sort(); break;
    case 'm':
        buffer = malloc(4 * n + 4);
        merge_sort(0, n);
        free(buffer);
        break;
    case 'q': quick_sort(0, n); break;
    case 'r':
        buffer = malloc(4 * n + 4);
        radix_sort(0, n, 0);
        free(buffer);
        break;
    default:
        printf("ERROR!!!\n");
        return 0;
    }
    for (line_ptr = 0; line_ptr < n; line_ptr++)
    {
        for (char_ptr = arr[line_ptr]; file_str[char_ptr]; char_ptr++) printf("%c", file_str[char_ptr]);
        printf("\n");
    }
    free(arr);
    free(file_str);
    fclose(file_input);
}
